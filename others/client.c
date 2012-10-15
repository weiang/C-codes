#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SERVER_PORT	20000
#define	CLIENT_PORT	((20001 + rand()) % 65536)

void 
error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	int	serfd, clifd, len;
	struct sockaddr_in	cliaddr, seraddr;
	char 	buf[BUFSIZ];
	FILE	*recvfile;
	int	n;
	

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <IP addr> < filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((clifd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Socket error");
	
	srand(time(NULL));

	bzero((char *)&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(CLIENT_PORT);
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bzero((char *)&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERVER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (bind(clifd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0)
		error("Bind error");
	if (connect(clifd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0)
		error("Connect error");
	
	printf("Connected to server %s\n", argv[1]);
	
	len = recv(clifd, buf, sizeof(buf), 0);
	if (len < 0)
		error("Recv error");
	printf("Receieved msg: %s\n", buf);
	
	if (send(clifd, argv[2], sizeof(argv[2]), 0) < 0)
		error("Send error");
	if ((recvfile = fopen(argv[2], "w")) == NULL)
		error("Fopen error");
	while ((n = recv(clifd, buf, sizeof(buf), 0)) > 0)
		fprintf(recvfile,buf);
	if (n < 0) 
		error("Write error");
	fclose(recvfile);
	exit(EXIT_SUCCESS);
}	
