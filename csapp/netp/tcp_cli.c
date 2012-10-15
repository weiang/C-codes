#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

void error_handle(char *msg)
{
	perror(msg);
	exit(-1);
}

int main(int argc, char *argv[])
{
	int	sockfd;
	unsigned short	port;
	in_addr_t	addr_in;
	struct sockaddr_in	ser_addr;
	int	len = 0;
	char	send_buf[1024];
	char	recv_buf[1024];

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))) 
		error_handle("Socket failed");
	bzero(&ser_addr, sizeof(ser_addr));
	ser_addr.sin_port = htons(atoi(argv[1]));
	ser_addr.sin_addr.s_addr = inet_addr("127.0.1.1");	/* inet_aton("127.0.1.1", struct in_addr ser_addr); */
	
	/* Connect */
	printf("Now connecting...\n");
	if (-1 == connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)))
		error_handle("Connect failed");
	
	/* Send msg to server */
	bzero(send_buf, sizeof(send_buf));
	sprintf(send_buf, "Hello!Server terminal!");
/*	if (-1 == write(sockfd, send_buf, strlen(send_buf))) {
		perror("Send failed");
		exit(-1);
	}
*/
	printf("Here\n");
	/* receiving msg from server */
	memset(recv_buf, 0, sizeof(recv_buf));
	if (-1 == (len = recv(sockfd, recv_buf, sizeof(recv_buf), 0)))
		error_handle("Recv failed");
	printf("Now receiving...\n");

	printf("Receive message:%s\n", recv_buf);
	close(sockfd);
	return 0;
}
