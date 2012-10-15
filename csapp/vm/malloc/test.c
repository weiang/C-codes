#include "../../csapp.h"

int main(void)
{
	char	*p;

	p = (char*)malloc(13);
	strcpy(p,"Hello world\n");
	printf("%s",p);
	return 0;
}
