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
            OVERLAPPED overlap = {};
            alignas(sizeof(DWORD)) uint8_t buffer[32 * 1024];
            std::filesystem::path m_DirectoryPath;
            HANDLE h_Directory = INVALID_HANDLE_VALUE;
            FileWatcherWindows* p_FileWatcher = nullptr;
        };

      private:
        static void LpoverlappedCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);
        static bool ReadDirectoryChangesAsync(DirectoryWatcher* pWatch);

    private:
        std::vector<Ref<DirectoryWatcher>> m_Watchers;
        std::vector<HANDLE> m_DirectoryHandles;
    };
}
