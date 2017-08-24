#pragma once

#include "calculator/calculator.hpp"
#include "calculator/metric/metric.hpp"
#include <mapi/graphics/bitmap.hpp>
#include <vector>

namespace pix {

    class MainContract {
    public:
        class View {
        public:
            virtual ~View() {}

            virtual void setupMetricsNames(std::vector<Metric*>& metrics) = 0;
            virtual void setupCalculatorsNames(std::vector<Calculator*>& calculators) = 0;

            virtual void displaySourceImage(mapi::Bitmap &bitmap) = 0;
            virtual void displayOutputImage(mapi::Bitmap &bitmap) = 0;
            virtual void displayOutputColors(std::vector<mapi::Color>& colors) = 0;

            virtual void blockAllWidgetsExceptCancelComputation() = 0;
            virtual void unlockCalculateButton() = 0;
            virtual void unlockAllWidgets() = 0;

            virtual void startTimer() = 0;
            virtual void stopTimer() = 0;
        };

        class PresenterForView {
        public:
            virtual ~PresenterForView() {}

            virtual void onLoadButtonClicked() = 0;
            virtual void onCalculateClicked() = 0;
            virtual void onColorsCountChanged(int colorsCount) = 0;
            virtual void onCalculatorSelected(Calculator* calculator) = 0;
            virtual void onMetricSelected(Metric* metric) = 0;

            virtual void onTimerTick() = 0;

            virtual int colorsCount() = 0;
        };

        class Router {
        public:
            virtual ~Router() {}

            virtual mapi::Bitmap loadImage() = 0;
        };
    };
}
