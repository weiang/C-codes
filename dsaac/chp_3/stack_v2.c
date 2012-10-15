/* Implement stack with array */
/* 2012.7.6 */

#include "stdlib.h"
#include "stdio.h"
#define EMPTY_NO	-1
#define	MIN_STACK_SIZE	5

typedef	struct stack_record	*stack;
typedef int	element_type;

struct stack_record
{
	int	cap;
	int	top;
	element_type	*arr;
};

int
is_empty(stack s)
{
	return s -> top == EMPTY_NO;
}

int
is_full(stack s)
{
	return s -> top == (s -> cap - 1);
}

stack
creat_stack(int size)
{
	stack	s;
	
	if (size < MIN_STACK_SIZE){
		printf("Stack size too small!\n");
		exit(EXIT_FAILURE);
	}
	
	if ((s = (stack)malloc(sizeof(struct stack_record))) == NULL){
		printf("Out of space!\n");
		exit(EXIT_FAILURE);
	}
	if ((s -> arr = (element_type *)malloc(sizeof(element_type) * size)) == NULL){
		printf("Out of space!\n");
		exit(EXIT_FAILURE);
	}
	
	s -> cap = size;
	s -> top = EMPTY_NO;
	return s;
}

void
dispose(stack s)
{	
	if (s != NULL){
		free(s -> arr);
		free(s);
	}
}

void
make_empty(stack s)
{
	if (s != NULL){
		s -> top = EMPTY_NO;
	}
}

void
push(element_type x,stack s)
{
	if (!is_full(s)){
		s -> top ++;
		s -> arr[s -> top] = x;
	}
	else {
		printf("Stack full!\n");
		exit(EXIT_FAILURE);
	}
}

element_type
top_of_stack(stack s)
{	
	if (!is_empty(s))
		return (s -> arr[s -> top]);
	printf("Stack empty!\n");
	exit(EXIT_FAILURE);
}

void 
pop(stack s)
{
	if (!is_empty(s))
		s -> top --;
	else	exit(EXIT_FAILURE);
}
