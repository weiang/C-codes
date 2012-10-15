#include "fcntl.h"
#include "error.h"

char	buffer[2048];
int	version = 1;

int main(int argc,char *argv[])
{
	int	copy(int ,int);
	int	fdold,fdnew;
	
	if (argc != 3){
		err_sys("Usage:copy <oldfilename> <newfilename>");
	}
	
	if ((fdold = open(argv[1],O_RDONLY)) < 0){
		err_sys("%s:open error",argv[1]);
	}
	if ((fdnew = creat(argv[2],0666)) < 0){
		err_sys("%s:creat error",argv[2]);
	}
	if (copy(fdold,fdnew) < 0){
		err_sys("copy error");
	}
	exit(0);
}

int copy(int fdold,int fdnew)
{
	int	count;
	
	while ((count = read(fdold,buffer,sizeof(buffer))) > 0){
		if (write(fdnew,buffer,count) != count){
			err_sys("write error");
		}
	}
	if (count < 0){
		err_sys("read error");
	}
	exit(0);
}
	
