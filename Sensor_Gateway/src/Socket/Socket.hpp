#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>

class ISocket
{
public:
    typedef enum eSocketStatus
    {
        SOCKET_SUCCESS = 0,
        SOCKET_CREATE_FAILED,
        SOCKET_BIND_FAILED,
        SOCKET_LISTEN_FAILED,
        SOCKET_ACCEPT_FAILED,
        SOCKET_CLOSE_FAILED
    } SocketStatus;

    virtual SocketStatus socketOpen(struct sockaddr_in *servaddr, int port) = 0;
    virtual int sendData(int sockfd, const void *buffer, int length) = 0;
    virtual int receiveData(int sockfd, void *buffer, int length) = 0;
};
;

#endif