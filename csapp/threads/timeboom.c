#include "csapp.h"

#define TIMEOUT	5

void *thread(void *argp);
struct timespec *maketimeout(struct timespec *tp,int secs);

pthread_cond_t	cond;
pthread_mutex_t	mutex;
pthread_t	tid;

int main(void)
{
	int	i,rc;
	struct timespec	timeout;

	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);

	pthread_mutex_lock(&mutex);
	pthread_create(&tid,NULL,thread,NULL);
	for (i = 0;i < TIMEOUT;i ++){
		printf("BEEP\n");
		rc = pthread_cond_timedwait(&cond,&mutex,maketimeout(&timeout,1));
		if (rc != ETIMEDOUT){
			printf("WHEW!\n");
			exit(EXIT_SUCCESS);
		}
	}
	printf("BOOM!\n");
	exit(EXIT_SUCCESS);
}

/*	Thread routine */
void *thread(void *argp)
{
	getchar();
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	return NULL;
}
