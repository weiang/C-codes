#ifndef	_CURSOR_H_
#define	_CURSOR_H_

typedef	int	PtrToNode;
typedef	int	List;
typedef	PtrToNode	Position;
typedef int	ElementType;

void InitializeCursorSpace(void);

int IsEmpty(const List l);
int IsLast(const List l,Position p);
Position Find(ElementType x,const List l);
void Delete(ElementType x,const List l);
Position FindPrevious(ElementType x,const List l);
void Insert(ElementType x,List l,Position p);
void DeleteList(List l);

#endif	/* _CURSOR_H_ */
