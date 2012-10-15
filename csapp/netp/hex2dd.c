#include "../csapp.h"

int main(int argc, char *argv[])
{
	unsigned int	net_address;
	struct in_addr	in;

	if (argc != 2) {
		printf("Usage: %s <hex address>\n", argv[0]);
		exit(0);
	}

	sscanf(argv[1], "%x", &net_address);
	in.s_addr = htonl(net_address);
	printf("%s\n", inet_ntoa(in));
}	
