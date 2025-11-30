#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

long long counter = 0;
pthread_mutex_t mutex;
pthread_spinlock_t spinl;

typedef struct {
    long long increments;
} thr_arg_t;

void* 
thread_ordinary(void* arg)
{
    thr_arg_t* a = arg;
    for (long long i = 0; i < a->increments; ++i) {
        ++counter;
    }
    return NULL;
}

void*
thread_mutex(void* arg)
{
    thr_arg_t* a = arg;
    for (long long i = 0; i < a->increments; ++i) {
        pthread_mutex_lock(&mutex);
        ++counter;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void*
thread_spinl(void* arg)
{
    thr_arg_t* a = arg;
    for (long long i = 0; i < a->increments; ++i) {
        pthread_spin_lock(&spinl);
        ++counter;
        pthread_spin_unlock(&spinl);
    }
    return NULL;
}

int 
main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <mode:none|mutex|spin> <N_threads> <M_increments>\n", argv[0]);
        return 1;
    }
    char *mode = argv[1];
    int N = atoi(argv[2]);
    long long M = atoll(argv[3]);
    if (N <= 0 || M < 0) {
        fprintf(stderr, "Invalid N or M\n");
        return 1;
    }

    pthread_t *threads = malloc(sizeof(pthread_t) * N);
    thr_arg_t arg = { .increments = M };

    if (strcmp(mode, "mutex") == 0) {
        pthread_mutex_init(&mutex, NULL);
    } else if (strcmp(mode, "spin") == 0) {
        pthread_spin_init(&spinl, PTHREAD_PROCESS_PRIVATE);
    }

    for (int i = 0; i < N; ++i) {
        if (strcmp(mode, "none") == 0) {
            pthread_create(&threads[i], NULL, thread_ordinary, &arg);
        } else if (strcmp(mode, "mutex") == 0) {
            pthread_create(&threads[i], NULL, thread_mutex, &arg);
        } else if (strcmp(mode, "spin") == 0) {
            pthread_create(&threads[i], NULL, thread_spinl, &arg);
        } else {
            fprintf(stderr, "Unknown mode: %s\n", mode);
            return 1;
        }
    }

    for (int i = 0; i < N; ++i) pthread_join(threads[i], NULL);

    if (strcmp(mode, "mutex") == 0) pthread_mutex_destroy(&mutex);
    if (strcmp(mode, "spin") == 0) pthread_spin_destroy(&spinl);

    long long expected = (long long)N * M;
    printf("Mode: %s\n", mode);
    printf("Expected: %lld\n", expected);
    printf("Actual:   %lld\n", counter);

    free(threads);
    return 0;
}

