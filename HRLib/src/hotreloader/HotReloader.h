#pragma once

#include "hotreloader/core/Core.h"
#include "hotreloader/filewatcher/FileWatcher.h"
#include "hotreloader/compiler/Compiler.h"

#include <filesystem>
#include <vector>

namespace hrcpp
{
    class HRCPP_API HotReloader
    {
    public:
        ~HotReloader();
        void addSourceDirectory(const std::filesystem::path &directory, bool recursiveSearch = true);
        void removeSourceDirectorry(const std::filesystem::path& directory);
        std::vector<std::filesystem::path> getSourceDirectories();

        void addIncludeDirectory(const std::filesystem::path &directory);
        void removeIncludeDirectorry(const std::filesystem::path& directory);
        std::vector<std::filesystem::path> getIncludeDirectories();

        void addCompileOptions(const std::string& options);
        void removeCompileOptions(const std::string& options);
        std::vector<std::string> getCompileOptions();

        void update();

    private:
        bool performRuntimeSwap();

    private:
        static Scope<FileWatcher> m_FileWatcher;
        static Scope<Compiler> m_Compiler;

        std::vector<std::filesystem::path> m_IncludeDirectories;
        std::vector<std::filesystem::path> m_SourceDirectories;
        std::vector<std::string> m_CompileOptions;
    };
}
