#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t printers;
pthread_mutex_t count_mtx;
int current_printing = 0;
int max_simultaneous = 0;

typedef struct {
    int id;
} arg_t;

void*
print_job(void* a) 
{
    arg_t* arg = a;
    int id = arg->id;

    sem_wait(&printers);

    pthread_mutex_lock(&count_mtx);
    ++current_printing;
    if (current_printing > max_simultaneous) max_simultaneous = current_printing;
    printf("Thread %d START printing (current=%d)\n", id, current_printing);
    pthread_mutex_unlock(&count_mtx);
    
    usleep((rand() % 200 + 100) * 1000); 
    
    pthread_mutex_lock(&count_mtx);
    --current_printing;
    printf("Thread %d DONE printing (current=%d)\n", id, current_printing);
    pthread_mutex_unlock(&count_mtx);

    sem_post(&printers);
    return NULL;
}

int 
main(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N_jobs> <K_printers>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int K = atoi(argv[2]);
    if (N <= 0 || K <= 0) return 1;

    srand((unsigned)time(NULL));
    sem_init(&printers, 0, K);
    pthread_mutex_init(&count_mtx, NULL);

    pthread_t* threads = malloc(sizeof(pthread_t) * N);
    arg_t* args = malloc(sizeof(arg_t) * N);

    for (int i = 0; i < N; ++i) {
        args[i].id = i;
        pthread_create(&threads[i], NULL, print_job, &args[i]);
    }
    for (int i = 0; i < N; ++i) pthread_join(threads[i], NULL);

    printf("Max simultaneous printing observed: %d (K=%d)\n", max_simultaneous, K);

    sem_destroy(&printers);
    pthread_mutex_destroy(&count_mtx);
    free(threads);
    free(args);
    return 0;
}

