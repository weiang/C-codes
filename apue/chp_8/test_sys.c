#include "apue.h"
#include "sys/wait.h"

extern int system(const char *);
extern void pr_exit(int);

int main(void)
{
	int	status;
	
	
/*	if ((status = system("ls -al")) < 0){
		err_sys("system() error");
	}
	pr_exit(status);
*/	
	
/*	if ((status = system("nosuchcmdstring")) < 0){
		err_sys("system() error");
	}
	pr_exit(status);
*/	
	if ((status = system("who;exit 44")) < 0){
		err_sys("system() error");
	}
	pr_exit(status);

	exit(0);
}
