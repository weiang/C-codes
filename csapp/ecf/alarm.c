#include "../csapp.h"

void alarm_handler(int msg);	/* SIGALRM signal handler */

int main(void)
{
	signal(SIGALRM, alarm_handler);	/* Install signal handler */

	alarm(1);	/* Send SIGALRM to itself in 1 sec */

	while (1) {
		;
	}	/* Signal handler returns control here each time */

	exit(EXIT_SUCCESS);
}

void alarm_handler(int msg)
{
	static int	beep = 0;

	if (beep ++ < 5){
		printf("BEEP!\n");
		alarm(1);
	}
	else {
		printf("BOOM!\n");
		exit(EXIT_SUCCESS);
	}
}

