#include <stdio.h>
#include <pthread.h>

#include "command_handler/command_handler.h"
#include "server/server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\nUsage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (atoi(argv[1]) < 1024 || atoi(argv[1]) > 65535)
    {
        printf("\nInvalid port number: %d\n", atoi(argv[1]));
        exit(EXIT_FAILURE);
    }

    APP_PORT = atoi(argv[1]);

    print_help();

    pthread_create(&server_thread, NULL, server_start_listening, NULL);

    pthread_mutex_lock(&server_started_mutex);
    pthread_cond_wait(&server_started_cond, &server_started_mutex);
    pthread_mutex_unlock(&server_started_mutex);

    command_handler();

    pthread_join(server_thread, NULL); // Wait for the server thread to finish

    return 0;
}