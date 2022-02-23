#include "platform/windows/Compiler_MSVC.h"

namespace hrcpp
{
    Scope<CommandShell> CompilerMSVC::m_CommandShell = CommandShell::Create();
    std::string CompilerMSVC::GetVisualStudioPath()
    {
        std::string compilerVersion = "16.0";
        switch (_MSC_VER)
        {
        case 1900:
            compilerVersion = "14.0";
            break;
        case 1910:
        case 1911:
        case 1912:
        case 1913:
        case 1914:
        case 1915:
        case 1916:
            compilerVersion = "15.0";
            break;
        case 1920:
        case 1921:
        case 1922:
        case 1923:
        case 1924:
        case 1925:
        case 1926:
        case 1927:
        case 1928:
            compilerVersion = "16.0";
            break;
        default:
            HR_WARN("Unknown compiler version, using default version %s", compilerVersion)
            break;
        }

        std::string command = "\"%ProgramFiles(x86)%\\Microsoft Visual Studio\\Installer\\vswhere\""
                              " -version " +
                              compilerVersion +
                              " -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64"
                              " -property installationPath";

        HR_TRACE("%s", command)
        return command;
    }
}
