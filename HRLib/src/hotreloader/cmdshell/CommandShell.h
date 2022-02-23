#pragma once

#include "hotreloader/core/Core.h"

namespace hrcpp
{
    class HRCPP_API CommandShell
    {
    public:
        virtual ~CommandShell() = default;
        static Scope<CommandShell> Create();
    };
}
