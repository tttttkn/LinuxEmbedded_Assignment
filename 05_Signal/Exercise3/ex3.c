#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int counter = 0;

void signalHandler(int sig)
{
    counter++;
    printf("Received signal from parent\n");
    if (counter > 5)
    {
        exit(EXIT_SUCCESS);
    }
}

void waitHandler(int sig)
{
    wait(NULL);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        signal(SIGUSR1, signalHandler);
        while (1)
            ;
    }
    else if (pid > 0)
    {
        for (int i = 0; i < 5; i++)
        {
            sleep(2);
            kill(pid, SIGUSR1); // Send SIGUSR1 to the child process
        }
        signal(SIGCHLD, waitHandler);
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}