#ifndef	_LIST_H_
#define	_LIST_H_

struct	Node;
typedef	struct Node	*PtrToNode;
typedef	PtrToNode	Header;
typedef	PtrToNode	Position;

typedef int	ElementType;
/* make list h empty */
Header	MakeEmpty(Header h);

/* check if list is empty,
 * return true if it is empty 
 */
int	IsEmpty(Header h);

/* check if node p is the last node of the list h,
 * return ture if it's the last node of the list h
 */
int	IsLast(Position p,Header h);

/* return Position of x in the list h;
 * NULL if not found
 */
Position	Find(ElementType x,Header h);

/* delete element x in the list h */
void	Delete(ElementType,Header);

/* return peevious Position of x in the list h;
 * NULL if list h is empty
 */
Position	FindPrevious(ElementType,Header);

/* insert x after Position p in the list h */
void	Insert(ElementType x,Header,Position p);

#endif	/* _LIST_H_ */
