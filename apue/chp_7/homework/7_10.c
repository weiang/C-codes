#include "apue.h"

int main(void)
{	
	int fun1(int);

	printf("%d\n",fun1(0));
	return 0;
}

int fun1(int val)
{
	int *ptr;
	if (val == 0){
		int	val;
		val = 5;
		ptr = &val;
	}
	return *ptr + 1;
}
