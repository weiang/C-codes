#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"

int main(int agrc,char *argv[])
{
	off_t offset;
	if ((STDIN_FILENO = open("argv[1]",O_RDONLY|O_CREAT)) == -1){
		printf("open %s file failed!\n",argv[1]);
	}
	if (lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
		printf("can't seek!\n");
	}
	else printf("seek OK!\n");
	exit(0);
}
