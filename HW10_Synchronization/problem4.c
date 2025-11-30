#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semA, semB, semC;
int N = 10;
pthread_mutex_t print_mtx; 

void*
threadA(void *arg) 
{
    for (int i = 0; i < N; ++i) {
        sem_wait(&semA);
        pthread_mutex_lock(&print_mtx);
        printf("Thread A: A %d\n", i);
        pthread_mutex_unlock(&print_mtx);
        sem_post(&semB);
    }
    return NULL;
}

void*
threadB(void *arg)
{
    for (int i = 0; i < N; ++i) {
        sem_wait(&semB);
        pthread_mutex_lock(&print_mtx);
        printf("Thread B: B %d\n", i);
        pthread_mutex_unlock(&print_mtx);
        sem_post(&semC);
    }
    return NULL;
}

void* 
threadC(void *arg) 
{
    for (int i = 0; i < N; ++i) {
        sem_wait(&semC);
        pthread_mutex_lock(&print_mtx);
        printf("Thread C: C %d\n", i);
        pthread_mutex_unlock(&print_mtx);
        sem_post(&semA);
    }
    return NULL;
}

int
main(int argc, char **argv) 
{
    if (argc >= 2) N = atoi(argv[1]);
    sem_init(&semA, 0, 1); 
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    pthread_mutex_init(&print_mtx, NULL);

    pthread_t a, b, c;
    pthread_create(&a, NULL, threadA, NULL);
    pthread_create(&b, NULL, threadB, NULL);
    pthread_create(&c, NULL, threadC, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    pthread_mutex_destroy(&print_mtx);
    return 0;
}


