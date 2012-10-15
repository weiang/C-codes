#include "../csapp.h"

void end(void)
{
	printf("2\n");
}

int main(void)
{
	if (fork() == 0)
		atexit(end);
	if (fork() == 0)
		printf("0");
	else 
		printf("1");
	exit(EXIT_SUCCESS);
}
