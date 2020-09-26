#pragma once

#include <string>
#include <fstream>
#include <ctime>
#include <iostream>
#include <filesystem>

void initLogging();

class Logger {
    public:
        Logger(std::string someApplication);
        Logger();

        void setSender(std::string someApplication);
        void setID(std::string someID);

        void destroy();

        void debug(std::string msg);
        void info(std::string msg);
        void warning(std::string msg);
    
    private:
        void setup(std::string someApplication);

        std::string sender;
        std::string ID;

        std::string fmtLog(std::string *level, std::string *msg);
        void writeLog(std::string level, std::string *msg);
};