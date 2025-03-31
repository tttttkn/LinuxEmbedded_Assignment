#include "EventLogger.hpp"

EventLogger::EventLogger(const std::string &logFilePath)
{
    mkfifo(logFilePath.c_str(), 0666);
}

EventLogger::~EventLogger()
{
}