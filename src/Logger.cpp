/**
 * @file Logger.cpp
 *
 * @brief Logging Class
 *
 * @author Daniel Nicolas Gisolfi
 * Contact: Daniel.Gisolfi1@marist.edu
 *
 */

#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Logger.h"


namespace mercury {

    /*
    * PRIVATE
    */ 
   
    void Logger::log(std::string msg){
        std::string l;
        switch (level) {
        case Level::trace:
            break;
        case Level::debug:
            break;
        case Level::info:
            l = Logger::buildLog(msg);
            break;
        case Level::warn:
            break;
        case Level::err:
            break;
        case Level::critical:
            break;
        }

        std::cout << l << std::endl;
    };

    const std::string Logger::lTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%X", &tstruct);

        return buf;
    }

    const std::string Logger::buildLog(std::string msg) {
        std::string log = Logger::lTime() + Logger::getSeperator() + Logger::getLevel() + Logger::getSeperator() + msg;
        return log;
    }
    
    
    /*
    * PUBLIC
    */
    // Create the single instance of the logger
    Logger Logger::instance;
   
    Logger& Logger::get() {
        return instance;
    };

    std::string Logger::getLevel() {
        return level_names[level];
    };

    void Logger::setLevel(int l) {
        Logger::level = static_cast<Level>(l);;
    };

    void Logger::setVerbose(bool v) {
        Logger::verbose = v;
    };

    void Logger::setSeperator(std::string s) {
        Logger::seperator = s;
    };

    std::string Logger::getSeperator() {
        return Logger::seperator;
    };

    void Logger::trace(std::string msg) {
        Logger::log(msg);
    };

    void Logger::debug(std::string msg) {
        Logger::log(msg);
    };

    void Logger::info(std::string msg) {
        Logger::log(msg);
    };

    void Logger::warn(std::string msg) {
        Logger::log(msg);
    };

    void Logger::error(std::string msg) {
        Logger::log(msg);
    };

    void Logger::critical(std::string msg) {
        Logger::log(msg);
    };
    
    void Logger::off() {
        Logger::setLevel(Level::off);
    };
};