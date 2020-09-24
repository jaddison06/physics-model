#include "logging.h"

// very very simple logging

// global ting
tm *startTime;

// get a tm struct
tm *getTime() {
    time_t rawTime = time(0);
    return localtime(&rawTime);
}

// take a tm and return a beautified string
std::string formatTime(tm *someTime) {
    return std::to_string(someTime->tm_year + 1900) + "-" + std::to_string(someTime->tm_mon) + "-" + std::to_string(someTime->tm_mday) + " " + std::to_string(someTime->tm_hour) + ":" + std::to_string(someTime->tm_min) + ":" + std::to_string(someTime->tm_sec);
}


// i'm used to interpreted langs so i find it difficult to put this before the getTime() definition
void initLogging() {
    startTime = getTime();
}

// constructor, atm just configures the ostream
Logger::Logger() {
    // create the logs folder, if it already exists this will hopefully just fail silently (?)
    std::filesystem::create_directories("./logs/");

    logfile.open("./logs/"+formatTime(startTime));
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