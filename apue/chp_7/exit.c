#include "apue.h"

static void my_exit1(void);
static void my_exit2(void);
void usr_fun(void);

int main(void)
{
	if (atexit(my_exit1) != 0)
		err_sys("cat't register my_exit1");
	if (atexit(my_exit2) != 0)
		err_sys("cat't register my_exit2");
	usr_fun();
	printf("main fun exit\n");
	return 0;
}

void usr_fun(void)
{
	printf("usr fun\n");
}
static void my_exit1(void)
{
	printf("my_exit1 fun\n");
	exit(0);
}

static void my_exit2(void)
{
	printf("my_exit2 fun\n");
}

