#include <stdio.h>
#include <pthread.h>

const int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int SIZE = 10;

void*
calculate_sum(void* arg)
{
    int part = (int)(long)arg;
    int start = part * (SIZE / 2);
    int end = start + (SIZE / 2);

    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += array[i];
    }

    printf("Thread %d sum: %d\n", part, sum);
    return NULL;
}

int
main()
{
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, calculate_sum, (void*)0);
    pthread_create(&threads[1], NULL, calculate_sum, (void*)1);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}

