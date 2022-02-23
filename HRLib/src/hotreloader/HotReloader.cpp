#include "HotReloader.h"

#include <iostream>

namespace hrcpp
{
    Scope<FileWatcher> HotReloader::m_FileWatcher = FileWatcher::Create();
    Scope<Compiler> HotReloader::m_Compiler = Compiler::Create();

    const static std::vector<std::string> DEFAULT_COMPILE_OPTIONS = {
        "/std:c++17", // Use C++17 standard.
        "/Z7",        // Add full debugging information.
        "/FC",        // Print full filepath in diagnostic messages.
        "/MP",        // Build with multiple processes.
#ifdef _DEBUG
        // Debug flags.
        "/MDd", // Use multithreaded debug DLL version of run-time library.
        "/LD",  // Create debug DLL.
#else
        // Release flags.
        "/MD", // Use multithreaded release DLL version of run-time library.
        "/Zo", // Enable enhanced debugging for optimized code.
        "/LD", // Create release DLL.
#endif
    };

    void HotReloader::addSourceDirectory(const std::filesystem::path& directory, bool recursiveSearch)
    {
        HR_INFO(directory.string().c_str());
        m_FileWatcher->AddWatch(directory,recursiveSearch);
    }

    void HotReloader::removeSourceDirectorry(const std::filesystem::path& directory)
    {
        m_FileWatcher->RemoveWatch(directory);
    }

    std::vector<std::filesystem::path> HotReloader::getSourceDirectories()
    {
        return m_SourceDirectories;
    }

    void HotReloader::addIncludeDirectory(const std::filesystem::path& directory)
    {
        m_FileWatcher->AddWatch(directory,false);
    }

    void HotReloader::removeIncludeDirectorry(const std::filesystem::path& directory)
    {
        m_FileWatcher->RemoveWatch(directory);
    }

    std::vector<std::filesystem::path> HotReloader::getIncludeDirectories()
    {
        return m_IncludeDirectories;
    }

    void HotReloader::addCompileOptions(const std::string& options)
    {

    }

    void HotReloader::removeCompileOptions(const std::string& options)
    {

    }

    std::vector<std::string> HotReloader::getCompileOptions()
    {
        return m_CompileOptions;
    }

    void HotReloader::update()
    {
        m_FileWatcher->PollEvents();
    }

    HotReloader::~HotReloader()
    {
        m_FileWatcher->RemoveAllWatch();
    }
}
