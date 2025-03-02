
#include <stdio.h>
#include <pthread.h>

void print(int i)
{
    printf("Thread %d: Hello from thread\n", i);
}

int main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, (void *)&print, (void *)1);
    pthread_create(&thread2, NULL, (void *)&print, (void *)2);

    pthread_join(thread2, NULL); // block until thread2 finishes its execution
    pthread_join(thread1, NULL); // block until thread1 finishes its execution

    return 0;
}