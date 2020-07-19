#include <iostream>
#include "Logger.h"

namespace mercury {

    /*
    * PRIVATE
    */ 
    bool level = false;
    bool verbose = false;

    void Logger::log(std::string msg){

        std::cout << msg << std::endl;
    };
    
    
    /*
    * PUBLIC
    */
    // Create the single instance of the logger
    Logger Logger::instance;
   
    Logger& Logger::get() {
        return instance;
    };

    bool getLevel() {
        return level;
    };

    void setLevel() {

    };

    // void trace();
    // void debug();
    // void info();
    // void warn();
    // void error();
    // void critical();
};