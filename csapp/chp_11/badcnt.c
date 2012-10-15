#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NITERS	1000

void *count(void *argp);
unsigned int	cnt = 0;

int main(void)
{
	pthread_t	tid1,tid2;

	pthread_create(&tid1,NULL,count,NULL);
	pthread_create(&tid2,NULL,count,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	if (cnt != (unsigned)NITERS * 2)
		printf("BOOM!!! cnt = %d\n",cnt);
	else
		printf("OK!!! cnt = %d\n",cnt);

	exit(EXIT_SUCCESS);
}

void *count(void *argp)
{
	int	i;
	for (i = 0;i < NITERS;i ++)
		cnt ++;
	return NULL;
}
