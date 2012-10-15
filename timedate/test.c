#include "datetime.h"
#include "stdio.h"
#include "time.h"

int main(void)
{
	TIMETYPE t;
	gettime(&t);
	printf("hour = %d,min = %d,sec = %d\n",t.hour,t.min,t.sec);
	return 0;
}
