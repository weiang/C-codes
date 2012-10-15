#ifndef	_QUEUE_H_
#define	_QUEUE_H_

struct queue_record;
typedef	struct	queue_record	*queue;
typedef	int	element_type;

int
is_empty(queue q);

int
is_full(queue q);

queue
creat_queue(int size);

void
dispose_queue(queue q);

void 
make_empty(queue q);

void
en_quene(element_type element,queue q);

void
de_queue(queue q);

element_type
front_queue(queue q);

#endif	/* _QUEUE_H_ */

struct queue_record
{

	int	cap;
	int	front
	int	rear;
	int	size;
	element_type	*arr;
};

#define	MIN_QUEUE_SIZE	5
