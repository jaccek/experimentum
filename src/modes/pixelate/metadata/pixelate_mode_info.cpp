#include "pixelate_mode_info.hpp"

namespace pix {
    PixelateModeInfo::PixelateModeInfo() {
    }

    PixelateModeInfo::~PixelateModeInfo() {
    }

    const char* PixelateModeInfo::modeName() {
        return "Pixelate";
    }

    mapi::Mode* PixelateModeInfo::createMode() {
        return new PixelateMode();
    }
}
