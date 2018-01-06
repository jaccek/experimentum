#include "ray_tracing_mode_info.hpp"

namespace ray {
    RayTracingModeInfo::RayTracingModeInfo() {
    }

    RayTracingModeInfo::~RayTracingModeInfo() {
    }

    const char* RayTracingModeInfo::modeName() {
        return "Ray Tracing";
    }

    mapi::Mode* RayTracingModeInfo::createMode() {
        return new RayTracingMode();
    }
}
