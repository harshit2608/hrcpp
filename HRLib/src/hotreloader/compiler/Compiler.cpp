#include "hotreloader/compiler/Compiler.h"
#include "platform/windows/Compiler_MSVC.h"

namespace hrcpp
{
    Scope<Compiler> Compiler::Create()
    {
#ifdef HR_PLATFORM_WINDOWS
#if defined(_MSC_VER)
        return CreateScope<CompilerMSVC>();
#else
        HR_ERROR("We support only MSVC for now!!")
        return nullptr;
#endif
#else
        HR_ERROR("Unknown Platform!")
        return nullptr;
#endif
    }
}
