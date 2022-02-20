#pragma once

#include "hotreloader/core/Core.h"
#include "hotreloader/filewatcher/FileWatcher.h"

#include <filesystem>

namespace hrcpp
{
    class HRCPP_API HotReloader
    {
    public:
        void addSourceDirectory(const std::filesystem::path &directory, bool recursiveSearch = true);
        void addIncludeDirectory(const std::filesystem::path &directory);

        void update();

    private:
        static Scope<FileWatcher> m_FileWatcher;
    };
}
