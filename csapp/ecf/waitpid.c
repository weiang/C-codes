#include "../csapp.h"

#define N	5

int main(void)
{
	int	status, i;
	pid_t	pid;
	
	/* Parent creates N child processes */
	for (i = 0; i < N; i ++) {
		if ((pid = Fork()) == 0)
			exit(100 + i);
	}

	/* Parent reaps N child processes */
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status)) {
			printf("Child %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
		}
		else
			printf("Child %d terminated abnormally\n", pid);
	}

	/* The only normal termination is if there are no more children */
	if (errno != ECHILD)
		unix_error("waitpid error");
	
	exit(EXIT_SUCCESS);
}
