#pragma once

#ifdef HRT_PLATFORM_WINDOWS
#ifdef HRT_BUILD_DLL
#define HRT_API __declspec(dllexport)
#else
#define HRT_API __declspec(dllimport)
#endif
#else
#error LOADER only supports Windows for now!
#endif
