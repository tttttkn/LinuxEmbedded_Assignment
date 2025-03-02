#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 100

int array[ARRAY_SIZE];
int even_count = 0;
int odd_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *count_even(void *arg)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (array[i] % 2 == 0)
        {
            even_count++;
        }
    }
}

void *count_odd(void *arg)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (array[i] % 2 != 0)
        {
            odd_count++;
        }
    }
    return NULL;
}

int main()
{
    // Initialize the array with random integers from 1 to 100
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 100 + 1;
    }

    pthread_t thread1, thread2;

    // Create threads
    pthread_create(&thread1, NULL, count_even, NULL);
    pthread_create(&thread2, NULL, count_odd, NULL);

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the results
    printf("Total even numbers: %d\n", even_count);
    printf("Total odd numbers: %d\n", odd_count);

    return 0;
}