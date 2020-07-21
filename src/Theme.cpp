#include "theme.hpp" 


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
