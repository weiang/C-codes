#include "apue.h"
#define MAXSIZE 100

int main(void)
{
	pid_t pid;
	char command[MAXSIZE];
	int status;	

	printf("%%");
	while (fgets(command,MAXSIZE,stdin) != NULL){
		if (command[strlen(command) - 1] == '\n'){
			command[strlen(command) - 1] = 0;	/*replace newline with NULL */
		}

		/*child process*/
		if ((pid = fork()) < 0){
			err_sys("fork error");
		}
		else if (pid == 0){
			execlp(command,command,(char *)0);
			err_ret("couldn't exectute:%s",command);
			exit(127);
		}
	
		/*parent process*/
		if ((pid == waitpid(pid,&status,0)) < 0){
			err_sys("waitpid error");
		}
		printf("%%");
	}
	exit(0);
}		
