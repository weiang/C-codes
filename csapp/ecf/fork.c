/* Unix error handler */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void unix_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(EXIT_SUCCESS);
}

pid_t Fork(void)
{
	pid_t	pid;
	
	if ((pid = fork()) < 0) {
		unix_error("Fork error");
	}
	return pid;
}
