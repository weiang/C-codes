/* Test the algorithom 2 that cope with Poly */
#include "stdio.h"
#include "stdlib.h"

typedef struct Node     *PtrToNode;

struct Node
{
        int     coefficient;
        int     exp;
        PtrToNode       next;
};

typedef PtrToNode       Poly;

extern Poly AddPoly(Poly,Poly);
extern void Retrive(Poly);

int main(void)
{
	struct Node p1,p2,*tmp1,*tmp2;
	Poly	p_sum;
	
	p1.coefficient = p1.coefficient = 0;	/* initilize Poly header with zero */
	p2.exp = p2.exp = 0;
	tmp1 = (Poly)malloc(sizeof(struct Node));
	tmp2 = (Poly)malloc(sizeof(struct Node));
	p1.next = tmp1;
	p2.next = tmp2;
	printf("please creat Poly 1(end with 0 ):\n");
	do	{
			printf("coefficinet = :\n");
			scanf("%d",&tmp1 -> coefficient);
			printf("exp = :\n");
			scanf("%d",&tmp1 -> exp);
			tmp1 -> next = (Poly)malloc(sizeof(struct Node));
			tmp1 = tmp1 -> next;
			tmp1 -> next = NULL;
	} while (tmp1 -> exp != 0);

	printf("please creat Poly 2(end with 0):\n");
	do	{	
			printf("coefficient = :\n");
			scanf("%d",&tmp2 -> coefficient);
			printf("exp = :\n");
			scanf("%d",&tmp2 -> exp);
			tmp2 -> next = (Poly)malloc(sizeof(struct Node));
			tmp2 = tmp2 -> next;
			tmp2 -> next = NULL;
	} while (tmp2 -> exp != 0);	

	p_sum = AddPoly(&p1,&p2);
	printf("%p\n",p_sum);
	Retrive(p_sum);
	return 0;
}
			
