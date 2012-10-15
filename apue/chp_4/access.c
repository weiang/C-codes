#include "apue.h"
#include "fcntl.h"

int main(int argc,char *argv[])
{
	int	val;

	if (argc != 2){
		err_quit("usage:a.out <pathname>");
	}
	if ((val = access(argv[1],R_OK)) < 0){
		err_ret("access error for %s",argv[1]);
	}
	else{
		printf("read access OK.val = %d\n",val);
	}
	if (open(argv[1],O_RDONLY) < 0){
		err_ret("open error for %s",argv[1]);
	}
	else{
		printf("open for reading OK\n");
	}
	exit(0);
}		
