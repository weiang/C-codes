#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N	5

void *producer(void *arg);
void *consumer(void *arg);

struct	{
	int	buf;	/* Shared variable */
	sem_t	full,empty;	/* Semaphores */
}shared;

int main(void)
{
	pthread_t	tid_producer,tid_consumer;
	
	/* Initialize the semaphores */
	sem_init(&shared.empty,0,1);
	sem_init(&shared.full,0,0);

	/* Creat threads and wait for them to finish */
	pthread_create(&tid_producer,NULL,producer,NULL);
	pthread_create(&tid_consumer,NULL,consumer,NULL);
	pthread_join(tid_producer,NULL);
	pthread_join(tid_consumer,NULL);
	
	exit(EXIT_SUCCESS);
}

/* Producer thread routine */
void *producer(void *arg)
{
	int	i,item;

	for (i = 0;i < N;i ++){
		/* Produce item */
		item = i;
		printf("Produce %d\n",item);
		
		/* Write item to buf */
		sem_wait(&shared.empty);
		shared.buf = item;
		sem_post(&shared.full);
	}
	return NULL;
}

/* Consumer thread routine */
void *consumer(void *arg)
{
	int	i,item;
	
	for (i = 0;i < N;i ++){
		/* Read item from buf */
		sem_wait(&shared.full);
		item = shared.buf;
		sem_post(&shared.empty);

		/* Consume item */
		printf("Consumed %d\n",item);
	}
	return NULL;
}
	
