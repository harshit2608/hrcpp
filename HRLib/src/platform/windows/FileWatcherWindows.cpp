#include "platform/windows/FileWatcherWindows.h"

namespace hrcpp
{
    bool FileWatcherWindows::AddWatch(const std::filesystem::path &directoryPath)
    {
        auto p_Watch = Scope<DirectoryWatcher>(new DirectoryWatcher);

        HANDLE h_Directory = CreateFileW(
            directoryPath.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            NULL);

        HR_INFO(directoryPath.string().c_str());

        if (h_Directory == INVALID_HANDLE_VALUE)
        {
            HR_ERROR("Failed to add directory %s to watcher", directoryPath);
            return false;
        }

        p_Watch->m_DirectoryPath = directoryPath;
        p_Watch->h_Directory = h_Directory;
        p_Watch->p_FileWatcher = this;

        return true;
    }

    bool FileWatcherWindows::RemoveWatch(const std::filesystem::path &directoryPath)
    {
        return true;
    }

    bool FileWatcherWindows::RemoveAllWatch()
    {
        return true;
    }

    void FileWatcherWindows::PollEvents()
    {
    }
}
