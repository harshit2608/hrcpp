#include "platform/windows/FileWatcherWindows.h"

#include <iostream>

namespace hrcpp
{
    bool FileWatcherWindows::AddWatch(const std::filesystem::path &directoryPath)
    {
        //for (const auto& file : std::filesystem::directory_iterator(directoryPath))
        //{
        //    std::string temp = file.path().string();
        //    HR_TRACE(file.path().string().c_str())
        //}

        auto p_Watch = CreateScope<DirectoryWatcher>();

        HANDLE h_Directory = CreateFileW(
            directoryPath.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            NULL);

        //HR_INFO(directoryPath.string().c_str());
        //std::cout << &h_Directory;

        if (h_Directory == INVALID_HANDLE_VALUE)
        {
            HR_ERROR("Failed to add directory %s to watcher", directoryPath);
            return false;
        }

        p_Watch->m_DirectoryPath = directoryPath;
        p_Watch->h_Directory = h_Directory;
        p_Watch->p_FileWatcher = this;

        if (!ReadDirectoryChangesAsync(p_Watch.get()))
        {
            HR_ERROR("Failed to call ReadDirectoryChangesAsync from %s", __FUNCTION__);
            return false;
        }
        
        m_DirectoryHandles.push_back(h_Directory);
        m_Watchers.push_back(std::move(p_Watch));
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
        WaitForMultipleObjectsEx(m_DirectoryHandles.size(), m_DirectoryHandles.data(), false, 0, true);
    }

    void FileWatcherWindows::LpoverlappedCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
    {
        if (dwErrorCode != ERROR_SUCCESS)
        {
            HR_ERROR("ReadDirectoryChangesAsync Failed %s", __func__)
                return;
        }

        DirectoryWatcher* p_Watch = reinterpret_cast<DirectoryWatcher*>(lpOverlapped);

        FILE_NOTIFY_INFORMATION *p_Notify = nullptr;
        char filenameBuf[MAX_PATH];

        size_t offset = 0;
        do
        {
            p_Notify = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(&p_Watch->buffer[offset]);
            offset += p_Notify->NextEntryOffset;

            int size = WideCharToMultiByte(
                CP_ACP,
                0,
                p_Notify->FileName,
                p_Notify->FileNameLength / sizeof(WCHAR),
                filenameBuf,
                MAX_PATH - 1,
                NULL,
                NULL);

            filenameBuf[size] = 0;

            switch (p_Notify->Action)
            {
            case FILE_ACTION_ADDED:
                HR_INFO("The file is added to the directory: [%s]", filenameBuf);
                break;
            case FILE_ACTION_REMOVED:
                HR_INFO("The file is removed from the directory: [%s]", filenameBuf);
                break;
            case FILE_ACTION_MODIFIED:
                HR_INFO("The file is modified. This can be a change in the time stamp or attributes: [%s]", filenameBuf);
                break;
            case FILE_ACTION_RENAMED_OLD_NAME:
                HR_INFO("The file was renamed and this is the old name: [%s]", filenameBuf);
                break;
            case FILE_ACTION_RENAMED_NEW_NAME:
                HR_INFO("The file was renamed and this is the new name: [%s]", filenameBuf);
                break;
            default:
                HR_WARN("Default error.");
                break;
            }

        } while (p_Notify->NextEntryOffset != 0);

        if (!ReadDirectoryChangesAsync(p_Watch))
        {
            HR_ERROR("Failed to call ReadDirectoryChangesAsync from %s", __FUNCTION__);
            return;
        }
    }

    bool FileWatcherWindows::ReadDirectoryChangesAsync(DirectoryWatcher* pWatch)
    {
        //pWatch->overlap = {};
        return ReadDirectoryChangesW(
            pWatch->h_Directory,
            pWatch->buffer,
            sizeof(pWatch->buffer),
            false,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_DIR_NAME,
            nullptr,
            &pWatch->overlap,
            LpoverlappedCompletionRoutine) != 0;
    }
}
