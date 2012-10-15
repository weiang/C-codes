#include "../csapp.h"

void error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int 	clientfd, port;
	char 	*host, buf[MAXLINE];
	struct sockaddr_in	cliaddr;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = atoi(argv[2]);

	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Scoket error");

	memset((char *)&cliaddr, 0, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(port);
	cliaddr.sin_addr.s_addr = inet_addr(host);

	if (connect(clientfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0)
		error("Connect error");
	printf("Now connecting...\n");
	 			
	read(clientfd, buf, sizeof(buf));
	printf("%s\n", buf);

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		write(clientfd, buf, strlen(buf));
		fputs(buf, stdout);
	}
	close(clientfd);
	exit(0);
}

