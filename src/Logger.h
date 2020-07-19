#pragma once

namespace mercury {
    class Logger {
        
    private:

        Logger() {}

        // The single instance
        static Logger instance;
        bool level;
        bool verbose;
    
        void log(std::string msg);

    public:
        // mark the copy constructor to delete
        Logger(const Logger&) = delete;

        static Logger& get();

        void setLevel();
        void getLevel();

        void trace();
        void debug();
        void info();
        void warn();
        void error();
        void critical();
    };
};

