#pragma once

#include "mode.hpp"

namespace mapi
{
    class ModeInfo
    {
    public:
        virtual ~ModeInfo() {}

        virtual const char* modeName() = 0;
        virtual Mode* createMode() = 0;
    };
}
