#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>

class SocketInterface
{
    public:
        virtual int socketOpen(struct sockaddr_in *servaddr, int *sockfd) = 0;
};

#endif