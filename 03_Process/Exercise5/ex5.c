#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void createZombie()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child process (Zombie) PID: %d\n", getpid());
        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process (Zombie creator) PID: %d\n", getpid());
        while (1)
            ;
    }
    else
    {
        printf("Fork failed\n");
    }
}

void createOrphan()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child process (Orphan) PID: %d, Parent PID: %d\nRemember to kill Orphan process\n", getpid(), getppid());
        while (1)
            ;
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process (Orphan creator) PID: %d\n", getpid());
    }
    else
    {
        printf("Fork failed\n");
    }
}

int main()
{
    // printf("Creating a zombie process...\n");
    // createZombie();

    printf("Creating an orphan process...\n");
    createOrphan();

    return 0;
}