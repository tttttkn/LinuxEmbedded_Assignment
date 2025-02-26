#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

void signal_handler(int sig)
{

    if (sig == SIGINT)
    {
        printf("SIGINT received.\n");
    }
    else if (sig == SIGTERM)
    {
        printf("SIGTERM received. Exiting...\n");
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    fd_set readfds;
    int retval;
    char buffer[256];

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                printf("Input: %s", buffer);
            }
        }
    }

    return 0;
}