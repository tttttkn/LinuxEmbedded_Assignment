#include "socket.h"
#include <sys/time.h>

#define SA struct sockaddr

int create_socket()
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("\nSocket creation failed");
    }
    return sockfd;
}

int listening_socket(int sockfd, struct sockaddr_in *servaddr, uint16_t max_clients)
{

    if ((bind(sockfd, (SA *)servaddr, sizeof(*servaddr))) != 0)
    {
        perror("\nbind failed");
        return -1;
    }

    if ((listen(sockfd, max_clients)) != 0)
    {
        perror("\nlisten failed");
        return -1;
    }

    return 0;
}

int connect_to_socket(int sockfd, struct sockaddr_in *servaddr)
{
    if (connect(sockfd, (SA *)servaddr, sizeof(*servaddr)) != 0)
    {
        // perror("\nConnection to %s failed...\n", inet_ntoa(servaddr->sin_addr));
        perror("\nConnection to server failed");
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
        perror("\ngetifaddrs failed\n");
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