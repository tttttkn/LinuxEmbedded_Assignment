#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int array[ARRAY_SIZE];
long long global_sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *sum_array(void *arg)
{
    int thread_part = *(int *)arg;
    long long local_sum = 0;
    int start = thread_part * (ARRAY_SIZE / NUM_THREADS);
    int end = (thread_part + 1) * (ARRAY_SIZE / NUM_THREADS);

    for (int i = start; i < end; i++)
    {
        local_sum += array[i];
    }

    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    // Initialize the array with random integers from 1 to 100
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 100 + 1;
    }

    pthread_t threads[NUM_THREADS];
    

    // Create threads
    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, sum_array, &i);
    }

    // Wait for threads to complete
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Print the result
    printf("Total sum of the array: %lld\n", global_sum);

    return 0;
}