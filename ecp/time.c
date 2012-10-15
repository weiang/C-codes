/* Get Max time of Linux system */

#include "stdio.h"
#include "time.h"

int
main(void)
{
	time_t	big_time = 0x7fffffff;
	printf("bigest time = %s\n",ctime(&big_time));
	return 0;
}
