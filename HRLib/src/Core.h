#pragma once

#ifdef HR_PLATFORM_WINDOWS
    #ifdef HR_BUILD_DLL
        #define HRCPP_API __declspec(dllexport)
    #else
        #define HRCPP_API __declspec(dllimport)
    #endif
#else
    #error LOADER only supports Windows!
#endif
