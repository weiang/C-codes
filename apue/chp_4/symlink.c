#include "unistd.h"
#include "apue.h"

int main()
{
	size_t size;
	char buf[15];
	ssize_t val;

/*	if (symlink("/home/weiang","link") < 0){
		err_sys("symlink error");
	}
*/
	if ((val = readlink("link",buf,size)) < 0){
		err_sys("readlink error");
	}
	else{
	//	printf("link size :%d\n",val);
		printf("link to %s\n",buf);
		printf("link to file's size %d\n",size);
	}
	return 0;
}
