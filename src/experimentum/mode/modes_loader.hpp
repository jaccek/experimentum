#pragma once

#include <vector>
#include <dirent.h>

#include <mapi/mode_info.hpp>

namespace e {
class ModesLoader {
    public:
        static std::vector<mapi::ModeInfo*> loadModes();
        static void cleanup();

    private:
        static DIR* getDirWithModes();
        static bool isDirValid(const char* dirName);
        static mapi::ModeInfo* loadMode(dirent* dir);

        static std::vector<void*> sLibraries;
    };
}
