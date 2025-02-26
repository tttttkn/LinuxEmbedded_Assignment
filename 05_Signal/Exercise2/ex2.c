#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int counter = 0;

void signal_handler(int signo)
{
    if (counter == 10)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        alarm(1);
        printf("Timer: %d seconds\n", counter + 1);
        counter++;
    }
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, &signal_handler);

    alarm(1);
    while (1)
    {
    }

    return 0;
}