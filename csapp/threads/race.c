#include "csapp.h"

#define N	3	

void *thread(void *argp);
	
int main(void)
{
	pthread_t	tid[N];
	int	i;
	
	for (i = 0;i < N;i ++){
		pthread_create(&tid[i],NULL,thread,&i);
	}
	for (i = 0;i < N;i ++){
		pthread_join(tid[i],NULL);
	}
	exit(EXIT_SUCCESS);
}

/* Thread routine */
void *thread(void *argp)
{
	int	myid = *((int *)argp);
	printf("Hello from thread %d\n",myid);
	
	return NULL;
}

