#include "hotreloader/filewatcher/FileWatcher.h"
#include "platform/windows/FileWatcherWindows.h"

namespace hrcpp
{
    Scope<FileWatcher> FileWatcher::Create()
    {
#ifdef HR_PLATFORM_WINDOWS
        return CreateScope<FileWatcherWindows>();
#else
        HR_ERROR("Unknown Platform!")
        return nullptr;
#endif
    }
}
