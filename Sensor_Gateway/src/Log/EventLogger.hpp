#ifndef EVENT_LOGGER_HPP
#define EVENT_LOGGER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>

#define FIFO_FILE "/tmp/logFifo"

class EventLogger
{
public:
    // Constructor and Destructor
    EventLogger();
    ~EventLogger();

    void init(const std::string &logFilePath);
    typedef enum eLogSource
    {
        CONNECTION_MANAGER = 0,
        DATA_MANAGER,
        STORAGE_MANAGER,
        EVENT_LOGGER,
        SOURCE_UNKNOWN
    } LogSource;

    void openFIFO(int mode);
    void logEvent(const std::string &eventMessage, LogSource source = SOURCE_UNKNOWN);
    void logError(const std::string &errorMessage);
    void logWarning(const std::string &warningMessage);
    void onStart();
    void closeFifo();

private:
    int fifoFd;
    int fd;
    unsigned int logCount = 0;
    pthread_mutex_t eventLoggerMutex = PTHREAD_MUTEX_INITIALIZER;
};

extern EventLogger eventLogger;

#endif // EVENT_LOGGER_HPP
