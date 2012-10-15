#include "../csapp.h"

#define LENQ	10

static void echo(int connfd)
{
	char	buf[BUFSIZ];
	int	n;
	
	sprintf(buf, "Connected to server!\n", sizeof(buf));
	write(connfd, buf, strlen(buf));
	
	printf("Msg received from client:\n");
	while ((n = read(connfd, buf, BUFSIZ)) > 0)
		write(STDOUT_FILENO, buf, n);
	return;
}

void sig_child(int sig)
{
	while (waitpid(-1, 0, WNOHANG) > 0)
		;
	return;
}

void error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in	seraddr, cliaddr;
	int	listenfd, connfd;
	int	cli_len;

	signal(SIGCHLD, sig_child);	/* Install signal handler */

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Socket error");
	
	bzero((char *)&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listenfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0)
		error("Bind error");
	
	if (listen(listenfd, LENQ) < 0)
		error("Listen error");
	printf("Now listening...\n");

	cli_len = sizeof(cliaddr);	
	while (1) {
		if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cli_len)) < 0)
			error("Accept error");
		if (fork() == 0) {	/* Child process */
			printf("Connect build successfully!\n");
			close(listenfd);
			echo(connfd);
			close(connfd);
			exit(EXIT_SUCCESS);
		}	/* Parent process */
		close(connfd);
	}
	eixt(EXIT_SUCCESS);
}
