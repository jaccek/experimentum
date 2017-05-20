#pragma once

#include "main_contract.hpp"

namespace pix {

    class MainRouter : public MainContract::Router {
    public:
        virtual ~MainRouter();

        virtual mapi::Bitmap loadImage();
    };
}
