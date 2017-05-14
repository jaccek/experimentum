#include "modes_loader.hpp"
#include <cstdio>
#include <dlfcn.h>

using namespace mapi;

namespace e {
    typedef ModeInfo* (*Function)();

    std::vector<void*> ModesLoader::sLibraries = std::vector<void*>();

    std::vector<mapi::ModeInfo*> ModesLoader::loadModes() {
        printf("ModesLoader: loading modes...\r");

        DIR *dir = getDirWithModes();

        std::vector<ModeInfo*> modes;
        dirent *entity;

        while ((entity = readdir(dir)) != NULL) {
            if (!isDirValid(entity->d_name)) {
                continue;
            }
            ModeInfo *modeInfo = loadMode(entity);
            if (modeInfo != nullptr) {
                modes.push_back(modeInfo);
            }
        }
        closedir(dir);

        printf("ModesLoader: %d modes loaded\n", (int) modes.size());

        return modes;
    }

    void ModesLoader::cleanup() {
        for (auto library : sLibraries) {
            dlclose(library);
        }
    }

    DIR* ModesLoader::getDirWithModes() {
        DIR *dir = opendir("./modes");
        if (dir == nullptr) {
            printf("ModesLoader: cannot find modes!\n");
            throw 1;
        }
        return dir;
    }

    bool ModesLoader::isDirValid(const char* dirName) {
        return dirName[0] != '.';
    }

    mapi::ModeInfo* ModesLoader::loadMode(dirent* dir) {
        printf("ModesLoader: found dir: %s\r", dir->d_name);

        // TODO: what if filename will be too long?
        char filename[512];
        sprintf(filename, "./modes/%s/lib%s.so", dir->d_name, dir->d_name);

        printf("ModesLoader: loading %s\n", filename);
        void *library = dlopen(filename, RTLD_NOW);

        if (library == nullptr) {
            printf("ModesLoader: cannot find library: %s\nReason: %s\n", filename, dlerror());
            return nullptr;
        }

        // get mode info from library
        ModeInfo* (*functionGetModeInfo)();
        functionGetModeInfo = (Function) dlsym(library, "getModeInfo");
        if (functionGetModeInfo == nullptr) {
            printf("ModesLoader: cannot find function: getModeInfo\n");
            dlclose(library);
            return nullptr;
        }

        sLibraries.push_back(library);
        ModeInfo *modeInfo = functionGetModeInfo();
        return modeInfo;
    }
}
