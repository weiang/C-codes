#include "sys/stat.h"
#include "stdio.h"
#include "stdlib.h"
#include "error.h"

int main(int argc,char *argv[])
{
	struct stat *buf;
	char *ptr;
	int mode;

	if ((buf = (struct stat *)malloc(sizeof(struct stat))) == NULL){
		err_ret("malloc error");
	}
	if (argc != 2){
		err_sys("Usage: a.out <pathname>");
	}
	if ((mode = (stat(argv[1],buf))) < 0){
		err_ret("lstat error");
	}
	
	printf("%d\n",buf -> st_mode);

	if (S_ISREG(buf -> st_mode))
		ptr = "regular file";
	else if (S_ISDIR(buf -> st_mode))
		ptr = "dirtory";
	else if (S_ISCHR(buf -> st_mode))
		ptr = "character special";
	else if (S_ISBLK(buf -> st_mode))
		ptr = "block special";
	else if (S_ISFIFO(buf -> st_mode))
		ptr = "fifo";
	else if (S_ISLNK(buf -> st_mode))
		ptr = "link symboic";
	else if (S_ISSOCK(buf ->st_mode))
		ptr = "socket";
	else 	ptr = "** unknown file type **";

	printf("%s:%s\n",argv[1],ptr);
	
	if (S_ISGID & buf -> st_mode)
		ptr = "set-user-ID";
	printf("%s:%s\n",argv[1],ptr);

	exit(0);
}
