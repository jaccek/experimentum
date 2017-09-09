#include "metadata/firlus_playground_mode_info.hpp"

extern "C" mapi::ModeInfo* getModeInfo() {
    return new fp::FirlusPlaygroundModeInfo();
}
