
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int fds1[2];
int fds2[2];

int main()
{
    if (pipe(fds1) == -1)
    {
        perror("pipe");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    pid_t pid1 = fork();

    switch (pid1)
    {
    case 0:             // Child process 1
        close(fds1[1]); // close write end of pipe 1

        read(fds1[0], buffer, BUFFER_SIZE);
        printf("Child %d received from parent %d: %s\n", getpid(), getppid(), buffer);
        strcat(buffer, " from parent!");

        close(fds1[0]); // close read end of pipe 1

        if (pipe(fds2) == -1)
        {
            perror("pipe");
            exit(1);
        }

        pid_t pid2 = fork();

        switch (pid2)
        {
        case 0:             // Child process 2
            close(fds2[1]); // close write end of pipe 2

            read(fds2[0], buffer, BUFFER_SIZE);
            printf("Child %d received from parent %d: %s\n", getpid(), getppid(), buffer);

            close(fds2[0]);
            break;

        case -1:
            perror("fork");
            exit(1);

        default:            // Parent process (child process 1)
            close(fds2[0]); // close read end of pipe 2

            write(fds2[1], buffer, strlen(buffer));
            
            close(fds2[1]);

            if (wait(NULL) == -1)
            {
                perror("wait");
                exit(1);
            }

        }

        close(fds1[0]);
        break;

    case -1:
        perror("fork");
        exit(1);

    default:            // Parent process
        close(fds1[0]); // close read end of pipe 1

        strcpy(buffer, "Hello, child!");

        write(fds1[1], buffer, strlen(buffer));

        close(fds1[1]);

        if (wait(NULL) == -1)
        {
            perror("wait");
            exit(1);
        }

        break;
    }

    return 0;
}