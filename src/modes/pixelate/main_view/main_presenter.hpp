#pragma once

#include "main_contract.hpp"
#include <thread>

namespace pix {

    class MainPresenter : public MainContract::PresenterForView {
    public:
        MainPresenter(MainContract::View *view);
        virtual ~MainPresenter();

        virtual void onLoadButtonClicked();
        virtual void onCalculateClicked();

    private:
        void deleteCalculationThread();
        void calculate();

    private:
        MainContract::View *mView;
        MainContract::Router *mRouter;

        mapi::Bitmap mImage;
        std::thread *mCalculateThread = nullptr;
        bool mCancelCalculation = false;
    };
}
