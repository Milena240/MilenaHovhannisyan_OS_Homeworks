#include <stdio.h>
#include <pthread.h>

const int SIZE = 3;

void*
thread_function(void* arg)
{
    long id = (long)arg;
    printf("Thread %ld is running\n", id);
    return NULL;
}

int
main()
{
    pthread_t threads[SIZE];

    for (long i = 0; i < SIZE; ++i) {
    	pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }

    for (int i = 0; i < SIZE; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads done.\n");
    return 0;
}

