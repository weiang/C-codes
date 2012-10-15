#include "../csapp.h"

/* Exception handler */
void handler(int msg);

int main(int argc, char *argv[])
{
	signal(SIGINT,handler);	/* Install signal handler */

	if (argc != 2){
		printf("Usage:%s <secs>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	(void)snooze(atoi(argv[1]));
	return 0;
}

void handler(int msg)
{
	return;	/* Catch the signal and return */
}	
