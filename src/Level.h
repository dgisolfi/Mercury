/**
 * @file Level.h
 *
 * @brief Logging Levels for Mecury
 *
 * @author Daniel Nicolas Gisolfi
 * Contact: Daniel.Gisolfi1@marist.edu
 *
 */

#define LEVEL_TRACE 0
#define LEVEL_DEBUG 1
#define LEVEL_INFO 2
#define LEVEL_WARN 3
#define LEVEL_ERR 4
#define LEVEL_CRITICAL 5
#define LEVEL_OFF 6


namespace mercury {
    enum Level {
        trace = LEVEL_TRACE,
        debug = LEVEL_DEBUG,
        info = LEVEL_INFO,
        warn = LEVEL_WARN,
        err = LEVEL_ERR,
        critical = LEVEL_CRITICAL,
        off = LEVEL_OFF
    };
    const std::string level_names[7] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL", "OFF"};
};
