#include "metadata/pixelate_mode_info.hpp"

extern "C" mapi::ModeInfo* getModeInfo() {
    return new pix::PixelateModeInfo();
}
