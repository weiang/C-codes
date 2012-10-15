#include "apue.h"
#include "sys/resource.h"

#define doit(name)	pr_limits(#name,name)


static void pr_limits(char *,int);

int main(void)
{
	#ifdef RLIMIT_AS
		doit(RLIMIT_AS);
	#endif
	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	exit(0);
}

static void pr_limits(char *name,int resource)
{
	struct rlimit	limit;
	
	if (getrlimit(resource,&limit) < 0){
		err_sys("getrlimit error for %s\n",name);
	}
	printf("%-14s ",name);
	if (limit.rlim_cur == RLIM_INFINITY)
		printf("(infinity) ");
	else 
		printf("%10ld ",limit.rlim_cur);
	if (limit.rlim_max == RLIM_INFINITY)
		printf("(infinity) ");
	else 
		printf("%10ld ",limit.rlim_max);
	putchar((int)'\n');
}
