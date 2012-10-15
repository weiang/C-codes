#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int
main(void)
{
	int	count = 0;
	int	ch;

	while ((ch = getchar()) != EOF){
		if (ch == '{'){
			count ++;
		}
		if (ch == '}'){
			count --;
		}
		if (count < 0){
			printf("match failed!\n");
			exit(EXIT_FAILURE);
		}
	}

	if (count != 0){
		printf("match failed!\n");
		exit(EXIT_FAILURE);
	}
	printf("match succeed!\n");	
	return EXIT_SUCCESS;
}			
