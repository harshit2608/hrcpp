#pragma once

#include "hotreloader/core/Core.h"
#include "hotreloader/cmdshell/CommandShell.h"
#include "hotreloader/compiler/Compiler.h"

namespace hrcpp
{
    class HRCPP_API CompilerMSVC : public Compiler
    {
    public:
    private:
        std::string GetVisualStudioPath();
        static Scope<CommandShell> m_CommandShell;
    };
}
