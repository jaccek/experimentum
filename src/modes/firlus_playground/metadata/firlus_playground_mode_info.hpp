#pragma once

#include "firlus_playground_mode.hpp"
#include <mapi/mode_info.hpp>

namespace fp {
    class FirlusPlaygroundModeInfo : public mapi::ModeInfo {
    public:
        FirlusPlaygroundModeInfo();
        virtual ~FirlusPlaygroundModeInfo();

        virtual const char* modeName();
        virtual mapi::Mode* createMode();
    };
}
