/* algorithom 1:implementatiom with array */
#define	MAX_DEGREE	1000
#include	"stdio.h"

/* data struct of array */
typedef struct 
{
	int	coeffarr[MAX_DEGREE + 1];
	int	high_power;
} *Poly;

/* initilize the coeffarr */
void ZeroPoly(Poly p)
{
	int	i;

	for (i = 0; i <= MAX_DEGREE; i ++){
		p -> coeffarr[i] = 0;
	}
	p -> high_power = 0;
}

/* Add poly */
void AddPoly(const Poly p1,const Poly p2,Poly p_sum)
{
	int	i;
	
	ZeroPoly(p_sum);
	p_sum -> high_power = (p1 -> high_power > p2 -> high_power ? p1 -> high_power : p2 -> high_power);
	for (i = p_sum -> high_power; i >= 0;i --){
		p_sum -> coeffarr[i] = p1 -> coeffarr[i] + p2 -> coeffarr[i];
	}
}

/* multiply polys */
void MulPoly(const Poly p1,const Poly p2,Poly p_mul)
{
	int	i,j;
	
	ZeroPoly(p_mul);
	p_mul -> high_power = p1 -> high_power + p2 -> high_power;
	if (p_mul -> high_power > MAX_DEGREE)
		printf("Exceeded array size\n");
	else {
		for (i = 0;i <= p1 -> high_power;i ++)
			for (j = 0;j <= p2 -> high_power;j ++)
				p_mul -> coeffarr[i + j] = p1 -> coeffarr[i] * p2 -> coeffarr[j];
	}
}
