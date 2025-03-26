#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <stdio.h>

#include "../Socket.hpp"
#include "TCPConfig.hpp"

#define SA struct sockaddr


class TCPSocket: public SocketInterface
{
    public:
        int socketOpen(struct sockaddr_in *servaddr, int *sockfd) override;

};



#endif //TCPSOCKET_HPP