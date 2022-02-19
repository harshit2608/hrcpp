#include "HRLogger.h"

namespace hrcpp
{
    namespace hrlogger
    {
        LogPriority Logger::m_Priority = InfoPriority;
        std::mutex Logger::m_LogMutex;
        const char* Logger::m_Filepath = 0;
        FILE* Logger::file = nullptr;

        void Logger::EnableFileOutput()
        {
            m_Filepath = "HotReloader.log";
            enable_file_output();
        }

        void Logger::EnableFileOutput(const char* new_filepath)
        {
            m_Filepath = new_filepath;
            enable_file_output();
        }

        void Logger::CloseFileOutput()
        {
            free_file();
        }

        void Logger::SetPriority(LogPriority priority)
        {
            m_Priority = priority;
        }

        void Logger::enable_file_output()
        {
            if (file != 0)
            {
                fclose(file);
            }

            file = fopen(m_Filepath, "a");

            if (file == 0)
            {
                printf("Logger: Failed to open file at %s", m_Filepath);
            }
        }

        void Logger::free_file()
        {
            fclose(file);
            file = nullptr;
        }
    }
}
