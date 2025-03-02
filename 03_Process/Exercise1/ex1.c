#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("I am Child process, myPID: %d\n", getpid());
    }
    else if (pid > 0)
    {
        printf("I am Parent process, childPID: %d\n", pid);
        wait(NULL);
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}