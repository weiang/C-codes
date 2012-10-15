#include "apue.h"
#include "errno.h"
#include "fcntl.h"

int main(int argc,char *argv[])
{
	void set_fl(int ,int);
	int fd;
	char buf[] = "hello world!";

	if (argc != 2)
		err_ret("Usage: a.out <pathname>");

	if ((fd = (open(argv[1],O_RDWR))) < 0){
		err_sys("open error");
	}
//	set_fl(fd,O_RDWR);
//	fcntl(fd,F_SETFL,O_RDONLY);
	if (write(fd,buf,strlen(buf)) != strlen(buf)){
		err_sys("write error");
	}
	exit (0);
}

void set_fl(int fd,int flags)
{
	int val;

	if ((val = fcntl(fd,F_GETFL,0)) < 0){
		err_sys("fcntl F_GETFL error");
	}
	
	val |= flags; /*turn in flags*/

	if (fcntl(fd,F_SETFL,val) < 0){
		err_sys("fcntl F_SETFL error");
	}
}
