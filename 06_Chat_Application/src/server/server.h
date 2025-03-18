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

void thread_cli_handler(void *cli_data);

void *server_start_listening();

void print_app_port();

void print_server_ip();

void close_server();

void setup_server_socket();

int accept_client_connection(struct sockaddr_in *cli);

void handle_client_connection(int connfd, struct sockaddr_in *cli);

extern in_port_t APP_PORT;

extern int is_server_listening;

extern pthread_t server_thread;

extern pthread_mutex_t server_started_mutex;

extern pthread_cond_t server_started_cond;

#endif