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

/**
 * @brief Creates a new socket.
 *
 * This function creates a new socket using the `socket()` system call with
 * the `AF_INET` address family and `SOCK_STREAM` type for TCP communication.
 *
 * @return Returns the file descriptor of the created socket, or -1 if the
 * socket creation fails.
 */
int create_socket();

/**
 * @brief Configures a socket to listen for incoming connections.
 *
 * This function binds the socket to the specified address and port, and
 * configures it to listen for incoming connections with a specified maximum
 * number of clients.
 *
 * @param sockfd The file descriptor of the socket to configure.
 * @param servaddr Pointer to the `sockaddr_in` structure containing the
 * server's address and port.
 * @param max_clients The maximum number of clients that can connect to the
 * socket.
 * @return Returns 0 on success, or -1 if binding or listening fails.
 */
int listening_socket(int sockfd, struct sockaddr_in *servaddr, uint16_t max_clients);

/**
 * @brief Connects a socket to a remote server.
 *
 * This function attempts to connect the specified socket to a remote server
 * using the provided address and port.
 *
 * @param sockfd The file descriptor of the socket to connect.
 * @param servaddr Pointer to the `sockaddr_in` structure containing the
 * server's address and port.
 * @return Returns 0 on success, or -1 if the connection fails.
 */
int connect_to_socket(int sockfd, struct sockaddr_in *servaddr);

/**
 * @brief Retrieves the local IP address of the machine.
 *
 * This function retrieves the local IP address of the machine, excluding
 * the loopback interface, and stores it in the provided buffer.
 *
 * @param buffer Pointer to the buffer where the IP address will be stored.
 * @param buflen The size of the buffer.
 */
void get_local_ip_address(char *buffer, size_t buflen);

#endif