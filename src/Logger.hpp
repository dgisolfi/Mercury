#pragma once
#include <iostream>
#include <time.h>
#include "theme.hpp"

#ifndef MERCURY_LOGGER_HPP
#define MERCURY_LOGGER_HPP


namespace mercury {
    /**
     * Implementation of a singleton logger
     *
     * The logger class supports 6 logging levels and the off level. In
     * Addition the output can be styled using the Theme class.
     */
    class Logger {
        
    private:
        Logger(): level(Level::debug) {
            theme = new Theme();
            log(Level::debug, "Mercury Enabled");
        }
        Logger(Level l): level(l) {
            theme = new Theme();
            log(Level::debug, "Mercury Enabled");
        }
        ~Logger() {
            delete theme;
        }

        Level level;
        // The single instance
        static Logger mercury;
 
        Theme *theme;

        
        /**
         * Logs messages according to Logging Level.
         *
         * @param level - A Level enum value
         * @param msg - The msg to be logged
         */
        void log(Level level, std::string msg);

        /**
         * Gets current time in H:M:S format.
         *
         * @returns time - a string of the current time.
         */
        const std::string lTime();

        /**
         * Builds the final log
         * 
         * Handles the timestamp and Level Name length application
         * to the log
         * 
         * @param level - A Level enum value
         * @param msg - The msg to be logged
         *
         * @returns the final log message
         */
        const std::string buildLog(Level level, std::string msg);
        
        /**
         * Checks if a level is within a range of levels
         * 
         * 
         * @param low The low end of the range
         * @param high The high end of the range
         * @param l The level to check
         *
         * @returns wether l is within the given range
         */
        const bool inLevel(int low, int high, int l);

    public:
        // mark the copy constructor to delete
        Logger(const Logger&) = delete;

        /**
         * Gets the singleton instance of mercury
         *
         * @returns the single instance of mercury
         */
        static Logger& get();

        /**
         * Gets the Level name
         *
         * @param level
         * 
         * @returns string name of Level
         */
        std::string getLevelName(Level level);

        /**
         * Gets the current logging level
         *
         * @returns Level
         */
        Level getLevel();

        /**
         * Sets the current logging level
         *
         * @param l the level to be set
         */
        void setLevel(Level l);

        /**
         * Gets the pointer to Mercury's theme object
         *
         * @returns Theme pointer to theme
         */
        Theme *getTheme();

        /**
         * Logs a message at the trace Logging Level
         *
         * @params msg message to be logged at applicable level 
         */
        void trace(std::string msg);

        /**
         * Logs a message at the debug Logging Level
         *
         * @params msg message to be logged at applicable level 
         */
        void debug(std::string msg);

        /**
         * Logs a message at the info Logging Level
         *
         * @params msg message to be logged at applicable level 
         */
        void info(std::string msg);

        /**
         * Logs a message at the warn Logging Level
         *
         * @params msg message to be logged at applicable level 
         */
        void warn(std::string msg);

        /**
         * Logs a message at the critical Logging Level
         *
         * @params msg message to be logged at applicable level 
         */
        void critical(std::string msg);

        /**
         * Logs a message at the error Logging Level and exits program
         *
         * @params msg message to be logged at applicable level 
         */
        void error(std::string msg);

        /**
         * Disables Logging
         */
        void off();
    };
};

#endif // MERCURY_LOGGER_HPP
