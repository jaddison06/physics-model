#include "logging.h"

// very very simple logging

tm *getTime() {
    time_t rawTime = time(0);
    return localtime(&rawTime);
}

std::string formatTime(tm *someTime) {
    return someTime->tm_year + "-" + someTime->tm_mon + "-" + someTime->tm_mday + " " + someTime->tm_hour + ":" + someTime->tm_min + ":" + someTime->tm_sec;
}

tm *startTime = getTime();

Logger::Logger() {
    std::ofstream logfile(formatTime(startTime));
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
    logfile << formatTime(logTime) << "   " << level << " (" << sender << ") " << msg << "\n\n";

}