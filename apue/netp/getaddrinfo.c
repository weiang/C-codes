#include "../apue.h"

void
print_protocol(struct addrinfo	*aip)
{
	printf("Protocol :");
	switch (aip -> ai_protocol) {
		case 0:
			printf("Deault");
			break;
		case IPPROTO_TCP:
			printf("TCP");
			break;
		case IPPROTO_UDP:
			printf("UDP");
			break;
		case IPPROTO_RAW:
			printf("RAW");
		default:
			printf("Unknown (%d)", aip -> ai_protocol);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	struct addrinfo	hint;
	struct addrinfo	*ailist, *aip;
	const char	*addr;
	struct sockaddr_in	*sinp;
	int	err;
	char	abuf[INET_ADDRSTRLEN];

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <host> <service>\n", argv[0]);
		exit(0);
	}

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = 0;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

	if (getaddrinfo(argv[1], argv[2], &hint, &ailist) < 0) {
		fprintf(stderr, "Getaddrinfo error\n");
		exit(0);
	}
	for (aip = ailist; aip != NULL; aip = aip -> ai_next) {
		print_protocol(aip);
		if (aip -> ai_family = AF_INET) {
			sinp = (struct sockaddr_in *)(aip -> ai_addr);
			addr = inet_ntop(AF_INET, &(sinp -> sin_addr), abuf, INET_ADDRSTRLEN);
			printf("Host name:  %s\n", addr ? addr : "Unknown");
			printf("Port: %d\n", ntohs(sinp -> sin_port));
		}
	}
	exit(0);
}
			
		
