#pragma once

#include <mapi/graphics/bitmap.hpp>

namespace pix {

    class MainContract {
    public:
        class View {
        public:
            virtual ~View() {}

            virtual void displaySourceImage(mapi::Bitmap &bitmap) = 0;
            virtual void displayOutputImage(mapi::Bitmap &bitmap) = 0;

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

            virtual void onTimerTick() = 0;
        };

        class Router {
        public:
            virtual ~Router() {}

            virtual mapi::Bitmap loadImage() = 0;
        };
    };
}
