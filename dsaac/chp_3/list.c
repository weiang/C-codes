#include "stdio.h"
#include "stdlib.h"
#include "list.h"

struct	Node
{
	ElementType	element;
	Position	next;
};

int IsLast(Position p,Header h)
{
	return p -> next == NULL;
}

int IsEmpty(Header h)
{
	return h -> next == NULL;
}

Header MakeEmpty(Header h)
{
	Position tmp,p;

	p = h -> next;
	h -> next = NULL;
	while (p != NULL){
		tmp = p -> next;
		free(p);
		p = tmp;
	}
	
	return h;
}

Position Find(ElementType x,Header h)
{
	Position	p;
	
	p = h -> next;
	while (p != NULL && p -> element != x){
		p = p -> next;
	}

	return p;
}

Position FindPrevious(ElementType x,Header h)
{
	Position	p;
	
	p = h -> next;
	while (p -> next != NULL && p -> next -> element != x){
		p = p -> next;
	}
	
	return p;
}

void Delete(ElementType x,Header h)
{
	Position	p,tmp;
	
	p = FindPrevious(x,h);
	if (!IsLast(p,h)){
		tmp = p -> next;
		p -> next = tmp -> next;
		free(tmp);
	}
	
}

void Insert(ElementType x,Header h,Position p)
{
	Position	tmp;
	
	tmp = p -> next;
	if ((p -> next = (Position)malloc(sizeof(struct Node))) == NULL)
		exit(-1);
	p -> next -> element = x;
	p -> next -> next = tmp;
}
	
	
