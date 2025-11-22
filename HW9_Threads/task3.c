#include <stdio.h>
#include <pthread.h>

const int NUMBER_COUNT = 5;
const int THREAD_COUNT = 3;

void*
print_numbers(void* arg)
{
    long id = (long)arg;

    for(int i = 0; i < NUMBER_COUNT; ++i) {
        printf("Thread %ld: %d\n", id, i);
    } 
    return NULL;
}

int
main()
{
    pthread_t threads[THREAD_COUNT];

    for (long i = 0; i < THREAD_COUNT; ++i) {
        pthread_create(&threads[i], NULL, print_numbers, (void*)i);
    }

    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

