#include "ConnectionManager.hpp"

// ConnectionManager::ConnectionManager(ISocket &socketDomain) : _iSocket{&socketDomain}
// {
// }

void ConnectionManager::init(ISocket *socketDomain, int port)
{
    if (_iSocket == nullptr)
    {
        _iSocket = socketDomain;
        if (_iSocket->socketOpen(&_servaddr, port) != ISocket::SOCKET_SUCCESS)
        {
            // Handle error
            return;
        }
    }
    _port = port;

    epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd == -1)
    {
        eventLogger.logEvent("Failed to create epoll instance", EventLogger::CONNECTION_MANAGER);
        return;
    }
}

void ConnectionManager::onListeningToSensorNode()
{

    int connfd;
    socklen_t len = sizeof(_servaddr);
    struct sockaddr_in cliaddr{0};

    TCPSocket *tcpSocket = static_cast<TCPSocket *>(_iSocket);
    while (1)
    {
        connfd = tcpSocket->onAcceptClient(&cliaddr, &len);
        if (connfd < 0)
        {
            // Handle error
            continue;
        }
        addSensorNode(connfd);
    }
}

void ConnectionManager::addSensorNode(int connfd)
{
    struct epoll_event ev;
    ev.events = EPOLLIN; // Set the event type to EPOLLIN
    ev.data.fd = connfd; // Set the file descriptor to monitor

    // Add the file descriptor to the epoll instance
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev) == -1)
    {
        // Handle error
        return;
    }
    // Log the new connection
    // eventLogger.logEvent("A sensor node with"+ std::to_string()+ has opened a new connection1, EventLogger::CONNECTION_MANAGER);
}

void ConnectionManager::onReceivingSensorData()
{
    // Start the epoll loop
    while (true)
    {
        struct epoll_event events[MAX_EVENTS];
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);

        if (nfds == -1)
        {
            // Handle error
            continue;
        }

        for (int i = 0; i < nfds; ++i)
        {
            if (events[i].events & EPOLLIN)
            {

                // Handle incoming data
                printf("Sensor node %d is sending data...\n", events[i].data.fd);
                SensorData data;
                if (_iSocket->receiveData(events[i].data.fd, &data, sizeof(data)) > 0)
                {
                    if (_connfdToSensorID.find(events[i].data.fd) == _connfdToSensorID.end())
                    {
                        // Associate connfd with sensorID
                        _connfdToSensorID[events[i].data.fd] = data.sensorId;
                        std::string logMessage = "A sensor node with " + std::to_string(data.sensorId) + " has opened a new connection";
                        eventLogger.logEvent(logMessage, EventLogger::CONNECTION_MANAGER);
                        logMessage.clear();
                    }
                    pthread_mutex_lock(&sharedDataMutex);
                    // Process the received data
                    sensorDataQueue.push(data);

                    pthread_mutex_unlock(&sharedDataMutex);
                }
                else
                {
                    // Handle disconnection or error
                    handleSensorNodeDisconnection(events[i].data.fd);
                }
            }
        }
    }
}

void ConnectionManager::onStart()
{
    // Create a thread to listen for incoming connections
    std::thread connMgrThread(&ConnectionManager::onListeningToSensorNode, this);

    this->onReceivingSensorData();
}

void ConnectionManager::handleSensorNodeDisconnection(int connfd)
{
    // Remove the file descriptor from the epoll instance
    if (epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, nullptr) == -1)
    {
        // Handle error
    }
    close(connfd);

    // Log the disconnection
    std::string logMessage = "A sensor node with " + std::to_string(_connfdToSensorID[connfd]) + " has closed the connection";
    eventLogger.logEvent(logMessage, EventLogger::CONNECTION_MANAGER);
    logMessage.clear();

    _connfdToSensorID.erase(connfd); // Remove the connection from the map
}

ConnectionManager connMgr;