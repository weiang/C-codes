#include "apue.h"
#include "stdlib.h"

int main(void)
{	
	int i;
	char **ptr;
	ptr = (char **)calloc(sizeof(char *),10);
	printf("%p\n",ptr);
	for (i = 0;i < 10;i ++){
		printf("%p\n",*ptr + i);
	}
	return 0;
}
