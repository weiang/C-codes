#include "../csapp.h"

extern char	**environ;

int main(int argc, char *argv[])
{
	int	i;
	
	/* Print arguments list */
	printf("Command line arguments:\n");
	for (i = 0; i < argc; i ++) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	printf("\n");
	
	/* Print environment variables list */
	i = 0;
	printf("Environment variables:\n");
	while (environ[i ++] != NULL) {
		printf("envp[%i]: %s\n", i, environ[i]);
	}
	return 0;
}
