#include "apue.h"
#include "sys/wait.h"
#include "error.h"

void pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination,exit status = %d or %d\n",WEXITSTATUS(status),status >> 8);
	else if(WIFSIGNALED(status))
		printf("abnormal termination,singal number = %d%s\n",WTERMSIG(status),
#ifdef WCOREDUP
		WCOREDUP(status) ? " (core file generated)" :"");
#else 		
		" ");
#endif

	else if (WIFSTOPPED(status))
		printf("child stopped,signal number = %d\n",WSTOPSIG(status));
}
