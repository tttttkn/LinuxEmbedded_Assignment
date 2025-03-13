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
void server_start_listening();
void print_server_port();
void print_server_ip();

extern in_port_t SERV_PORT;

#endif