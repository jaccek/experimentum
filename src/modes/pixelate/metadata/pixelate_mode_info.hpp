#pragma once

#include "pixelate_mode.hpp"
#include <mapi/mode_info.hpp>

namespace pix {
    class PixelateModeInfo : public mapi::ModeInfo {
    public:
        PixelateModeInfo();
        virtual ~PixelateModeInfo();

        virtual const char* modeName();
        virtual mapi::Mode* createMode();
    };
}
