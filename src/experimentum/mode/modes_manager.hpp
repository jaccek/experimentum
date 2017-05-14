#pragma once

#include <mapi/mode_info.hpp>
#include <vector>

namespace e {
    class ModesManager {
    public:
        ModesManager();
        ~ModesManager();

        std::vector<mapi::ModeInfo*> modes();

    private:
        std::vector<mapi::ModeInfo*> mModes;
    };
}
