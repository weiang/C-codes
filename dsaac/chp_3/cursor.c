#include "cursor.h"
#include "stdlib.h"

#define	SPACE_SIZE	1000

struct Node
{
	ElementType	element;
	Position	next;
};

struct Node cursor_space[SPACE_SIZE];

static Position CursorAlloc(void)
{
	Position	p;
	
	p = cursor_space[0].next;
	cursor_space[0].next = cursor_space[p].next;
	return p;
}

static void CursorFree(Position p)
{
	cursor_space[p].next = cursor_space[0].next;
	cursor_space[0].next = p;
}

int IsEmpty(const List l)
{
	return cursor_space[l].next == 0;
}

int IsLast(List l,Position p)
{
	return cursor_space[p].next == 0;
}

Position Find(ElementType x,const List l)
{
	Position	p;
	
	p = cursor_space[l].next;
	while (p != 0 && cursor_space[p].element != x)
		p = cursor_space[p].next;
	return p;
}

Position FindPrevious(ElementType x,const List l)
{
	Position	p;
	
	p = cursor_space[l].next;
	while (cursor_space[p].next != 0 && cursor_space[cursor_space[p].next].element != x)
		p = cursor_space[p].next;
	return p;
}

void Delete(ElementType x,List l)
{
	Position	p,tmp;
	
	p = FindPrevious(x,l);
	
	if (!IsLast(p,l)){
		tmp = cursor_space[p].next;
		cursor_space[p].next = cursor_space[tmp].next;
		CursorFree(tmp);
	}
}

void Insert(ElementType x,List l,Position p)
{
	Position	tmp;
	
	tmp = CursorAlloc();
	if (tmp == 0){
		exit(-1);
	}
	cursor_space[tmp].next = cursor_space[p].next;
	cursor_space[p].next = tmp;
	cursor_space[tmp].element = x;
}
