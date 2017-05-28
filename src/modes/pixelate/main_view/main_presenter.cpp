#include "main_presenter.hpp"
#include "main_router.hpp"
#include "calculator/kmeans_calculator.hpp"
#include "calculator/metric/euclides_square_metric.hpp"

namespace pix {
    MainPresenter::MainPresenter(MainContract::View *view) : mView(view) {
        mRouter = new MainRouter();

        mMetric = new EuclidesSquareMetric();
        mCalculator = new KMeansCalculator();
        mCalculator->setMetric(mMetric);
    }

    MainPresenter::~MainPresenter() {
        delete mRouter;

        deleteCalculationThread();
    }

    void MainPresenter::onLoadButtonClicked() {
        mSourceImage = mRouter->loadImage();

        int w, h;
        if (mSourceImage.width() > mSourceImage.height()) {
            w = 200;
            h = mSourceImage.height() * w / mSourceImage.width();
        } else {
            h = 200;
            w = mSourceImage.width() * h / mSourceImage.height();
        }
        mSourceScaledImage = mSourceImage.scaled(w, h);

        initCalculator();

        mView->displaySourceImage(mSourceImage);
        mView->displayOutputImage(mSourceScaledImage);
        mView->unlockCalculateButton();
    }

    void MainPresenter::onCalculateClicked() {
        if (mCalculateThread == nullptr) {
            mView->blockAllWidgetsExceptCancelComputation();
            mView->startTimer();
            mCalculateThread = new std::thread([this]() { calculate(); });
        } else {
            deleteCalculationThread();
            mView->unlockAllWidgets();
            mView->stopTimer();
            onTimerTick();
        }
    }

    void MainPresenter::onTimerTick() {
        printf("iteration: %d\n", mCalculator->iteration());

        mOutputImage = mSourceScaledImage.clone();
        Calculator::State state = mCalculator->state();

        for (int x = 0; x < mOutputImage.width(); ++x) {
            for (int y = 0; y < mOutputImage.height(); ++y) {
                auto color = mOutputImage.pixel(x, y);
                int bestIdx = 0;
                float minDistance = 1000000000.0f;
                for (unsigned i = 0; i < state.centers.size(); ++i) {
                    float distance = mMetric->distance(state.centers[i], color);
                    if (distance < minDistance) {
                        minDistance = distance;
                        bestIdx = i;
                    }
                }
                mOutputImage.setPixel(x, y, state.centers[bestIdx]);
            }
        }
        mView->displayOutputImage(mOutputImage);
    }

    void MainPresenter::deleteCalculationThread() {
        if (mCalculateThread != nullptr) {
            mCalculator->breakCalculation();
            mCalculateThread->join();
            delete mCalculateThread;
            mCalculateThread = nullptr;
        }
    }

    void MainPresenter::initCalculator() {
        std::vector<Calculator::ColorItem> colors;
        for (int x = 0; x < mSourceScaledImage.width(); ++x) {
            for (int y = 0; y < mSourceScaledImage.height(); ++y) {
                // TODO: merge same colors
                colors.push_back(Calculator::ColorItem{ mSourceScaledImage.pixel(x, y), 1 });
            }
        }
        mCalculator->init(10, colors);
    }

    void MainPresenter::calculate() {
        mCalculator->calculate();
    }
}
