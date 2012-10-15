#include "../csapp.h"

int main(void)
{	
	pid_t	pid;

	if ((pid = Fork()) == 0) {
		pause();
		printf("Received SIGKILL!\n");
		exit(EXIT_SUCCESS);
	}

	if (kill(pid, SIGKILL) < 0) {
		unix_error("Kill error");
	}
	exit(EXIT_SUCCESS);
}
	
