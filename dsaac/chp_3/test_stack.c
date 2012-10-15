typedef struct stack_record     *stack;
typedef int     element_type;

struct stack_record
{
        int     cap;
        int     top;
        element_type    *arr;
};

#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#include "string.h"

#define	MIN_STACK_SIZE	5
#define EMPTY_NO	-1
#define	MAX_INPUT	1000
/*
#define	BIG_LEFT	{
#define	BIG_RIGHT	}
#define	MEDIA_LEFT	[
#define	MEDIA_RIGHT	]
*/

int
main(void)
{
	char	array[MAX_INPUT];
	stack	s;
	int	i,num;

	gets(array);
	num = strlen(array);
	if ((s = creat_stack(num)) == NULL){
		printf("Stack created failed!\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0;i < num;i ++){
		if (array[i] == '[' || array[i] == '{'){
			push(array[i],s);
		}
		else if (array[i] == '}'){
			if ( top_of_stack(s) == '{')
				pop(s);
			else {
				printf("Match failed!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (array[i] == ']'){
			if (top_of_stack(s) == '['){
				pop(s);
			}
			else {
				printf("Match failed!\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	printf("Match succeed!\n");
	return EXIT_SUCCESS;
}


