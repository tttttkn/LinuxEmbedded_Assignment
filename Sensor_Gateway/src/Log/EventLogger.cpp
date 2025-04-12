#include "EventLogger.hpp"
#include <string.h>

EventLogger::EventLogger()
{
}

void EventLogger::init(const std::string &logFilePath)
{
    // Check if the FIFO file was created successfully
    if (mkfifo(logFilePath.c_str(), 0666) == -1)
    {
        std::cerr << "Error creating FIFO file: " << logFilePath << std::endl;
        return;
    }
    // std::cout << "FIFO file created successfully: " << logFilePath << std::endl;

    fd = open("gateway.log", O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

EventLogger::~EventLogger()
{
    // Close the FIFO file
    // close(fifoFd);
    // Remove the FIFO file
    printf("Removing FIFO file: %s\n", FIFO_FILE);
    if (unlink(FIFO_FILE) == -1)
    {
        perror("Error removing FIFO file");
    }
    else
    {
        std::cout << "FIFO file removed successfully." << std::endl;
    }
}

void EventLogger::logEvent(const std::string &eventMessage, LogSource source)
{
    std::string sourceStr;
    switch (source)
    {
    case CONNECTION_MANAGER:
        sourceStr = "Connection Manager";
        break;
    case DATA_MANAGER:
        sourceStr = "Data Manager";
        break;
    case STORAGE_MANAGER:
        sourceStr = "Storage Manager";
        break;
    case EVENT_LOGGER:
        sourceStr = "Event Logger";
        break;
    default:
        sourceStr = "Unknown Source";
        break;
    }

    logCount++;
    std::string logMessage = "[" + std::to_string(logCount) + "] " + "[" + sourceStr + "]: " + eventMessage + "\n";

    // Write the log message to the FIFO
    if (fifoFd != -1)
    {
        ssize_t bytesWritten = write(fifoFd, logMessage.c_str(), logMessage.size());
        if (bytesWritten == -1)
        {
            perror("Error writing to FIFO");
        }
    }
    else
    {
        std::cerr << "FIFO file is not open for writing." << std::endl;
    }
}

void EventLogger::closeFifo()
{
    close(fifoFd);
}

void EventLogger::onStart()
{
    while (1)
    {
        // Wait for a new log message
        char logMessage[1024];
        logMessage[0] = '\0'; // Initialize the buffer
        // std::cout << "Waiting for log message..." << std::endl;
        read(fifoFd, &logMessage, sizeof(logMessage));
        
        if (logMessage[0] == '\0')
        {
            std::cerr << "Received empty log message" << std::endl;
            continue;
        }
        // else
        // {
        //     std::cout << "Log message received: " << logMessage << std::endl;
        // }

        logMessage[sizeof(logMessage) - 1] = '\0';

        // Write the log message to the file
        ssize_t bytesWritten = write(fd, logMessage, strlen(logMessage));
        if (bytesWritten == -1)
        {
            perror("Error writing to log file");
        }
        // else
        // {
        //     std::cout << "Log message written to file: " << logMessage;
        // }
    }
}

void EventLogger::openFIFO(int mode)
{
    fifoFd = open(FIFO_FILE, mode);
    if (fifoFd == -1)
    {
        perror("Error opening FIFO file");
        return;
    }
    else
    {
        std::cout << "FIFO file opened successfully: " << fifoFd << std::endl;
    }
}

EventLogger eventLogger;