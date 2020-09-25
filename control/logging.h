#pragma once

#include <string>
#include <fstream>
#include <ctime>
#include <iostream>
#include <filesystem>

class Logger {
    public:
        Logger(std::string someApplication);

        void setSender(std::string someApplication);
        void setID(std::string someID);

        void destroy();

        void debug(std::string msg);
        void info(std::string msg);
        void warning(std::string msg);
    
    private:
        std::string sender;
        std::string ID;
        std::ofstream logfile;
        void writeLog(std::string level, std::string msg);
};