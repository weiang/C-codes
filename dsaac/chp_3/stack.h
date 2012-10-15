#ifndef	_STACK_H_
#define	_STACK_H_

int
is_empty(stack s);

stack
creat_stack(int);

void
dispose_stack(stack s);

void
make_empty(stack s);

void
push(element_type x,stack s);

element_type
top_of_stack(stack s);

void
pop(stack s);

#endif	/* _STACK_H_ */


