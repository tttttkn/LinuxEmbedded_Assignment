#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int data = 0;

int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *producer()
{
    while (counter < 10)
    {
        pthread_mutex_lock(&mutex);
        data = rand() % 10 + 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

static void *consumer()
{
    pthread_mutex_lock(&mutex);
    while (counter < 10)
    {
        pthread_cond_wait(&cond, &mutex);
        printf("Data %d: %d\n", counter + 1, data);
        counter++;
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;

    pthread_create(&thread2, NULL, consumer, NULL);
    pthread_create(&thread1, NULL, producer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
