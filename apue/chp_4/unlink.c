#include "apue.h"
#include "fcntl.h"

int main(void)
{

	if (open("link",O_RDWR) < 0){
		err_sys("open error");
	}
	if (unlink("link") < 0){
		err_sys("unlink error");
	}
	else{
		printf("file unlinking...\n");
		sleep(10);
		printf("unlinked\n");
	}
	return 0;
}
