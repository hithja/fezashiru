#pragma once
#include <string>
#include <iostream>

#include "core/io/Files.hpp"
#include "core/Settings.hpp"

enum class LogLevel {
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    NOTICE
};

class Logger {
    private:
    public:
        static void log(LogLevel logLevel, std::string log) { 
            if (Settings::showLogs) {
                switch (logLevel) {
                    case LogLevel::DEBUG:
                        std::cout << "\033[37m[DEBUG]: " << log << "\033[m" << std::endl; 
                        break;
                    case LogLevel::FATAL:
                        std::cout << "\033[31m[FATAL]: " << log << "\033[m" << std::endl; 
                        break;
                    case LogLevel::ERROR:
                        std::cout << "\033[31m[ERROR]: " << log << "\033[m" << std::endl;  
                        break;
                    case LogLevel::WARN:
                        std::cout << "\033[93m[WARN]: " << log << "\033[m" << std::endl; 
                        break;
                    case LogLevel::INFO:
                        std::cout << "\033[36m[INFO]: " << log << "\033[m" << std::endl; 
                        break;
                    case LogLevel::NOTICE:
                        std::cout << "\033[34m[NOTICE]: " << log << "\033[m" << std::endl; 
                        break;
                    default:
                        std::cout << "[UNKNOWN]: " << log << std::endl;
                        break;
                }
            }
        }     
};
