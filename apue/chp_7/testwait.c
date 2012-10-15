#include "apue.h"
#include "sys/wait.h"

extern void pr_exit(int);

int main(void)
{
	pid_t	pid;
	int	status;
	
/*
 *first child:normal exit
 */
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0){
		exit(7);
	}
	if (waitpid(pid,&status,0) != pid)
		err_sys("waitpid error");
	pr_exit(status);

/*
 *second child:abnormal exit
 */
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		abort();
	if (waitpid(pid,&status,0) != pid)
		err_sys("waitpid error");
	pr_exit(status);
	
/*
 *third child:divide by 0 generates SIGFPE
 */
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		status /= 0;
	if (waitpid(pid,&status,0) != pid)
		err_sys("waitpid error");
	pr_exit(status);
	exit(0);
}	
