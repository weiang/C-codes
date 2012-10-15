/* Algorithom 2:implementation of Poly */
#include "stdio.h"
#include "stdlib.h"

/* data structure */
typedef struct Node	*PtrToNode;

struct Node
{
	int	coefficient;
	int 	exp;
	PtrToNode	next;
};

typedef PtrToNode	Poly;

/* Initlize Poly Node */
void InitPoly(Poly p)
{
	Poly	tmp;
	tmp = p -> next;
	while (tmp != NULL){
		tmp -> coefficient = 0;
		tmp -> exp = 0;
		tmp = tmp -> next;
	}
}

/* Add Poly */
Poly AddPoly(const Poly p1,const Poly p2)
{
	Poly	tmp1,tmp2,p;
	Poly	p_sum;

	tmp1 = p1 -> next;
	tmp2 = p2 -> next;
	p_sum = (Poly)malloc(sizeof(struct Node));
	InitPoly(p_sum);
	p = p_sum;
	while (tmp1 != NULL && tmp2 != NULL){
		while (tmp1 -> coefficient != tmp2 -> coefficient){
			p -> next = (Poly)malloc(sizeof(struct Node));
			if (tmp1 -> exp > tmp2 -> exp){
				p -> next -> coefficient = tmp1 -> coefficient;
				p -> next -> exp = tmp1 -> exp;
				p -> next -> next = NULL;
				p = p -> next;
				tmp1 = tmp1 -> next;
			}
			else	{
				p -> next -> coefficient = tmp2 -> coefficient;
				p -> next -> exp = tmp2 -> exp;
				p -> next -> next = NULL;
				p = p -> next;
				tmp2 = tmp2 -> next;
			}
		}
		if (tmp1 -> exp == tmp2 ->exp){
			p -> next = (Poly)malloc(sizeof(struct Node));
			p -> next -> next = NULL;
			p -> next -> coefficient = tmp1 -> coefficient + tmp2 -> coefficient;
			p -> next -> exp = tmp1 -> exp;
			p = p -> next;
		}
	}

	if (tmp1 == NULL){
		while (tmp2 != NULL){
			p -> next = (Poly)malloc(sizeof(struct Node));
			p = p -> next;
			p -> next = NULL;
			p -> coefficient = tmp2 -> coefficient;
			p -> exp = tmp2 -> exp;
			tmp2 = tmp2 -> next;
				
		}
	}
	else if (tmp2 == NULL){
		while (tmp1 != NULL){
			p -> next = (Poly)malloc(sizeof(struct Node));
			p = p -> next;
			p -> next = NULL;
			p -> coefficient = tmp1 -> coefficient;
			p -> exp = tmp1 -> exp;
			tmp1 = tmp1 -> next;
		}
	}
			 
	return p_sum;
}

/* Multiple Poly */
Poly MulPoly(const Poly p1,const Poly p2)
{
	Poly	tmp1,tmp2,p;
	Poly	p_mul;

	tmp1 = p1 -> next;
	tmp2 = p2 -> next;
	p_mul = (Poly)malloc(sizeof(struct Node));
	InitPoly(p_mul);
	p = p_mul;

	while (tmp1 != NULL){
		tmp2 = p2 -> next;
		while (tmp2 != NULL){
			p -> next = (Poly)malloc(sizeof(struct Node));
			p = p -> next;
			p -> exp = tmp1 -> exp + tmp2 -> exp;
			p -> coefficient = tmp1 -> coefficient * tmp2 -> coefficient;
			p -> next = NULL;
			tmp2 = tmp2 -> next;
		}
		tmp1 = tmp1 -> next;
	}

	/* Intergate Nodes whose "exp" are the same */
	p = p_mul -> next;
	while (p != NULL){
		tmp1 = p;
		while (tmp1 ->next != NULL){
			if (tmp1 -> next -> exp == p -> exp){
				p -> coefficient += tmp1 -> next -> coefficient;
				tmp2 = tmp1 -> next;
				tmp1 -> next = tmp2 -> next;
				free(tmp2);
				tmp1 = tmp1 -> next;
			}
			else	tmp1 = tmp1 -> next;
		}
		if (tmp1 -> exp == p -> exp){		/* Cope with the last Node of the p_mul */
			p -> coefficient += tmp1 -> coefficient;
			tmp1 -> exp = 0;		/* Set last Node's exp and coefficient val equal to "0" */
			tmp1 -> coefficient = 0;	/* So that when added to the rest of the list Node it does not make sense*/
		}
		p = p -> next;
	}

	return p_mul;
}

/* retrive Poly */
void Retrive(Poly p)
{
	while (p != NULL){
		printf("%d*exp(%d) + ",p -> coefficient,p -> exp);
		p = p -> next;
	}
	printf("0\n");
}
