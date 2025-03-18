#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include <stdio.h>

#include "../connection/socket.h"
#include "../connection/connection_handler.h"

/**
 * @brief Establishes a connection to the server using the provided IP address and port.
 *
 * This function creates a socket, validates the server's IP address and port,
 * and establishes a connection to the server. It also creates a thread to handle
 * communication with the server and adds the connection to the connection list.
 *
 * @param ip The IP address of the server to connect to.
 * @param port The port number of the server to connect to.
 */
void connect_to_server(char ip[], in_port_t port);

/**
 * @brief Handles communication with the server in a separate thread.
 *
 * This function is executed in a separate thread to manage communication
 * with the server. It processes incoming messages and handles disconnection
 * scenarios.
 *
 * @param arg Pointer to the arguments required for the thread.
 * @return NULL when the thread exits.
 */
void thread_serv_handler(void *arg);

/**
 * @brief Validates the server's IP address and port.
 *
 * This function checks if the provided IP address and port are valid. It ensures
 * that the IP address is properly formatted, the port is within the valid range,
 * and the application is not attempting to connect to itself or an already
 * connected server.
 *
 * @param ip The IP address of the server to validate.
 * @param port The port number of the server to validate.
 * @return Returns -1 if the server is invalid, 0 otherwise.
 */
int is_valid_server(char ip[], in_port_t port);

#endif