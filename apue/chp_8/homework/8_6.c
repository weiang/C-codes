#include "apue.h"

int main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0){
		err_sys("fork error");
	}

	else if (pid == 0){
		exit(1);
	}
	else {
		sleep(2);
		if (system("ps -s") < 0){
			err_sys("system() error");
		}
	}
	exit(0);
}

