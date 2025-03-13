#include "socket.h"
#include <sys/time.h>

#define SA struct sockaddr

int create_socket()
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return sockfd;
    }
}

void listening_socket(int sockfd, struct sockaddr_in *servaddr, uint16_t max_clients)
{

    if ((bind(sockfd, (SA *)servaddr, sizeof(*servaddr))) != 0)
    {
        printf("\nSocket bind failed...\n");
        exit(EXIT_FAILURE);
    }

    if ((listen(sockfd, max_clients)) != 0)
    {
        printf("\nListen failed...\n");
        exit(EXIT_FAILURE);
    }
}

int connect_to_socket(int sockfd, struct sockaddr_in *servaddr)
{
    if (connect(sockfd, (SA *)servaddr, sizeof(*servaddr)) != 0)
    {
        printf("\nConnection to %s failed...\n", inet_ntoa(servaddr->sin_addr));
        printf("Please check the IP address and port number\n");
        return -1;
    }
    else
    {
        printf("\nConnected to %s\n", inet_ntoa(servaddr->sin_addr));
        return 0;
    }
}

void get_local_ip_address(char *buffer, size_t buflen)
{
    struct ifaddrs *ifaddr, *ifa;
    int family;

    if (getifaddrs(&ifaddr) == -1)
    {
        printf("\ngetifaddrs failed\n");
        return;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET)
        {
            if (strcmp(ifa->ifa_name, "lo") != 0) // Skip loopback interface
            {
                strncpy(buffer, inet_ntoa(((struct sockaddr_in *)ifa->ifa_addr)->sin_addr), buflen);
                break;
            }
        }
    }

    freeifaddrs(ifaddr);
}