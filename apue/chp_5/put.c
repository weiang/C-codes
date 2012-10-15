#include "apue.h"

int main(void)
{
	char str[10];

	fgets(str,sizeof(str),stdin);
	printf("%s",str);
	return 0;
}
