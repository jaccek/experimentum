#include "main_presenter.hpp"
#include "main_router.hpp"
#include "calculator/gng_calculator.hpp"
#include "calculator/kmeans_calculator.hpp"
#include "calculator/metric/euclides_rgb_square_metric.hpp"
#include "calculator/metric/euclides_hsv_metric.hpp"
#include <map>

namespace pix {
    MainPresenter::MainPresenter(MainContract::View *view) : mView(view) {
        mRouter = new MainRouter();

        std::vector<Metric*> metrics;
        metrics.push_back(new EuclidesHsvMetric());
        metrics.push_back(new EuclidesRgbSquareMetric());
        view->setupMetricsNames(metrics);
        mCurrentMetric = metrics[0];

        // mCalculator = new KMeansCalculator();
        mCalculator = new GngCalculator();
        mCalculator->setMetric(mCurrentMetric);
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

    void MainPresenter::onColorsCountChanged(int colorsCount) {
        printf("MainPresenter: change colors count: %d\n", colorsCount);
        mColorsCount = colorsCount;
        initCalculator();   // TODO: here we can init only colors count
    }

    void MainPresenter::onMetricSelected(Metric* metric) {
        printf("MainPresenter: change metric to: %s\n", metric->name().c_str());
        mCurrentMetric = metric;
        mCalculator->setMetric(mCurrentMetric);
    }

    void MainPresenter::onTimerTick() {
        printf("iteration: %d\n", mCalculator->iteration());

        mOutputImage = mSourceScaledImage.clone();
        Calculator::State state = mCalculator->state();

        updateOutputImage(state);
        mView->displayOutputImage(mOutputImage);
    }

    int MainPresenter::colorsCount() {
        return mColorsCount;
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
        std::map<uint32_t, unsigned> colorToIndexMap;

        for (int x = 0; x < mSourceScaledImage.width(); ++x) {
            for (int y = 0; y < mSourceScaledImage.height(); ++y) {
                auto color = mSourceScaledImage.pixel(x, y);
                auto iterator = colorToIndexMap.find(color.asUint32());

                if (iterator == colorToIndexMap.end()) {
                    colorToIndexMap[color.asUint32()] = colors.size();
                    colors.push_back(Calculator::ColorItem{ color, 1 });
                } else {
                    colors[iterator->second].count += 1;
                }
            }
        }

        printf("unique colors count: %d\n", (int) colors.size());
        mCalculator->init(mColorsCount, colors);
    }

    void MainPresenter::calculate() {
        mCalculator->calculate();
    }

    void MainPresenter::updateOutputImage(Calculator::State state) {
        for (int x = 0; x < mOutputImage.width(); ++x) {
            for (int y = 0; y < mOutputImage.height(); ++y) {
                auto color = mOutputImage.pixel(x, y);
                int bestIdx = 0;
                float minDistance = 1000000000.0f;

                for (unsigned i = 0; i < state.centers.size(); ++i) {
                    float distance = mCurrentMetric->distance(state.centers[i], color);
                    if (distance < minDistance) {
                        minDistance = distance;
                        bestIdx = i;
                    }
                }
                mOutputImage.setPixel(x, y, state.centers[bestIdx]);
            }
        }
    }
}
