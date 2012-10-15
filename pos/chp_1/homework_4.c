#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX	1000

static void deblank(char *string);

int
main(void)
{
	char	input[MAX];

	if ((gets(input)) == NULL){
		printf("gets() error!\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n",input);
	deblank(input);
	printf("%s\n",input);
	return EXIT_SUCCESS;
}

void
deblank(char *string)
{
	int	i,k,flag;

	i = 0;
	k = 0;
	flag = 0;
	while (string[i] != '\0'){
		if (string[i] == ' '){
			flag = 1;
		}
		string[k] = string[i];
//		printf("%c",string[i]);
//		printf("%c",string[k]);
		i ++;
		if (flag == 1){
			while (string[i] == ' ')
				i ++;
			flag = 0;
		}
		k ++;
	}
	string[k] = '\0';
}
