#include "TCPSocket.hpp"

int TCPSocket::socketOpen(struct sockaddr_in *servaddr, int *sockfd) 
{
    int status{TCP_SUCCESS};

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1)
    {
        status = TCP_CREATE_FAILED;
    }

    if ((bind(*sockfd, (SA *)servaddr, sizeof(servaddr))) != 0)
    {
        status = TCP_BIND_FAILED;
    }

    if ((listen(*sockfd, TCP_MAX_CLIENTS)) != 0)
    {
        status = TCP_LISTEN_FAILED;
    }

    return status;
}