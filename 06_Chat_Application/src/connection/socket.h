#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // inet_ntoa()
#include <unistd.h>    // read(), write(), close()
#include <stdio.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <pthread.h>

int create_socket();

int listening_socket(int sockfd, struct sockaddr_in *servaddr, uint16_t max_clients);

int connect_to_socket(int sockfd, struct sockaddr_in *servaddr);

void get_local_ip_address(char *buffer, size_t buflen);

#endif