#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

#define P 2
#define C 2
#define K 9

int total_to_produce = P * K;
int consumed_count = 0;

void* 
producer_thread(void* arg) 
{
	int id = (int)(size_t)arg;

	for (int i = 0; i < K; i++) 
	{
		int item = id * 1000 + i;
		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);
		
		buffer[in_pos] = item;
		printf("Producer %d - produced %d at %d\n", id, item, in_pos);

		in_pos = (in_pos + 1) % BUFFER_SIZE;

		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);
	}

	return NULL;
}

void*
consumer_thread(void* arg) 
{
    int id = (int)(size_t)arg;

    int items_per_consumer = (P * K) / C;

    for (int i = 0; i < items_per_consumer; i++) 
    {
        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_mutex);

        int item = buffer[out_pos];
        printf("Consumer %d ← consumed %d at %d\n", id, item, out_pos);

        out_pos = (out_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);
    }

    return NULL;
}

int
main() 
{
	pthread_t prod_threads[P];
	pthread_t cons_threads[C];

	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);

	for (int i = 0; i < P; i++) 
	{
		pthread_create(&prod_threads[i], NULL, producer_thread, (void*)(size_t)i);
	}

	for (int i = 0; i < C; i++) 
	{
		pthread_create(&cons_threads[i], NULL, consumer_thread, (void*)(size_t)i);
	}

	for (int i = 0; i < P; i++) 
	{
		pthread_join(prod_threads[i], NULL);
	}

	for (int i = 0; i < C; i++)
	{
		pthread_join(cons_threads[i], NULL);
	}
	
	sem_destroy(&empty_slots);
	sem_destroy(&full_slots);
	pthread_mutex_destroy(&buffer_mutex);

	printf("All items produced and consumed.\n");
	return 0;
}

