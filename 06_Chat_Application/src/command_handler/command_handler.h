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

/**
 * @brief Reads input from the user and stores it in the provided buffer.
 *
 * This function prompts the user to enter a command, reads the input from
 * standard input, and stores it in the provided buffer. The input is
 * null-terminated, and the trailing newline character is removed.
 *
 * @param buff Pointer to the buffer where the input will be stored.
 */
void get_input_from_user(char *buff);

/**
 * @brief Handles the user input and executes the corresponding command.
 *
 * This function continuously listens for user input while the server is
 * running. It reads the input, parses it, and executes the corresponding
 * command using the `command_parser` function.
 */
void command_handler();

/**
 * @brief Parses the user input and executes the corresponding command.
 *
 * This function takes the user input, tokenizes it to extract the command
 * and its arguments, and executes the appropriate functionality. Supported
 * commands include `connect`, `send`, `list`, `help`, `myip`, `myport`,
 * `terminate`, and `exit`.
 *
 * @param command_input The user input to parse and execute.
 */
void command_parser(char *command_input);

/**
 * @brief Prints the list of available commands.
 *
 * This function displays a help menu with a list of all supported commands
 * and their descriptions, providing guidance to the user on how to use the
 * chat application.
 */
void print_help();

extern pthread_t command_handler_thread;

#endif