#include "stdio.h"
#include "time.h"

int 
main(void)
{
	time_t	big_time = 0x7fffffff;

	printf("bigest time = %s\n",asctime(gmtime(&big_time)));
	return 0;
}
