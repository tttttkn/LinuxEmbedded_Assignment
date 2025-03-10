#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if ((argc != 2) || ((strcmp(argv[1], "EXIT_SUCCESS") != 0) && (strcmp(argv[1], "EXIT_FAILURE") != 0)))
    {
        printf("Usage: %s [EXIT_SUCCESS/EXIT_FAILURE]\n", argv[0]);
        return -1;
    }

    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        if ((strcmp(argv[1], "EXIT_SUCCESS") == 0))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("child exited, status = %d\n", WEXITSTATUS(status));
        }
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}