#include "TCPSocket.hpp"

ISocket::SocketStatus TCPSocket::socketOpen(struct sockaddr_in *servaddr, int port)
{
    SocketStatus status{SOCKET_SUCCESS};

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1)
    {
        status = SOCKET_CREATE_FAILED;
    }

    // Initialize socket structure
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr->sin_port = htons(port);

    if ((bind(_sockfd, (SA *)servaddr, sizeof(*servaddr))) != 0)
    {
        status = SOCKET_BIND_FAILED;
    }

    //
    if ((listen(_sockfd, TCP_MAX_CLIENTS)) != 0)
    {
        status = SOCKET_LISTEN_FAILED;
    }

    return status;
}

int TCPSocket::sendData(int sockfd, const void *buffer, int length)
{
    return write(sockfd, buffer, length);
}

int TCPSocket::receiveData(int sockfd, void *buffer, int length)
{
    return read(sockfd, buffer, length);
}

int TCPSocket::onAcceptClient(struct sockaddr_in *cliaddr, socklen_t *len)
{
    return accept(_sockfd, (SA *)cliaddr, len);
}

TCPSocket tcpSocket;