#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

struct timespec *maketimeout(struct timespec *tp,int secs)
{
	struct timeval	now;

	gettimeofday(&now,NULL);
	tp -> tv_sec = now.tv_sec + secs;
	tp -> tv_nsec = now.tv_usec * 1000;
	return tp;
}
