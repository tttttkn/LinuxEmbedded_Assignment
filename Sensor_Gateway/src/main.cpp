#include <iostream>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <thread>

#include "ConnectionManager/ConnectionManager.hpp"
#include "DataManager/DataManager.hpp"
#include "Log/EventLogger.hpp"
#include "StorageManager/StorageManager.hpp"

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

    eventLogger.init(FIFO_FILE);

    pid_t pid = fork();

    switch (pid)
    {
    case 0: // Child process
    {
        eventLogger.openFIFO(O_RDONLY);
        eventLogger.onStart();
        break;
    }
    case -1: // Fork failed
        break;
    default:
    {
        eventLogger.openFIFO(O_WRONLY);
        TCPSocket tcpSocket;
        connMgr.init(&tcpSocket, port);
        dataMgr.init();
        storageMgr.init();

        std::thread connMgrThread(&ConnectionManager::onStart, &connMgr);
        std::thread dataMgrThread(&DataManager::processSensorData, &dataMgr);
        std::thread storageMgrThread(&StorageManager::storeSensorData, &storageMgr);
        connMgrThread.join();
        dataMgrThread.join();
        storageMgrThread.join();
        break;
    }
    }

    return 0;
}
