#include "stdio.h"
#include "stdlib.h"

static void PrintDigit(int );
static void PrintOut(unsigned int );

int main(void)
{
	int	x;
	
	scanf("%d",&x);

	PrintOut(x);
	printf("\n");

	exit(0);
}

static void PrintDigit(int x)
{
	printf("%d",x);
}

static void PrintOut(unsigned int n)
{
	if (n >= 10){
		PrintOut(n / 10);
	}
	PrintDigit(n % 10);
}
