
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int counter = 0;
void signal_handler(int signo)
{
    if (counter < 2)
    {
        printf("SIGINT received\n");
        counter++;
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

int main()
{
    signal(SIGINT, &signal_handler);
    while (1)
    {
    }
    return 0;
}