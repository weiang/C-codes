#include "../csapp.h"

void sigchld_handler(int);	/* SIGCHLD signal handler */

int main(void)
{
	int	i, n;
	char	buf[MAXBUF];

	if (signal(SIGCHLD, sigchld_handler) == SIG_ERR)
		unix_error("signal error");	/* Install SIGCHLD handler */

	for (i = 0; i < 5; i ++){
		if (Fork() == 0){
			printf("Hello from child %d\n", getpid());
			sleep(1);
			exit(EXIT_SUCCESS);
		}
	}

	if (n = read(STDIN_FILENO,buf, sizeof(buf)) < 0)
		unix_error("Read error");

	printf("Processing command line!\n");

	while (1) {
		;
	}
	exit(EXIT_SUCCESS);
}

void sigchld_handler(int msg)
{
	pid_t	pid;

	if ((pid = waitpid(-1, NULL, 0)) < 0)
		unix_error("Waitpid error");

	fprintf(stdout, "child %d has been reaped!\n", pid);
	sleep(2);
	return;
}
