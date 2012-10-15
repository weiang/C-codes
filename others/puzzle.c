#include <stdio.h>

static	count = 0;
int puzzle(int n)
{
	printf("puzzle(%d)\n\t", n);
	count ++;
	if (n == 1) 
		return 1;
	if (n % 2 == 0)
		return puzzle(n / 2);
	else return puzzle(3 * n + 1);
}


int main(void)
{
	int	i;
	int	max = 0;
	int	num = 1;

	for(i = 1;i <= 1000;i ++) {
		count = 0;
		puzzle(i);
		if (count > max){
			max = count;
			num = i;
		}
		printf("\n");
	}
	printf("Max = %d, num = %d\n", max, num);
	return 0;
}
