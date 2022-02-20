#pragma once

#include "hotreloader/Core/PlatformDetection.h"

#include <memory>

#ifdef HR_PLATFORM_WINDOWS
    #ifdef HR_BUILD_DLL
        #define HRCPP_API __declspec(dllexport)
    #else
        #define HRCPP_API __declspec(dllimport)
    #endif
#else
    #error LOADER only supports Windows for now!
#endif

namespace hrcpp
{
    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args &&...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#ifdef HR_PLATFORM_WINDOWS
    #include <Windows.h>
#endif // HR_PLATFORM_WINDOWS

#include "hotreloader/logger/HRLogger.h"
