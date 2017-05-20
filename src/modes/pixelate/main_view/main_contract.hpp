#pragma once

#include <mapi/graphics/bitmap.hpp>

namespace pix {

    class MainContract {
    public:
        class View {
        public:
            virtual ~View() {}

            virtual void displaySourceImage(mapi::Bitmap &bitmap) = 0;
        };

        class PresenterForView {
        public:
            virtual ~PresenterForView() {}

            virtual void onLoadButtonClicked() = 0;
        };

        class Router {
        public:
            virtual ~Router() {}

            virtual mapi::Bitmap loadImage() = 0;
        };
    };
}
