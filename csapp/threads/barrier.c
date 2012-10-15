#include "csapp.h"

static pthread_mutex_t	mutex;
static pthread_cond_t	cond;

static int	nthreads;	/* The number of threads */
static int 	barriercnt = 0;	/* The number of barrier that has been called */

/* Initalize  barrier */
void barrier_init(int n)
{
	nthreads = n;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
}

void barrier()
{
	pthread_mutex_lock(&mutex);
	if (++barriercnt == nthreads){
		barriercnt = 0;
		pthread_cond_broadcast(&cond);
	}
	else
		pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
}
