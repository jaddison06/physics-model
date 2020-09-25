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
// you NEED to call this before you start logging otherwise bad things will happen
void initLogging() {
    startTime = getTime();
}

// called by both versions of the constructor
void Logger::setup(std::string someApplication) {

    // create the logs folder, if it already exists this will hopefully just fail silently (?)
    std::filesystem::create_directories("./logs/");

    logfile.open("./logs/" + formatTime(startTime));
    
    setSender(someApplication);
}

// constructors
Logger::Logger(std::string someApplication) {
    setup(someApplication);
}

Logger::Logger() {
    setup("");
}

// set the sender of the logs
//
// you can also do this via the constructor, I recommend
// inherited classes use setSender but standalones can be implicit
void Logger::setSender(std::string someApplication) {
    sender = someApplication;
}

// set a unique ID if you're gonna have more than one 
// of the same class
//
// this one can't be done from the constructor. this is probably a design choice
void Logger::setID(std::string someID) {
    ID = someID;
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

    // make id look slightly prettier
    std::string fmtID = "";
    if (ID != "") {
        fmtID = " " + ID;
    }

    logfile << formatTime(logTime) << "   " << level << " (" << sender << fmtID << ") " << msg << "\n\n";

}