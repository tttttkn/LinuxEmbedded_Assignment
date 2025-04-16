#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <thread>
#include <memory>
#include <sys/epoll.h>
#include <signal.h>
#include <map>

#include "../Socket/TCPSocket.hpp"
#include "../SharedData/SharedData.hpp"
#include "../Log/EventLogger.hpp"

#define MAX_EVENTS 10

class ConnectionManager
{
public:
    // Constructor and Destructor
    ConnectionManager() = default;
    // explicit ConnectionManager(ISocket &socketDomain);
    ~ConnectionManager() = default;

    void init(ISocket *socketDomain, int port);
    void onListeningToSensorNode();
    void onStart();
    void addSensorNode(int connfd);
    void onReceivingSensorData();
    void handleSensorNodeDisconnection(int connfd);

    static void signalHandler(int sensorID)
    {
        std::string logMessage = "A sensor node with " + std::to_string(sensorID) + " has opened a new connection";
        eventLogger.logEvent(logMessage, EventLogger::CONNECTION_MANAGER);
        logMessage.clear();
    }

private:
    struct sockaddr_in _servaddr{0};
    int _port{0};
    ISocket *_iSocket{nullptr};
    int epfd{0};

    std::map<int, int> _connfdToSensorID; // Map to store sensor node connections
};

extern ConnectionManager connMgr;

#endif