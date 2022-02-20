#pragma once

#include "hotreloader/filewatcher/FileWatcher.h"

namespace hrcpp
{
    class HRCPP_API FileWatcherWindows : public FileWatcher
    {
    public:

        bool AddWatch(const std::filesystem::path& directoryPath) override;
        bool RemoveWatch(const std::filesystem::path& directoryPath) override;
        bool RemoveAllWatch() override;
        void PollEvents() override;

    private:

        struct DirectoryWatcher
        {
            std::filesystem::path m_DirectoryPath;
            HANDLE h_Directory = INVALID_HANDLE_VALUE;
            FileWatcherWindows* p_FileWatcher = nullptr;
        };

    };
}
