/* Homework problem 8.21 */
#include "../csapp.h"

int main(void)
{
	if (fork() == 0) {
		printf("a");
		exit(0);
	}

	else {
		printf("b");
		waitpid(-1, NULL, 0);
	}
	printf("c");
	exit(0);
}
