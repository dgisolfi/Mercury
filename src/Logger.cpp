/**
 * @file Logger.cpp
 *
 * @brief Singleton Logging Class
 *
 * @author Daniel Nicolas Gisolfi
 * Contact: Daniel.Gisolfi1@marist.edu
 *
 */

#include <iostream>
#include <time.h>
#include "Logger.h"


namespace mercury {

    /*
    * PRIVATE
    */ 
   
    /*
    * info = [ "INFO", "WARN", "CRITICAL"]
    * debug = info + [ "DEBUG" ]
    * trace = debug + [ "TRACE" ]
    * err => throws error and exits program
    * off => disables logging
    */ 
    void Logger::log(Level level, std::string msg){
        std::string l;

        if (Logger::getLevel() != Level::off) {
         
                switch (Logger::getLevel()) {
                case Level::trace:
                    if (Logger::inLevel(Level::trace, Level::err, level)) {
                        l = Logger::buildLog(level, msg);
                    }
                    break; 
                case Level::debug:
                    if (Logger::inLevel(Level::debug, Level::err, level)) {
                        l = Logger::buildLog(level, msg);
                    }
                    break;
                case Level::info:
                    if (Logger::inLevel(Level::info, Level::err, level)) {
                        l = Logger::buildLog(level, msg);
                    }
                    break;
            };
        };
        
        if (!l.empty()) {
            std::cout << l << std::endl;
        };
    };

    const std::string Logger::lTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%X", &tstruct);

        return buf;
    }

    const std::string Logger::buildLog(Level level, std::string msg) {
        Theme *t = Logger::getTheme();
        std::string log;
        if (t -> getIsTimestampEnabled()) {
            log += Logger::lTime() + t -> getSeperator();
        };
        
        log += Logger::getLevelName(level).substr(0, t -> getLevelNameLen()) + t -> getSeperator();
        log += msg;
        return t -> apply(level, log);
    }

    const bool Logger::inLevel(int low, int high, int l) { 
        return ((l-high)*(l-low) <= 0); 
    };
    
    
    /*
    * PUBLIC
    */

    // Create the single instance of the logger
    Logger Logger::mercury;
   
    Logger& Logger::get() {
        return mercury;
    };

    std::string Logger::getLevelName(Level level) {
        return level_names[level];
    };

    Level Logger::getLevel() {
        return Logger::level;
    };

    void Logger::setLevel(int l) {
        Logger::level = static_cast<Level>(l);;
    };

    void Logger::setVerbose(bool v) {
        Logger::verbose = v;
    };

    Theme *Logger::getTheme() { return Logger::theme; };

    void Logger::trace(std::string msg) {
        Logger::log(Level::trace, msg);
    };

    void Logger::debug(std::string msg) {
        Logger::log(Level::debug, msg);
    };

    void Logger::info(std::string msg) {
        Logger::log(Level::info, msg);
    };

    void Logger::warn(std::string msg) {
        Logger::log(Level::warn, msg);
    };

    void Logger::critical(std::string msg) {
        Logger::log(Level::critical, msg);
    };

    void Logger::error(std::string msg) {
        Logger::log(Level::err, msg);
        exit(EXIT_FAILURE);
    };
    
    void Logger::off() {
        Logger::setLevel(Level::off);
        Logger::log(Level::debug, "Mercury Disabled");
    };
    
};