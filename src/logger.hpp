#ifndef LAMINARFLOW_LOGGER_H
#define LAMINARFLOW_LOGGER_H

#include <bits/types/time_t.h>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <ctime>
#include <utility>

/**
 * @brief Simple Logger for project. More functions may be supported in the future.
 * 
 */
class Logger {
    public:
        enum LogLevel {
            INFO,
            WARN,
            ERROR,
            FATAL,
            DEBUG
        };
        
        explicit Logger(std::string  name): _name(std::move(name)) {

		}

        ~Logger() = default;

		void log(enum LogLevel lv, const std::string& msg) {
            time_t t;
            time(&t);
            auto localt=localtime(&t);

            std::string lvstr;
            switch (lv) {
				case LogLevel::INFO :   
					lvstr= _name + "/INFO] ";
					break;
                case LogLevel::WARN :
					lvstr= _name + "/WARN] ";
					break;
                case LogLevel::ERROR:
					lvstr= _name + "/ERROR]";
					break;
                case LogLevel::FATAL:
					lvstr= _name + "/FATAL]";
					break;
                case LogLevel::DEBUG:
					lvstr= _name + "/DEBUG]";
					break;
                default:
                    throw std::runtime_error("invalid LogLevel. LogLevel type only includes: INFO, WARN, ERROR, FATAL, DEBUG.");
                    return;
            }

            printf("[%02d:%02d:%02d] [%s %s\n", localt->tm_hour, localt->tm_min, localt->tm_sec, lvstr.c_str(), msg.c_str());

        }
		void info(const std::string& msg)
        {
            log(LogLevel::INFO, msg);
        }
		void warn(const std::string& msg)
        {
	        log(LogLevel::WARN, msg);
        }
        void error(const std::string& msg)
        {
	        log(LogLevel::ERROR, msg);
        }
        void fatal(const std::string& msg)
        {
	        log(LogLevel::FATAL, msg);
        }
        void debug(const std::string& msg)
        {
	        log(LogLevel::DEBUG, msg);
        }
private:
	std::string _name;
};

#endif //LAMINARFLOW_LOGGER_H