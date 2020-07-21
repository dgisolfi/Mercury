/**
 * @Project: Mercury
 * @Description: Lightweight & Colorful Singleton logger
 * @Version: 1.0.0
 * 
 * This is a single header lib, get the latest build from: 
 * Include this file in your project to start using Mercury
 * 
 * @Date: 2020-7-20
 * @Author Daniel Nicolas Gisolfi
 * @License: MIT
 * @Contact: Daniel.Gisolfi1@marist.edu
 * @Website: https://dgisolfi.xyz
 * @Copyright Copyright © Daniel Gisolfi 2020 - Present
*/
#pragma once

#ifndef MERCURY_HPP
#define MERCURY_HPP

#include <iostream>
#include <time.h>

#include <string> 
#include <stdexcept>

#define LEVEL_TRACE 0
#define LEVEL_DEBUG 1
#define LEVEL_INFO 2
#define LEVEL_WARN 3
#define LEVEL_CRITICAL 4
#define LEVEL_ERR 5
#define LEVEL_OFF 6

namespace mercury {

    enum Level {
        trace = LEVEL_TRACE,
        debug = LEVEL_DEBUG,
        info = LEVEL_INFO,
        warn = LEVEL_WARN,
        critical = LEVEL_CRITICAL,
        err = LEVEL_ERR,
        off = LEVEL_OFF
    };
    
    const std::string level_names[7] = {
        /*
         * I have added the needed spaces to make the 
         * names line up vertically even if the max 
         * length is set
         * */ 
        "TRACE   ", 
        "DEBUG   ", 
        "INFO    ", 
        "WARN    ", 
        "CRITICAL", 
        "ERROR   ", 
        "OFF     "
    };
};

namespace mercury {

    /**
     * A two value vector for storing theme modifers
     */
    struct Vector2 {
        int color;
        int style;
    };

    /**
     * Implementation of a Theme
     *
     * The theme class stores all colors and style changes to 
     * each logging levels messages. It also stores the seperator characters 
     * and the additional settings about the look of the logs
     */
    class Theme {
    private:
        Vector2 trace;
        Vector2 debug;
        Vector2 info;
        Vector2 warn;
        Vector2 critical;
        Vector2 error;
        std::string seperator;
        bool is_timestamp_visible;
        int level_name_len;
    public:
        Theme() :
            trace {34, 0}, //    blue, no style
            debug {36, 0}, //    cyan, no style
            info {37, 0}, //     white, no style
            warn {33, 1}, //     yellow, bold
            critical {35, 1}, // magenta, bold
            error {31, 1}, //    red, bold
            seperator(" - "),
            is_timestamp_visible(true),
            level_name_len(4)
        {}
        ~Theme(){}

        /**
         * Get the Vector2 struct that defines the style modifiers
         * for the trace logging level
         *
         * @returns Vector2 Trace Level Theme
         */
        Vector2 getTrace();

        /**
         * Set the Vector2 struct that defines the style modifiers
         * for the trace logging level
         *
         * @param Vector2 Trace Level Theme
         */
        void setTrace(Vector2 v);

        /**
         * Get the Vector2 struct that defines the style modifiers
         * for the debug logging level
         *
         * @returns Vector2 Debug Level Theme
         */
        Vector2 getDebug();

        /**
         * Set the Vector2 struct that defines the style modifiers
         * for the debug logging level
         *
         * @param Vector2 Debug Level Theme
         */
        void setDebug(Vector2 v);

        /**
         * Get the Vector2 struct that defines the style modifiers
         * for the info logging level
         *
         * @returns Vector2 Info Level Theme
         */
        Vector2 getInfo();

        /**
         * Set the Vector2 struct that defines the style modifiers
         * for the info logging level
         *
         * @param Vector2 Info Level Theme
         */
        void setInfo(Vector2 v);

        /**
         * Get the Vector2 struct that defines the style modifiers
         * for the warn logging level
         *
         * @returns Vector2 Warn Level Theme
         */
        Vector2 getWarn();

        /**
         * Set the Vector2 struct that defines the style modifiers
         * for the warn logging level
         *
         * @param Vector2 Warn Level Theme
         */
        void setWarn(Vector2 v);

        /**
         * Get the Vector2 struct that defines the style modifiers
         * for the critical logging level
         *
         * @returns Vector2 Critical Level Theme
         */
        Vector2 getCritical();

        /**
         * Set the Vector2 struct that defines the style modifiers
         * for the critical logging level
         *
         * @param Vector2 Critical Level Theme
         */
        void setCritical(Vector2 v);

        /**
         * Get the Vector2 struct that defines the style modifiers
         * for the error logging level
         *
         * @returns Vector2 Error Level Theme
         */
        Vector2 getError();

        /**
         * Set the Vector2 struct that defines the style modifiers
         * for the error logging level
         *
         * @param Vector2 Error Level Theme
         */
        void setError(Vector2 v);

