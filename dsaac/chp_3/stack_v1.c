/* Implement stack with list */
/* 2012.7.6 */

#include "stdio.h"
#include "stdlib.h"

struct  node;
typedef struct node     *ptr_to_node;
typedef ptr_to_node     stack;
typedef int     element_type;

struct	node
{
	element_type	element;
	ptr_to_node	next;
};

#include "stack.h"

int
is_empty(stack s)
{
	return (s -> next == NULL);
}

stack
creat_stack(int size)
{
	ptr_to_node	p;

	if ((p = (ptr_to_node)malloc(sizeof(struct node))) == NULL){
		printf("out of space!\n");
		exit(EXIT_FAILURE);
	}
	p -> element = 0;
	p -> next = NULL;
	return p;
}

void 
dispose_stack(stack s)
{
	ptr_to_node	p;

	while (s != NULL){
		p = s -> next;
		free(s);
		s = p;
	}
	free(s);
}

void
make_empty(stack s)
{
	if (s == NULL){
		printf("Must use stack first!\n");
		exit(EXIT_FAILURE);
	}
	while(!is_empty(s))
		pop(s);
}

void
push(element_type x,stack s)
{
	ptr_to_node	p;
	
	if ((p = (ptr_to_node)malloc(sizeof(struct node))) == NULL){
		printf("out of space!\n");
		exit(EXIT_FAILURE);
	}
	
	p -> element = x;
	p -> next = s -> next;
	s -> next = p;
}

element_type
top_of_stack(stack s)
{	
	if (!is_empty(s))
		return s -> next -> element;
	printf("empty stack!\n");
	exit(EXIT_FAILURE);
}

void
pop(stack s)
{
	ptr_to_node	p;
	
	if (is_empty(s)){
		printf("empty stack!\n");
		exit(EXIT_FAILURE);
	}
	p = s -> next;
	s -> next = s -> next -> next;
	free(p);
}
