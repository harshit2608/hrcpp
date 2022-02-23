#pragma once

#include "hotreloader/core/Core.h"
#include "hotreloader/logger/ColorCodes.h"

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
            static void EnableFileOutput(const char *new_filepath);

            static void SetPriority(LogPriority priority);

            template <typename... Args>
            static void Trace(int line, const char *sourceFile, const char *color, const char *message, Args... args)
            {
                GetInstance().log(line, sourceFile, color, "[Trace] : ", TracePriority, message, args...);
            }

            template <typename... Args>
            static void Info(int line, const char *sourceFile, const char *color, const char *message, Args... args)
            {
                GetInstance().log(line, sourceFile, color, "[Info] : ", InfoPriority, message, args...);
            }

            template <typename... Args>
            static void Warn(int line, const char *sourceFile, const char *color, const char *message, Args... args)
            {
                GetInstance().log(line, sourceFile, color, "[Warn] : ", WarnPriority, message, args...);
            }

            template <typename... Args>
            static void Error(int line, const char *sourceFile, const char *color, const char *message, Args... args)
            {
                GetInstance().log(line, sourceFile, color, "[Error] : ", ErrorPriority, message, args...);
            }

            template <typename... Args>
            static void Critical(int line, const char *sourceFile, const char *color, const char *message, Args... args)
            {
                GetInstance().log(line, sourceFile, color, "[Critical] : ", CriticalPriority, message, args...);
            }

        private:
            LogPriority m_Priority = TracePriority;
            std::mutex m_LogMutex;
            const char *m_Filepath = 0;
            FILE *file = nullptr;

        private:
            Logger()
            {
            }

            Logger(const Logger &) = delete;
            Logger &operator=(const Logger &) = delete;

            ~Logger()
            {
                free_file();
            }

            static Logger &GetInstance()
            {
                static Logger logger;
                return logger;
            }

        private:
            void enable_file_output();
            void free_file();

            template <typename... Args>
            void log(int line, const char *sourceFile, const char *color, const char *messagePriorityStr, LogPriority messagePriority, const char *message, Args... args)
            {
                if (m_Priority <= messagePriority)
                {
                    std::time_t current_time = std::time(0);
                    std::tm *timestamp = std::localtime(&current_time);
                    char buffer[80];
                    strftime(buffer, 80, "%I:%M:%S %p", timestamp);

                    std::scoped_lock lock(m_LogMutex);
                    printf(color);
                    printf("[%s]", buffer);
                    printf("[HRCPP]");
                    printf(messagePriorityStr);
                    printf(message, args...);
                    printf(" on line %d in %s ", line, sourceFile);
                    printf(Reset);
                    printf("\n");

                    if (file)
                    {
                        fprintf(file, "[%s]", buffer);
                        fprintf(file, "[HRCPP]");
                        fprintf(file, messagePriorityStr);
                        fprintf(file, message, args...);
                        fprintf(file, " on line %d in %s ", line, sourceFile);
                        fprintf(file, "\n");
                    }
                }
            }
        };
    }
}

#define HR_TRACE(Message, ...) ::hrcpp::hrlogger::Logger::Trace(__LINE__, __FILE__, White, Message, __VA_ARGS__);
#define HR_INFO(Message, ...) ::hrcpp::hrlogger::Logger::Info(__LINE__, __FILE__, Green, Message, __VA_ARGS__);
#define HR_WARN(Message, ...) ::hrcpp::hrlogger::Logger::Warn(__LINE__, __FILE__, Yellow, Message, __VA_ARGS__);
#define HR_ERROR(Message, ...) ::hrcpp::hrlogger::Logger::Error(__LINE__, __FILE__, Red, Message, __VA_ARGS__);
#define HR_CRITICAL(Message, ...) ::hrcpp::hrlogger::Logger::Critical(__LINE__, __FILE__, Magenta, Message, __VA_ARGS__);
