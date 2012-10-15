#include "../apue.h"

#define MAXADDRLEN	256
#define BUFLEN	128

extern int connect_retry(int, const struct sockaddr *, socklen_t);

void
print_uptime(int sockfd)
{
	char	buf[BUFLEN];
	int	n;

	while ((n = recv(sockfd, buf, sizeof(buf) , 0)) > 0)
		write(STDOUT_FILENO, buf, n);
	if (n < 0) 
		err_sys("Recv error");
}
/*
int 
main(void)
{
	struct sockaddr_in	ser_addr;
	int	clifd, addr_len;

	if ((clifd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("Socket error");

	memset(&ser_addr, 0, sizeof(ser_addr));
	addr_len = sizeof(ser_addr);

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ser_addr.sin_port = htons(8000);
	
	printf("Now connecting...\n");
	if (connect_retry(clifd, (struct sockaddr *)&ser_addr, addr_len) < 0)
		err_sys("Connect error");
	printf("Here\n");
	print_uptime(clifd);
	
	exit(0);
}	
*/

int main(void)
{
	
