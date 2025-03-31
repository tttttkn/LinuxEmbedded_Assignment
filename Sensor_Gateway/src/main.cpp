#include <iostream>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <thread>

#include "ConnectionManager/ConnectionManager.hpp"
#include "Log/EventLogger.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\nUsage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (atoi(argv[1]) < 1024 || atoi(argv[1]) > 65535)
    {
        printf("\nInvalid port number: %d\n", atoi(argv[1]));
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    pid_t pid = fork();

    switch (pid)
    {
    case 0: // Child process
    {
        // EventLogger eventLogger("gateway.log");
        break;
    }
    case -1: // Fork failed
        break;
    default:
    {
        std::thread connMgrThread(&ConnectionManager::onListeningToSensorNode, &connMgr);

        break;
    }
    }

    return 0;
}
