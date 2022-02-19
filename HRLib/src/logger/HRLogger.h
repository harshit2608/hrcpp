#pragma once

#include "Core.h"
#include "ColorCodes.h"

#include <stdio.h>
#include <mutex>
#include <string>
#include <ctime>

namespace hrcpp
{
    namespace hrlogger
    {
        enum LogPriority
        {
            TracePriority,
            InfoPriority,
            WarnPriority,
            ErrorPriority,
            CriticalPriority
        };

        class HRCPP_API Logger
        {
        public:
            static void EnableFileOutput();
            static void EnableFileOutput(const char* new_filepath);
            static void CloseFileOutput();

            static void SetPriority(LogPriority priority);

            template <typename... Args>
            static void Trace(const char* message, Args... args)
            {
                log("[Trace] : ", TracePriority, message, args...);
            }

            template <typename... Args>
            static void Info(const char* message, Args... args)
            {
                log("[Info] : ", InfoPriority, message, args...);
            }

            template <typename... Args>
            static void Warn(const char* message, Args... args)
            {
                log("[Warn] : ", WarnPriority, message, args...);
            }

            template <typename... Args>
            static void Error(const char* message, Args... args)
            {
                log("[Error] : ", ErrorPriority, message, args...);
            }

            template <typename... Args>
            static void Critical(const char* message, Args... args)
            {
                log("[Critical] : ", CriticalPriority, message, args...);
            }          

        private:
            static LogPriority m_Priority;
            static std::mutex m_LogMutex;
            static const char* m_Filepath;
            static FILE* file;

        private:
            static void enable_file_output();
            static void free_file();

            template <typename... Args>
            static void log(const char* messagePriorityStr, LogPriority messagePriority, const char* message, Args... args)
            {
                if (m_Priority <= messagePriority)
                {
                    std::time_t current_time = std::time(0);
                    std::tm* timestamp = std::localtime(&current_time);
                    char buffer[80];
                    strftime(buffer, 80, "%I:%M:%S %p", timestamp);

                    std::scoped_lock lock(m_LogMutex);
                    printf("[%s]", buffer);
                    printf("[HRCPP]");
                    printf(messagePriorityStr);
                    printf(message, args...);
                    printf("\n");

                    if (file)
                    {
                        fprintf(file, "[%s]", buffer);
                        fprintf(file, "[HRCPP]");
                        fprintf(file, messagePriorityStr);
                        fprintf(file, message, args...);
                        fprintf(file, "\n");
                    }
                }
            }
        };
    }
}

#define HR_TRACE(...)         ::hrcpp::hrlogger::Logger::Trace(__VA_ARGS__);
#define HR_INFO(...)          ::hrcpp::hrlogger::Logger::Info(__VA_ARGS__);
#define HR_WARN(...)          ::hrcpp::hrlogger::Logger::Warn(__VA_ARGS__);
#define HR_ERROR(...)         ::hrcpp::hrlogger::Logger::Error(__VA_ARGS__);
#define HR_CRITICAL(...)      ::hrcpp::hrlogger::Logger::Critical(__VA_ARGS__);
