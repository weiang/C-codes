#include "apue.h"
#include "setjmp.h"

static void fun1(int,int,int,int);
static void fun2(void);

static int	globval;
static jmp_buf	setjmpbuf;

int main(void)
{
	int	autoval;
	register int	regival;
	volatile int	volaval;
	static int	statval;

	globval = 1;
	autoval = 2;
	regival = 3;
	volaval = 4;
	statval = 5;

	if (setjmp(setjmpbuf) != 0){
		printf("after long jump:\n");
		printf("globval = %d,autoval = %d,regival = %d,volaval = %d,statval = %d\n",globval,autoval,regival,volaval,statval);
		exit(0);
	}

/*
 *Change valiables after setjmp(),but before longjmp()
 */
	globval = 95;
	autoval = 96;
	regival = 97;
	volaval = 98;
	statval = 99;
	fun1(autoval,regival,volaval,statval); 
	exit(0);
}

static void fun1(int i,int j,int k,int l)
{
	printf("in fun1():\n");
	printf("globval = %d,autoval = %d,regival = %d,volaval = %d,statval = %d\n",globval,i,j,k,l);
	fun2();
}

static void fun2(void)
{
	longjmp(setjmpbuf,1);
}
