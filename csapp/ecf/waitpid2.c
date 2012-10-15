#include "../csapp.h"

#define N	5

int main(void)
{
	int	status, i;
	pid_t	pid[N], retpid;
	
	/* Parent creates N child processes */
	for (i = 0; i < N; i ++) {
		if ((pid[i] = Fork()) == 0)
			exit(100 + i);
	}

	/* Parent reaps N child processes */
	i = 0;
	while ((retpid = waitpid(pid[i ++], &status, 0)) > 0) {
		if (WIFEXITED(status)) {
			printf("Child %d terminated normally with exit status = %d\n", retpid, WEXITSTATUS(status));
		}
		else
			printf("Child %d terminated abnormally\n", pid[i]);
	}

	/* The only normal termination is if there are no more children */
	if (errno != ECHILD)
		unix_error("waitpid error");
	
	exit(EXIT_SUCCESS);
}
