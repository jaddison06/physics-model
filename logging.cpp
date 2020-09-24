#include "logging.h"

// very very simple logging

tm *getTime() {
    time_t rawTime = time(0);
    return localtime(&rawTime);
}

Logger::Logger() {

}

// set the sender of the logs
void Logger::setSender(std::string someApplication) {
    sender = someApplication;
}

// called by someone, hopefully, when they're finished with the logger
void Logger::destroy() {
    logfile.close();
}

// wrappers for various log levels
void Logger::debug(std::string msg) {
    writeLog("DEBUG", msg);
}

void Logger::info(std::string msg)
{
    writeLog("INFO", msg);
}

void Logger::warning(std::string msg)
{
    writeLog("WARNING", msg);
}


void Logger::writeLog(std::string level, std::string msg) {
    tm *logTime = getTime();
    logfile << logTime->tm_year << "-" << logTime->tm_mon << "-" << logTime->tm_mday << " " << logTime->tm_hour << ":" << logTime->tm_min << "-" << logTime->tm_sec << "   " << level << " (" << sender << ") " << msg << "\n\n";

}