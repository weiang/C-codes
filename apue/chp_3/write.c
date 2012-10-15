#include "unistd.h"
#include "fcntl.h"
#include "aupe.h"

int main(int argc,char *argv[])
{
	int val;
	int fd;

	if ((fd = open("./test",O_RDWR)) < 0){
		err_sys("open failed");

	if ((val = fcntl(fd,F_SETFD,
