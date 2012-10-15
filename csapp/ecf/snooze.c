#include <unistd.h>
#include <stdio.h>

unsigned int snooze(unsigned int secs)
{
	unsigned int	left_time;
	
	left_time = sleep(secs);
	printf("Slept for %u of %u secs.\n", secs - left_time, secs);
	return left_time;
}

