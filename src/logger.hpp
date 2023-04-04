#ifndef LAMINARFLOW_LOGGER_H
#define LAMINARFLOW_LOGGER_H

#include <bits/types/time_t.h>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <ctime>

/**
 * @brief Simple Logger for project. More functions may be supported in the future.
 * 
 */
class Logger
{
    public:
        enum LogLevel
        {
            INFO,
            WARN,
            ERROR,
            FATAL,

            DEBUG
        };
        Logger()
        {

        }
        ~Logger()
        {
            
        }
        void log(enum LogLevel lv, const std::string& msg)
        {
            time_t t;
            time(&t);
            auto localt=localtime(&t);

            std::string lvstr;
            switch (lv)
            {
                case LogLevel::INFO :   lvstr="INFO";   break;
                case LogLevel::WARN :   lvstr="WARN";   break;
                case LogLevel::ERROR:   lvstr="ERROR";  break;
                case LogLevel::FATAL:   lvstr="FATAL";  break;
                case LogLevel::DEBUG:   lvstr="DEBUG";  break;
                default:
                    std::runtime_error("invalid LogLevel. LogLevel type only includes: INFO, WARN, ERROR, FATAL, DEBUG.");
                    return;
            }

            printf("[%02d:%02d:%02d] [%s] %s\n", localt->tm_hour, localt->tm_min, localt->tm_sec, lvstr.c_str(), msg.c_str());

        }
        void Info(const std::string& msg)
        {
            log(LogLevel::INFO, msg);
        }
        void Warn(const std::string& msg)
        {
            log(LogLevel::WARN, msg);
        }
        void Error(const std::string& msg)
        {
            log(LogLevel::ERROR, msg);
        }
        void Fatal(const std::string& msg)
        {
            log(LogLevel::FATAL, msg);
        }
        void Debug(const std::string& msg)
        {
            log(LogLevel::DEBUG, msg);
        }
};

#endif //LAMINARFLOW_LOGGER_H