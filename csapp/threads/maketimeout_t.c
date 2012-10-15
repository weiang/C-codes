#include "csapp.h"

struct timespec *maketimeout_u(int secs);

static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

struct timespec *maketimeout_t(int secs)
{
	struct timespec	*sp;	/* Shared */
	struct timespec	*up = malloc(sizeof(struct timespec));	/* Unshared */

	pthread_mutex_lock(&mutex);
	sp = maketimeout_u(secs);
	*up = *sp;	/* Copy the shared struct to the unshared one */
	pthread_mutex_unlock(&mutex);
	return up;
}


