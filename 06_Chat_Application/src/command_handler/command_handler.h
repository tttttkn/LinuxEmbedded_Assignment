#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../client/client.h"
#include "../connection/connection_handler.h"
#include "../server/server.h"

#define MAX_INPUT_SIZE 1024

void get_input_from_user(char *buff);

void *command_handler();

void command_parser(char *command_input);

void print_help();

#endif