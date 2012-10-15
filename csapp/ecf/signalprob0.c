#include "../csapp.h"

#define SIGUSER	33

pid_t	pid;
int	counter = 2;

void siguser_handler(int msg)
{
	counter = counter - 1;
	printf("%d\n",counter);
	fflush(stdout);
	exit(EXIT_SUCCESS);
}

int main(void)
{
	signal(SIGUSER, siguser_handler);

	printf("%d\n", counter);
	fflush(stdout);

	if ((pid = Fork()) == 0) {
		while (1) {
				;
		}
	}

	kill(pid, SIGUSER);
	waitpid(-1, NULL, 0);
	counter = counter + 1;
	printf("%d", counter);
	exit(EXIT_SUCCESS);
}
