#include <stdio.h>
#include <pthread.h>

int numbers[] = {1, 2, 3, 4, 5};
const int COUNT = 5;

void*
square(void* arg)
{
    int n = *(int*)arg;
    printf("Square of %d is %d\n", n, n * n);

    return NULL;
}

int
main()
{
    pthread_t threads[COUNT];

    for (int i = 0; i < COUNT; ++i) {
        pthread_create(&threads[i], NULL, square, &numbers[i]);
    }
    
    for (int i = 0; i < COUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

