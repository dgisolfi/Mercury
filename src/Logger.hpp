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
#include "Theme.h"


namespace mercury {
    class Logger {
        
    private:
        Logger() {
            theme = new Theme();
            log(Level::debug, "Mercury Enabled");
        }
        ~Logger() {
            delete theme;
        }

        Theme *theme;

        // The single instance
        static Logger mercury;
        Level level = Level::info;
        bool verbose = false;
    
        void log(Level level, std::string msg);

        const std::string lTime();

        const std::string buildLog(Level level, std::string msg);

        const bool inLevel(int low, int high, int l);

    public:
        // mark the copy constructor to delete
        Logger(const Logger&) = delete;

        static Logger& get();

        void setLevel(int l);
        std::string getLevelName(Level level);
        Level getLevel();

        void setVerbose(bool v);

        Theme *getTheme();

        void trace(std::string msg);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void critical(std::string msg);
        void error(std::string msg);
        void off();
    };
};


/**
 * Sum numbers in a vector.
 *
 * This sum is the arithmetic sum, not some other kind of sum that only
 * mathematicians have heard of.
 *
 * @param values Container whose values are summed.
 * @return sum of `values`, or 0.0 if `values` is empty.
 */