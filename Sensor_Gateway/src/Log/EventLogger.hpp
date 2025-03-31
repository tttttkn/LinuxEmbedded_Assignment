#ifndef EVENT_LOGGER_HPP
#define EVENT_LOGGER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

class EventLogger
{
public:
    // Constructor and Destructor
    EventLogger(const std::string &logFilePath);
    ~EventLogger();

    typedef enum eLogSource
    {
        CONNECTION_MANAGER = 0,
        DATA_MANAGER,
        STORAGE_MANAGER,
        EVENT_LOGGER,
        SOURCE_UNKNOWN
    } LogSource;

    void logEvent(const std::string &eventMessage);
    void logError(const std::string &errorMessage);
    void logWarning(const std::string &warningMessage);
};

#endif // EVENT_LOGGER_HPP
