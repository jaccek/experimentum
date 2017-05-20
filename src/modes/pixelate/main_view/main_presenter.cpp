#include "main_presenter.hpp"
#include "main_router.hpp"

namespace pix {
    MainPresenter::MainPresenter(MainContract::View *view) : mView(view) {
        mRouter = new MainRouter();
    }

    MainPresenter::~MainPresenter() {
        delete mRouter;

        deleteCalculationThread();
    }

    void MainPresenter::onLoadButtonClicked() {
        mImage = mRouter->loadImage();
        mView->displaySourceImage(mImage);
    }

    void MainPresenter::onCalculateClicked() {
        if (mCalculateThread == nullptr) {
            mView->blockAllWidgetsExceptCancelComputation();
            mCancelCalculation = false;
            mCalculateThread = new std::thread([this]() { printf("thread\n"); });
        } else {
            deleteCalculationThread();
            mView->unlockAllWidgets();
        }
    }

    void MainPresenter::deleteCalculationThread() {
        if (mCalculateThread != nullptr) {
            mCancelCalculation = true;
            mCalculateThread->join();
            delete mCalculateThread;
            mCalculateThread = nullptr;
        }
    }
}
