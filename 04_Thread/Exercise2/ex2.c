#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increase_counter()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, increase_counter, NULL);
    pthread_create(&thread2, NULL, increase_counter, NULL);
    pthread_create(&thread3, NULL, increase_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("Counter: %d\n", counter);

    return 0;
}