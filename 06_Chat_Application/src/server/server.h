#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h> // inet_ntoa()

#include "../connection/socket.h"
#include "../connection/connection_handler.h"

#define SA struct sockaddr
#define MAXNCLI 5

/**
 * @brief Handles communication with a specific client in a separate thread.
 *
 * This function is executed in a detached thread to handle communication
 * with a specific client. It adds the client connection to the connection
 * list and processes incoming messages.
 *
 * @param cli_data Pointer to the connection data of the client.
 */
void thread_cli_handler(void *cli_data);

/**
 * @brief Starts the server and listens for incoming client connections.
 *
 * This function sets up the server socket, accepts incoming client connections,
 * and handles them in separate threads. It runs in a loop to continuously
 * accept new connections.
 *
 * @return A pointer to the server thread function.
 */
void *server_start_listening();

/**
 * @brief Prints the application's listening port.
 *
 * This function displays the port number on which the server is currently
 * listening for incoming connections.
 */
void print_app_port();

/**
 * @brief Prints the server's local IP address.
 *
 * This function retrieves and displays the local IP address of the server,
 * excluding the loopback interface.
 */
void print_server_ip();

/**
 * @brief Closes the server and terminates all active connections.
 *
 * This function shuts down the server by closing the server socket, terminating
 * all active client connections, and stopping the server thread.
 */
void close_server();

/**
 * @brief Sets up the server socket for listening.
 *
 * This function creates a socket, binds it to the specified port, and configures
 * it to listen for incoming client connections. It also signals that the server
 * is ready to accept connections.
 */
void setup_server_socket();

/**
 * @brief Accepts an incoming client connection.
 *
 * This function accepts a new client connection on the server socket and
 * retrieves the client's address information.
 *
 * @param cli Pointer to a `sockaddr_in` structure to store the client's address.
 * @return The file descriptor of the accepted client connection, or -1 if the
 * connection fails.
 */
int accept_client_connection(struct sockaddr_in *cli);

/**
 * @brief Handles a newly accepted client connection.
 *
 * This function initializes the connection data for a new client, retrieves
 * the client's application port, and creates a thread to handle communication
 * with the client.
 *
 * @param connfd The file descriptor of the accepted client connection.
 * @param cli Pointer to the `sockaddr_in` structure containing the client's address.
 */
void handle_client_connection(int connfd, struct sockaddr_in *cli);

extern in_port_t APP_PORT; /** The port number on which the server listens. */

extern int is_server_listening; /** Flag indicating whether the server is currently listening. */

extern pthread_t server_thread; /** The thread handling the server's main listening loop. */

extern pthread_mutex_t server_started_mutex; /** Mutex to synchronize server startup. */

extern pthread_cond_t server_started_cond; /** Condition variable to signal server startup. */

#endif