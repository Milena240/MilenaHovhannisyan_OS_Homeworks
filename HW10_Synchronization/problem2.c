#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

long long balance = 0;
pthread_mutex_t mutex;
pthread_spinlock_t spinl;
int use_mutex = 1;
int long_cs = 0;
long long it = 100000;

typedef struct {
    int id;
    long long it;
} thr_arg_t;

void* 
depositor(void* arg) 
{
    thr_arg_t* a = arg;
    for (long long i = 0; i < a->it; ++i) {
        if (use_mutex) {
            pthread_mutex_lock(&mutex);
            ++balance;
            if (long_cs) usleep(100);
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_spin_lock(&spinl);
            ++balance;
            if (long_cs) usleep(100);
            pthread_spin_unlock(&spinl);
        }
    }
    return NULL;
}

void*
withdrawer(void *arg) 
{
    thr_arg_t *a = arg;
    for (long long i = 0; i < a->it; ++i) {
        if (use_mutex) {
            pthread_mutex_lock(&mutex);
            --balance;
            if (long_cs) usleep(100);
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_spin_lock(&spinl);
            --balance;
            if (long_cs) usleep(100);
            pthread_spin_unlock(&spinl);
        }
    }
    return NULL;
}

double elapsed_sec(struct timespec s, struct timespec e) {
    return (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec) / 1e9;
}

int main(int argc, char **argv) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <mutex|spin> <short|long> <num_deposit> <num_withdraw> <it_per_thread>\n", argv[0]);
        return 1;
    }
    char *mode = argv[1];
    char *cs = argv[2];
    int ndeposit = atoi(argv[3]);
    int nwithdraw = atoi(argv[4]);
    it = atoll(argv[5]);
    if (ndeposit < 0 || nwithdraw < 0 || it < 0) return 1;

    use_mutex = (strcmp(mode, "mutex") == 0);
    long_cs = (strcmp(cs, "long") == 0);

    if (use_mutex) pthread_mutex_init(&mutex, NULL);
    else pthread_spin_init(&spinl, PTHREAD_PROCESS_PRIVATE);

    pthread_t *dthreads = malloc(sizeof(pthread_t) * ndeposit);
    pthread_t *wthreads = malloc(sizeof(pthread_t) * nwithdraw);
    thr_arg_t *dargs = malloc(sizeof(thr_arg_t) * ndeposit);
    thr_arg_t *wargs = malloc(sizeof(thr_arg_t) * nwithdraw);

    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    for (int i = 0; i < ndeposit; ++i) {
        dargs[i].id = i; dargs[i].it = it;
        pthread_create(&dthreads[i], NULL, depositor, &dargs[i]);
    }
    for (int i = 0; i < nwithdraw; ++i) {
        wargs[i].id = i; wargs[i].it = it;
        pthread_create(&wthreads[i], NULL, withdrawer, &wargs[i]);
    }

    for (int i = 0; i < ndeposit; ++i) pthread_join(dthreads[i], NULL);
    for (int i = 0; i < nwithdraw; ++i) pthread_join(wthreads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &t_end);
    double elapsed = elapsed_sec(t_start, t_end);

    printf("Mode: %s Case: %s\n", mode, cs);
    printf("Deposit threads: %d Withdraw threads: %d it/thread: %lld\n",
           ndeposit, nwithdraw, it);
    printf("Final balance: %lld Expected: 0\n", balance);
    printf("Elapsed time: %.6f seconds\n", elapsed);

    if (use_mutex) pthread_mutex_destroy(&mutex);
    else pthread_spin_destroy(&spinl);

    free(dthreads); free(wthreads); free(dargs); free(wargs);
    return 0;
}

