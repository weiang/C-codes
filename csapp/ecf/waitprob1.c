#include "../csapp.h"

int main(void)
{
	int	status;
	pid_t 	pid;
	
	printf("Hello\n");
	pid = Fork();
	printf("%d\n", !pid);
	if (pid != 0) {
		if (waitpid(-1, &status, 0) > 0) 
			if (WIFEXITED(status))
				printf("%d\n", WEXITSTATUS(status));
	}

	printf("Bye\n");
	exit(5);
}
