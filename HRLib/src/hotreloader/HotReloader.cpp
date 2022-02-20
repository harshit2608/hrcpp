#include "HotReloader.h"

#include <iostream>

namespace hrcpp
{
    Scope<FileWatcher> HotReloader::m_FileWatcher = FileWatcher::Create();
    void HotReloader::addSourceDirectory(const std::filesystem::path &directory, bool recursiveSearch)
    {
        // std::cout << directory;
        std::string t = directory.string();
        const char *temp = t.c_str();
        HR_INFO(temp);
        m_FileWatcher->AddWatch(directory);
    }

    void HotReloader::addIncludeDirectory(const std::filesystem::path &directory)
    {
        m_FileWatcher->AddWatch(directory);
    }

    void HotReloader::update()
    {
        m_FileWatcher->PollEvents();
    }
}
