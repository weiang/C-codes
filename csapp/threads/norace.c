#include "csapp.h"

#define N	4		

void *thread(void *argp);
	
int main(void)
{
	pthread_t	tid[N];
	int	i;
	int	*ptr = NULL;
	
	for (i = 0;i < N;i ++){
		ptr = malloc(sizeof(int));
		*ptr = i;
		pthread_create(&tid[i],NULL,thread,ptr);
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
	
	free(argp);
	printf("Hello from thread %d\n",myid);
	
	return NULL;
}

