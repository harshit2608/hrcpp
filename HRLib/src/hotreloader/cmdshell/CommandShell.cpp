#include "hotreloader/cmdshell/CommandShell.h"
#include "platform/windows/CommandShellWindows.h"

namespace hrcpp
{
    Scope<CommandShell> CommandShell::Create()
    {
#ifdef HR_PLATFORM_WINDOWS
        return CreateScope<CommandShellWindows>();
#else
        HR_ERROR("Unknown Platform!")
        return nullptr;
#endif
    }
}
