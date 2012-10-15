#include "stdio.h"
#include "stdlib.h"
#include "string.h"
extern int MaxSubsequenceSum(int *,int);

int main(void)
{
	int arr[]={4,-3,5,-2,-1,2,6,-2};

	printf("max sub sum = %d\n",MaxSubsequenceSum(arr,sizeof(arr) / sizeof(int)));
	return 0;
}