        /**
         * Set string that be used to seperate components of a log
         *
         * @param std::string log component seperator
         */
        void setSeperator(std::string s);
        /**
         * Get the string that is used to seperate components
         * of a log
         *
         * @returns std::string log component seperator
         */
        std::string getSeperator();

        /**
         * Gets the theme for a given level
         *
         * @param Level level to find theme for
         * 
         * @returns Vector2 theme of specified level
         */
        Vector2 getLevelTheme(Level l);

        /**
         * Sets boolean for timestamp visibility
         *
         * @param is_visible boolean value to set visibility to
         */
        void setIsTimestampVisibile(bool is_visible);

        /**
         * Gets the theme for a given level
         * 
         * @returns Bool visibility
         */
        bool getIsTimestampVisibile();

        /**
         * Sets the length of the Level Name in the output
         * 
         * @throws invalid_argument Length must be between 1 and 8
         * 
         * @params Int number of characters desired
         */
        void setLevelNameLen(int len);

        /**
         * Gets the length of the Level Name in the output
         * 
         * @returns Int length in number of characters
         */
        int getLevelNameLen();

        /**
         * Applys the theme to a log
         * 
         * Will only apply a theme if the platform is unix like
         * Otherwise will return the given string, unmodified
         * 
         * @params Level the level of the log
         * @params std::string The string to be styled
         * 
         * @returns std::string the final log
         */
        std::string apply(Level l, std::string s);
    };
};

namespace mercury {
    /**
     * Implementation of a singleton logger
     *
     * The logger class supports 6 logging levels and the off level. In
     * Addition the output can be styled using the Theme class.
     */
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

#endif // MERCURY_HPP

#ifdef _WIN64
   #define THEME_SUPPORT false
#elif _WIN32
    #define THEME_SUPPORT false
#else
    #define THEME_SUPPORT true
#endif

namespace mercury {

    Vector2 Theme::getTrace() {
        return Theme::trace;
    };
    void Theme::setTrace(Vector2 v) {
        Theme::trace = v;
    };

    Vector2 Theme::getDebug() {
        return Theme::debug;
    };
    void Theme::setDebug(Vector2 v){
        Theme::debug = v;
    };

    Vector2 Theme::getInfo() {
        return Theme::info;
    };
    void Theme::setInfo(Vector2 v) {
        Theme::info = v;
    };

    Vector2 Theme::getWarn() {
        return Theme::warn;
    };
    void Theme::setWarn(Vector2 v) {
        Theme::warn = v;
    };

    Vector2 Theme::getCritical() {
        return Theme::critical;
    };
    void Theme::setCritical(Vector2 v) {
        Theme::critical = v;
    };

    Vector2 Theme::getError() {
        return Theme::error;
    };
    void Theme::setError(Vector2 v) {
        Theme::error = v;
    };

    void Theme::setSeperator(std::string s) {
        Theme::seperator = s;
    };

    std::string Theme::getSeperator() {
        return Theme::seperator;
    };

    Vector2 Theme::getLevelTheme(Level l) {
        Vector2 t;
        switch (l){
        case Level::trace:
            t = Theme::getTrace();
            break;
        case Level::debug:
            t = Theme::getDebug();
            break;
        case Level::info:
            t = Theme::getInfo();
            break;
        case Level::warn:
            t = Theme::getWarn();
            break;
        case Level::critical:
            t = Theme::getCritical();
            break;
        case Level::err:
            t = Theme::getError();
            break;
        default:
            t = Theme::getInfo();
            break;
        }
        return t;
    };

    void Theme::setIsTimestampVisibile(bool is_visible){
        Theme::is_timestamp_visible = is_visible;
    };

    bool Theme::getIsTimestampVisibile(){
        return Theme::is_timestamp_visible;
    };

    void Theme::setLevelNameLen(int len) {
        if (len > 8 || len < 1) {
            throw std::invalid_argument("Length must be between 1 and 8");
        } else {
            Theme::level_name_len = len;
        };
    };
    int Theme::getLevelNameLen() {
        return Theme::level_name_len;
    };

    std::string Theme::apply(Level l, std::string s) {
        std::string o;
        if (THEME_SUPPORT) {
            Vector2 t = Theme::getLevelTheme(l);
            o += "\033[";
            o += std::to_string(t.style) + ";";
            o += std::to_string(t.color) + "m";
            o += s;
            o += "\033[0m";
        } else {
            o = s;
        }
       
        return o;
    };  
}

namespace mercury {

    /*
    * PRIVATE
    */ 
   
    
    void Logger::log(Level level, std::string msg){
        if (Logger::getLevel() != Level::off) {
            /*
            * info = [ "INFO", "WARN", "CRITICAL"]
            * debug = info + [ "DEBUG" ]
            * trace = debug + [ "TRACE" ]
            * err => throws error and exits program
            * off => disables logging
            */ 
            if (Logger::inLevel(Logger::getLevel(), Level::err, level)) {
                std::cout << Logger::buildLog(level, msg) << std::endl;
            }
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

        if (t -> getIsTimestampVisibile()) {
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

    void Logger::setLevel(Level l) {
        Logger::level = l;
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
