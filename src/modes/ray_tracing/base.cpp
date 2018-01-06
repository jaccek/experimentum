#include "metadata/ray_tracing_mode_info.hpp"

extern "C" mapi::ModeInfo* getModeInfo() {
    return new ray::RayTracingModeInfo();
}
