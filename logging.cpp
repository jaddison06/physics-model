#include "logging.h"

// very very simple logging

// get a tm struct
tm *getTime() {
    time_t rawTime = time(0);
    return localtime(&rawTime);
}

// take a tm and return a beautified string
std::string formatTime(tm *someTime) {
    return someTime->tm_year + "-" + someTime->tm_mon + "-" + someTime->tm_mday + " " + someTime->tm_hour + ":" + someTime->tm_min + ":" + someTime->tm_sec;
}

// will this run? who knows
tm *startTime = getTime();

// constructor, atm just configures the ostream
Logger::Logger() {
    std::ofstream logfile("./logs/"+formatTime(startTime));
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


// write a log entry
// does "logfile << something" write or append? let's find out
void Logger::writeLog(std::string level, std::string msg) {
    tm *logTime = getTime();
    logfile << formatTime(logTime) << "   " << level << " (" << sender << ") " << msg << "\n\n";

}