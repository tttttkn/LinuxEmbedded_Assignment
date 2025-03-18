#ifndef CONNECTION_HANDLER
#define CONNECTION_HANDLER

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#include "../server/server.h"

#define MAXCONN 10
#define MAX_MSG_LEN 100

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;

typedef struct
{
    int sockfd;
    pthread_t thread_id;
    in_port_t port;
    char ip_address[INET_ADDRSTRLEN];
} connection_data_t;

/**
 * @brief Sends a message to a specified connection.
 *
 * This function sends a message to a connection identified by its connection ID.
 * If the message length exceeds the maximum allowed length, it logs an error.
 *
 * @param conn_id The ID of the connection to which the message will be sent.
 * @param msg The string message to be sent.
 */
void send_message(int conn_id, const char *msg);

/**
 * @brief Adds a new connection to the connection data list.
 *
 * This function adds the provided connection data to the list of active
 * connections. It increments the total number of connections.
 *
 * @param connection_data Pointer to the connection data to be added.
 */
void add_connection_data(const connection_data_t *connection_data);

/**
 * @brief Receives messages from a connection.
 *
 * This function continuously reads messages from the specified connection.
 * If the connection is lost, it terminates the connection and removes it
 * from the connection list.
 *
 * @param sender_data Pointer to the connection data of the sender.
 */
void receiving_message(const connection_data_t *sender_data);

/**
 * @brief Terminates a specific connection.
 *
 * This function closes the socket associated with the connection, cancels
 * the thread handling the connection, and removes the connection from the list.
 *
 * @param conn_id The ID of the connection to terminate.
 */
void terminate_connection(int conn_id);

/**
 * @brief Removes a connection from the connection list.
 *
 * This function removes the connection identified by its ID from the list
 * of active connections and shifts the remaining connections in the list.
 *
 * @param conn_id The ID of the connection to remove.
 */
void remove_connection_from_list(int conn_id);

/**
 * @brief Finds the connection ID by socket file descriptor.
 *
 * This function searches for a connection in the list using its socket file
 * descriptor and returns the corresponding connection ID.
 *
 * @param sockfd The socket file descriptor to search for.
 * @return The connection ID if found, or -1 if not found.
 */
int find_conn_id_by_sockfd(int sockfd);

/**
 * @brief Terminates all active connections.
 *
 * This function iterates through all active connections, terminates each one,
 * and clears the connection list.
 */
void terminate_all_connections();

/**
 * @brief Prints a message along with sender information.
 *
 * This function displays a message received from a specific sender, including
 * the sender's IP address and port.
 *
 * @param message The null-terminated string message to print.
 * @param sender_ip_address The IP address of the sender.
 * @param sender_port The port of the sender.
 */
void print_message(const char *message, const char *sender_ip_address, in_port_t sender_port);

/**
 * @brief Prints the list of active connections.
 *
 * This function displays all active connections, including their IP addresses
 * and ports, in a tabular format.
 *
 * @param connection_data Array of connection data structures.
 * @param connection_count The number of active connections.
 */
void print_list_connections(const connection_data_t connection_data[], const int connection_count);

extern connection_data_t conn_data[MAXCONN];

extern int nconn;

#endif // CONNECTION_HANDLER