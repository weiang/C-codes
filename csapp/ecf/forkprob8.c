#include "../csapp.h"

int main(int argc, char *argv[])
{
	int	i;
	static int	count = 0;
	int	n;
	
	n = atoi(argv[1]);

	for (i = 0; i < n; i ++)
		fork();

	printf("Hello\n");
	count ++;
	exit(EXIT_SUCCESS);
}
