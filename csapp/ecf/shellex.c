/*  A simple shell routime */
#include "../csapp.h"

#define MAXARGS	128

/* Function prototypes */
void eval(char *cmdline);	/* Evaluate a command line */
int parseline(char *buf, char **argv);	/* Parse command line to get arguement list */
int builtin_command(char **argv);	/* Decide whether first arguement of the argv list is a builtin command
					 * If so, run it and return true */
extern char	**environ;
int main(void)
{
	char cmdline[MAXLINE];	/* Command line */

	while (1) {
		/* Read */
		printf("> ");
		if (fgets(cmdline, MAXLINE, stdin) < 0)
			unix_error("Command line read error");
		if (feof(stdin))
			exit(EXIT_SUCCESS);
	
		/* Evaluate */
		eval(cmdline);
	}
}

/* Eval() routine */
void eval(char *cmdline)
{
	char	*argv[MAXARGS];	/* Argument list of execve() */
	char	buf[MAXLINE];	/* Holds modified command line */
	int	bg;	/* Should the job run in bg or fg? */
	pid_t	pid;

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;	/* Ignore empty command line */

	if (!builtin_command(argv)) {
		if ((pid = Fork()) == 0) {	/* Child runs user's job */
			if (execve(argv[0], argv, environ) < 0) {
				printf("%s: Command not found.\n", argv[0]);
				exit(EXIT_SUCCESS);
			}
		}

		/* Parent wait for foreground job to terminate */
		if (!bg) {
			int	status;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("Waitpid error");
		}
		else
			printf("%d %s", pid, cmdline);
	}
	return;
}
 
/* Builtin_command() routine */
int builtin_command(char **argv)
{
	if (!strcmp(argv[0], "quit"))	/* Quit command */
		exit(0);
	if (!strcmp(argv[0], "&"))	/* Ignore singleton */
		return 1;
	return 0;	/* Not a builtin command */
}

/* Parse the command line and build the arguement list */
int parseline(char *buf, char **argv)
{
	char	*delim;
	int	argc;
	int	bg;
	
	buf[strlen(buf) - 1] = ' ';
	while (*buf && (*buf == ' '))
		buf ++;
	
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc ++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' '))
			buf ++;
	}
	argv[argc] = NULL;
	
	if (argc == 0)
		return 1;
	
	if ((bg = (*argv[argc - 1] == '&')) != 0)
		argv[--argc] = NULL;
	
	return bg;
}
