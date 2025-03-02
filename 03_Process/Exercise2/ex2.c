#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{

    if ((argc != 2) || ((atoi(argv[1]) != 1) && (atoi(argv[1]) != 2)))
    {
        printf("Usage: %s [1/2]\n", argv[0]);
        return -1;
    }

    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        if (atoi(argv[1]) == 1)
        {
            execlp("ls", "ls", NULL);
        }
        else if (atoi(argv[1]) == 2)
        {
            execlp("date", "date", NULL);
        }
        else
        {
            printf("Usage: %s [1/2]\n", argv[0]);
            return -1;
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}