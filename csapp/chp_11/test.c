#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NITERS 5

void *producer(void *arg), *consumer(void *arg); 

struct {
int buf;	/* shared variable */
sem_t full, empty; /* semaphores */
} shared;


int main(void)
{
	pthread_t tid_producer, tid_consumer;
	/* initialize the semaphores */
	sem_init(&shared.empty, 0, 1);
	sem_init(&shared.full, 0, 0);

	/* create threads and wait for them to finish */
	pthread_create(&tid_producer, NULL, producer, NULL);
	pthread_create(&tid_consumer, NULL, consumer, NULL);
	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);
	
	exit(0);
}



/* producer thread */
void *producer(void *arg)
{
	int i, item;
	for (i=0; i<NITERS; i++) {
	/* produce item */
	item = i;
	printf("produced %d\n", item);
	
	/* write item to buf */
	sem_wait(&shared.empty);
	shared.buf = item;
	sem_post(&shared.full);
	}
	return NULL;
}

/* consumer thread */
void *consumer(void *arg)
{
	int i, item;
	
	for (i=0; i<NITERS; i++) {
	/* read item from buf */
	sem_wait(&shared.full);
	item = shared.buf;
	sem_post(&shared.empty);
	
	/* consume item */
	printf("consumed %d\n", item);
	}
	return NULL;
}

