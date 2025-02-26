#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void signal_handler()
{
    printf("SIGTSTP ignored\n");
}

int main(int argc, char *argv[])
{
    signal(SIGTSTP, signal_handler);
    while (1)
    {
    }
    return 0;
}