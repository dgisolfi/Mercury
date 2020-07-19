/**
 * @file Logger.cpp
 *
 * @brief Logging Class
 *
 * @author Daniel Nicolas Gisolfi
 * Contact: Daniel.Gisolfi1@marist.edu
 *
 */

#pragma once
// #include <string>
#include "Level.h"

namespace mercury {
    class Logger {
        
    private:

        Logger() {}

        // The single instance
        static Logger instance;
        Level level = Level::off;
        bool verbose = false;
        std::string seperator = " - ";
    
        void log(std::string msg);

        const std::string lTime();

        const std::string buildLog(std::string msg);

    public:
        // mark the copy constructor to delete
        Logger(const Logger&) = delete;

        static Logger& get();

        void setLevel(int l);
        std::string getLevel();

        void setVerbose(bool v);

        void setSeperator(std::string s);
        std::string getSeperator();

        void trace(std::string msg);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
        void critical(std::string msg);
        void off();
    };
};

