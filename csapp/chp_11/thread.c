#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *argp);

int
main(void)
{
	pthread_t	tid;
	
	pthread_create(&tid,NULL,thread,NULL);
	pthread_join(tid,NULL);
	exit(EXIT_SUCCESS);
}

/* Thread routine */
void *thread(void *argp)
{
	printf("Hello world\n");
	return NULL;
}
