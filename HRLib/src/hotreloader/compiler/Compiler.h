#pragma once

#include "hotreloader/core/Core.h"

namespace hrcpp
{
    class HRCPP_API Compiler
    {
    public:
        static Scope<Compiler> Create();
    };
}
