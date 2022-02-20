#pragma once

#include "hotreloader/core/Core.h"

#include <filesystem>

namespace hrcpp
{
    enum EventType
    {
        EventNewFile,
        EventFileRemoved,
        EventFileModified
    };

    class HRCPP_API FileWatcher
    {
    public:
        virtual ~FileWatcher() = default;

        virtual bool AddWatch(const std::filesystem::path &directoryPath) = 0;
        virtual bool RemoveWatch(const std::filesystem::path &directoryPath) = 0;
        virtual bool RemoveAllWatch() = 0;
        virtual void PollEvents() = 0;

        static Scope<FileWatcher> Create();
    };
}
