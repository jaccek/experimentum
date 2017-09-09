#include "firlus_playground_mode_info.hpp"

namespace fp {
    FirlusPlaygroundModeInfo::FirlusPlaygroundModeInfo() {
    }

    FirlusPlaygroundModeInfo::~FirlusPlaygroundModeInfo() {
    }

    const char* FirlusPlaygroundModeInfo::modeName() {
        return "Firlus Playground";
    }

    mapi::Mode* FirlusPlaygroundModeInfo::createMode() {
        return new FirlusPlaygroundMode();
    }
}
