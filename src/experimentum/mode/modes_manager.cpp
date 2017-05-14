#include "modes_manager.hpp"
#include "modes_loader.hpp"

namespace e {
    ModesManager::ModesManager() {
        mModes = ModesLoader::loadModes();
    }

    ModesManager::~ModesManager() {
        ModesLoader::cleanup();
    }

    std::vector<mapi::ModeInfo*> ModesManager::modes() {
        return mModes;
    }
}
