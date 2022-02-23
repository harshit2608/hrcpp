#pragma once
#include "Core.h"

// This line prevents C++ name mangling which would prevent dlsym from retrieving
// the correct symbols.
extern "C"
{
    HRT_API void foo();
    HRT_API extern int bar;
}
