#include "../csapp.h"

jmp_buf	buf;

void handler(int msg)
{
	longjmp(buf, 1);
}

int main(void)
{
	signal(SIGINT, handler);

	if (!setjmp(buf))
		printf("starting\n");
	else 
		printf("restarting\n");
	while (1) {
		sleep(1);
		printf("processing..\n");
	}
	exit(EXIT_SUCCESS);
}
