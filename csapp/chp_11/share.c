#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define	N	2

void *thread(void *argp);

char	**ptr;
int
main(void)
{
	int	i;
	pthread_t	tid;
	char	*msgs[N] = {
		"Hello from foo\n",
		"Hello from bar\n"
	};
	
	ptr = msgs;

	for (i = 0;i < N;i ++){
		pthread_create(&tid,NULL,thread,(void *)i);
	}
	pthread_exit(NULL);
}

void *thread(void *argp)
{
	int	myid = (int)argp;
//	int	myid = *((int*)argp);
	static int	cnt = 0;
	
	printf("[%d]:%s (cnt = %d)\n",myid,ptr[myid],++cnt);
}
