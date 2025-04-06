#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <stdio.h>
#include <unistd.h>

#include "Socket.hpp"
#include "TCPConfig.hpp"

#define SA struct sockaddr

class TCPSocket : public ISocket
{
public:
    // Constructor and Destructor
    TCPSocket() = default;
    ~TCPSocket() = default;

    // ISocket interface methods
    SocketStatus socketOpen(struct sockaddr_in *servaddr, int port) override;
    int sendData(int sockfd, const void *buffer, int length) override;
    int receiveData(int sockfd, void *buffer, int length) override;

    int onAcceptClient(struct sockaddr_in *cliaddr, socklen_t *len);
    int onClose(int connfd);

private:
    int _sockfd{0};
};

#endif // TCPSOCKET_HPP