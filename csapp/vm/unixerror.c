/* Unix error handler */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void unix_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, (char *)strerror(errno));
	exit(EXIT_SUCCESS);
} 
