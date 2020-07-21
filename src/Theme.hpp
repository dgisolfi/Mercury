#pragma once
#include <string> 
#include <stdexcept>
#include "level.hpp"


#ifndef MERCURY_THEME_HPP
#define MERCURY_THEME_HPP

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

#endif // MERCURY_THEME_HPP
