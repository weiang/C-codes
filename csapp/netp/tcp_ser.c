#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int	listenfd,connfd;
	struct sockaddr_in	ser_addr;
	struct sockaddr_in	cli_addr;
	int	cli_len = 1;
	int	len = 0;
	char	recv_buf[1024];
	char	send_buf[1024];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listenfd) {
		perror("Socket failed");
		exit(-1);
	}

	bzero(&ser_addr, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// INADDR_ANY denote local host address
	ser_addr.sin_port = htons(atoi(argv[1]));	// Server port
	if (bind(listenfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0) {
		perror("Bind failed");
		exit(-1);
	}
	
	/* Listen */
	if (listen(listenfd, 10) < 0) {
		perror("Listen failed");
		exit(-1);
	}
	printf("Now listening...\n");
	
	while (1) {
		memset(&cli_addr, 0, sizeof(cli_addr));
		cli_len = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_len);
			if (-1 == connfd) {
			perror("Accept failed");
			exit(-1);
		}
		
		/* Receive msg from client */
		bzero(recv_buf, sizeof(recv_buf));
/*		printf("Now receiving...\n");
		len = read(connfd, recv_buf, sizeof(recv_buf));
		if (-1 == len) {
			perror("Recv failed");
			exit(-1);
		}
		printf("Recv from client is %s\n", recv_buf);
*/
		/* Send msg to client */
		printf("Now sending...\n");
		bzero(send_buf, sizeof(send_buf));
		sprintf(send_buf, "Hello! Client tcp terminal.");
		if (-1 == (len = send(connfd, send_buf, strlen(send_buf), 0))) {
			perror("Send failed");
			exit(-1);
		}
		
		printf("Send msg to client %s\n", send_buf);
		close(connfd);
	}
	close(listenfd);
	return 0;
}



