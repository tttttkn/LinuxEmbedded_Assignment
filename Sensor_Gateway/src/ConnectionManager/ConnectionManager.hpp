#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <thread>
#include <memory>
#include <sys/epoll.h>

#include "../Socket/TCPSocket.hpp"
#include "../SharedData/SharedData.hpp"

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
    void removeSensorNode(int connfd);
    void onReceivingSensorData();
    void handleSensorNodeDisconnection(int connfd);
    void handleSensorNodeError(int connfd);

private:
    struct sockaddr_in _servaddr{0};
    int _port{0};
    ISocket *_iSocket{nullptr};
    int epfd{0};
};

extern ConnectionManager connMgr;

#endif