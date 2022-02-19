#pragma once
#include "Core.h"

namespace hrcpp
{
    class HRCPP_API Foo
    {
    public:
        int GetAnswer() const;

    private:
        int m_Answer = 42;
    };
}
