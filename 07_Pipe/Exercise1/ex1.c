
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int fds[2];

int main()
{
    if (pipe(fds) == -1)
    {
        perror("pipe");
        exit(1);
    }
    char buffer[BUFFER_SIZE];
    pid_t pid = fork();

    switch (pid)
    {
    case 0: // Child process
        close(fds[1]);

        read(fds[0], buffer, BUFFER_SIZE);
        printf("Child received: %s\n", buffer);

        close(fds[0]);
        break;

    case -1:
        perror("fork");
        exit(1);

    default: // Parent process
        close(fds[0]);

        strcpy(buffer, "Hello, child!");

        write(fds[1], buffer, strlen(buffer));

        close(fds[1]);

        if (wait(NULL) == -1)
        {
            perror("wait");
            exit(1);
        }

        break;
    }

    return 0;
}