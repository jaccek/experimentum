#pragma once

#include "main_contract.hpp"
#include "calculator/calculator.hpp"
#include <thread>

namespace pix {

    class MainPresenter : public MainContract::PresenterForView {
    public:
        MainPresenter(MainContract::View *view);
        virtual ~MainPresenter();

        virtual void onLoadButtonClicked();
        virtual void onCalculateClicked();
        virtual void onColorsCountChanged(int colorsCount);
        virtual void onMetricSelected(Metric* metric);

        virtual void onTimerTick();

        virtual int colorsCount();

    private:
        void deleteCalculationThread();
        void initCalculator();
        void calculate();

    private:
        MainContract::View *mView;
        MainContract::Router *mRouter;

        mapi::Bitmap mSourceImage;
        mapi::Bitmap mSourceScaledImage;
        mapi::Bitmap mOutputImage;

        Calculator *mCalculator;
        Metric* mCurrentMetric;
        std::thread *mCalculateThread = nullptr;

        int mColorsCount = 20;
    };
}
