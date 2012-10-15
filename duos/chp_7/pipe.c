#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char str1[]="from parent";
char str2[]="form child";

int main(void)
{
	int to_par[2];
	int to_child[2];
	char buf[256];
	int count;

	pipe(to_par);
	pipe(to_child);

	if (fork() == 0){
		close(0);
		dup(to_par[0]);
		close(1);
		dup(to_child[1]);
		close(to_par[0]);
		close(to_par[1]);
		close(to_child[0]);
		close(to_child[1]);
		
		count = read(0,buf,strlen(buf));
		write(1,str2,strlen(str2));
	printf("child's buf:%s\n",buf);
	}

/*parent process*/
	close(0);
	dup(to_par[1]);
	close(1);
	dup(to_child[0]);
	close(to_par[0]);
	close(to_par[1]);
	close(to_child[0]);
	close(to_child[1]);
	
	for(;;){
		write(0,str1,strlen(str1));
		read(1,buf,strlen(buf));
	}
	printf("parent's buf:%s\n",buf);
}
