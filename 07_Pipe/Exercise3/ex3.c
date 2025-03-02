
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define NUM_BYTES 1

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
    int counter = 0;

    switch (pid)
    {
    case 0: // Child process
        close(fds[1]);
        while (read(fds[0], &buffer[counter], NUM_BYTES) > 0)
        {
            counter++;
        }

        printf("Child received: %s\nNumber of bytes read: %d\n", buffer, counter);

        close(fds[0]);
        break;

    case -1:
        perror("fork");
        exit(1);

    default: // Parent process
        close(fds[0]);

        strcpy(buffer, "Hello this is Tan Tai");

        while (buffer[counter] != '\0')
        {
            write(fds[1], &buffer[counter], NUM_BYTES);
            counter++;
        }
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