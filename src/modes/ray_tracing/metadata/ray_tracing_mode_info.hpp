#pragma once

#include "ray_tracing_mode.hpp"
#include <mapi/mode_info.hpp>

namespace ray {
    class RayTracingModeInfo : public mapi::ModeInfo {
    public:
        RayTracingModeInfo();
        virtual ~RayTracingModeInfo();

        virtual const char* modeName();
        virtual mapi::Mode* createMode();
    };
}
