/**
 * @file Colors.h
 *
 * @brief Theme support for Mecury
 *
 * @author Daniel Nicolas Gisolfi
 * Contact: Daniel.Gisolfi1@marist.edu
 *
 */

#pragma once
#include <string> 
#include <iostream>
#include "Level.h"

namespace mercury {

    struct Vector2 {
        int color;
        int style;
    };

    class Theme {
    private:
        Vector2 trace;
        Vector2 debug;
        Vector2 info;
        Vector2 warn;
        Vector2 critical;
        Vector2 error;
        std::string seperator;
        bool is_timestamp_enabled;
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
            is_timestamp_enabled(true),
            level_name_len(4)
        {}
        ~Theme(){}

        Vector2 getTrace();
        void setTrace(Vector2 v);

        Vector2 getDebug();
        void setDebug(Vector2 v);

        Vector2 getInfo();
        void setInfo(Vector2 v);

        Vector2 getWarn();
        void setWarn(Vector2 v);

        Vector2 getCritical();
        void setCritical(Vector2 v);

        Vector2 getError();
        void setError(Vector2 v);

        void setSeperator(std::string s);
        std::string getSeperator();

        Vector2 getLevelTheme(Level l);
    
        void setIsTimestampEnabled(bool is_enabled);
        bool getIsTimestampEnabled();

        void setLevelNameLen(int len);
        int getLevelNameLen();

        std::string apply(Level l, std::string s);
    };
};