#include "../csapp.h"

int main(int argc, char *argv[])
{
	struct in_addr	inaddr;
	unsigned int	host_addr;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <dotted-decimal string>\n", argv[0]);
		exit(0);
	}
	
	inet_aton(argv[1], &inaddr);
	host_addr = ntohl(inaddr.s_addr);
	printf("0x%x\n", host_addr);
	return 0;
}
