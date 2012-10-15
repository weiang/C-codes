#include "../csapp.h"

int main(void)
{
	if (Fork() == 0) {
		printf("a\n");
	}
	else {
		printf("b\n");
		waitpid(-1, NULL, 0);
	}
	printf("c\n");
	exit(EXIT_SUCCESS);
}
