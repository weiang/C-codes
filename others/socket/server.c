#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>

#define	SERVER_PORT	20000
#define	LENQ	10

void
error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
	struct sockaddr_in	cliaddr, seraddr;
	char	buf[BUFSIZ];
	int	serfd, connfd;
	int	cli_len;
	FILE	*sendfile;
	int	n;
	if ((serfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Sock error");
		
	bzero((char *)&cliaddr, sizeof(cliaddr));
	
	bzero((char *)&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERVER_PORT);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(serfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0)
		error("Bind error");
	
	if (listen(serfd, LENQ) < 0)
		error("Listen error");
	printf("Now listening...\n");

	cli_len = sizeof(cliaddr);
	
	while (1) {
		connfd = accept(serfd, (struct sockaddr *)&cliaddr, &cli_len);
		if (connfd < 0)
			error("Accept error");
		printf("Connected with %s\n", inet_ntoa(cliaddr.sin_addr));
		sprintf(buf, "Welcome to connect to server\n");
		if (send(connfd, buf, sizeof(buf), 0) < 0)
			error("Send error");

		printf("Now sending file...\n");
		strcpy(buf, "Now receiving file...\n");
		if (send(connfd, buf, sizeof(buf), 0) < 0)
			error("Recv error");
//		if (recv(connfd, buf, sizeof(buf), 0) < 0)
//			error("Can't receive file name\n");
		if ((sendfile = fopen("server.c", "r")) == NULL)
			error("Fopen error");
		while ((n = fscanf(sendfile, buf, sizeof(buf))) > 0)
			send(connfd, buf, n, 0);
		printf("Send end!\n");
		if (n < 0)
			error("Read error");
		fclose(sendfile);
		close(connfd);
	}
	close(serfd);
	exit(EXIT_SUCCESS);
}
	

