#include "HRLogger.h"

namespace hrcpp
{
    namespace hrlogger
    {
        void Logger::EnableFileOutput()
        {
            GetInstance().m_Filepath = "HotReloader.log";
            GetInstance().enable_file_output();
        }

        void Logger::EnableFileOutput(const char *new_filepath)
        {
            GetInstance().m_Filepath = new_filepath;
            GetInstance().enable_file_output();
        }

        void Logger::SetPriority(LogPriority priority)
        {
            GetInstance().m_Priority = priority;
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
