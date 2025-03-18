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

void send_message(int conn_id, const char *msg);

void add_connection_data(const connection_data_t *connection_data);

void receiving_message(const connection_data_t *sender_data);

void terminate_connection(int conn_id);

void remove_connection_from_list(int conn_id);

int find_conn_id_by_sockfd(int sockfd);

void terminate_all_connections();

void print_message(const char *message, const char *sender_ip_address, in_port_t sender_port);

void print_list_connections(const connection_data_t connection_data[], const int connection_count);

extern connection_data_t conn_data[MAXCONN];

extern int nconn;

#endif // CONNECTION_HANDLER