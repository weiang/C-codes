#include "apue.h"

extern int system(const char *);
extern void pr_exit(int);

int main(int argct,char *argv[])
{
	int	status;
	
 	if (argct < 2){
		err_sys("commnd-line argument required");
	}
	if ((status = system(argv[1])) < 0){
		err_sys("system() error");
	}
	pr_exit(status);
	
	exit(0);
}
