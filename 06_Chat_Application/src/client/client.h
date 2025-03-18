#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include <stdio.h>

#include "../connection/socket.h"
#include "../connection/connection_handler.h"

void connect_to_server(char ip[], in_port_t port);

int is_valid_server(char ip[], in_port_t port);

#endif