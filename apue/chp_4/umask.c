#include "apue.h"
#include "fcntl.h"

#define RWRWRW	(S_IRUSR |S_IWUSR |S_IRGRP |S_IWGRP |S_IROTH |S_IWOTH)
int main(void)
{
	
/*creat a file with rwxrwxr-x*/
	umask(0577);
	if (creat("foo",RWRWRW) == 0)
		err_sys("open error");
	umask(S_IRGRP|S_IROTH |S_IWOTH);
	if (creat("bar",RWRWRW) < 0)
		err_sys("creat error for bar");
	exit(0);
}
