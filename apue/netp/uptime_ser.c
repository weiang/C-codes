#include "../apue.h"

#define QLEN	10
#define BUFSIZE	128

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX	256
#endif

int initserver(int type, const struct sockaddr *addrp, socklen_t len, int qlen)
{
	int	sockfd;

	if ((sockfd = socket(addrp -> sa_family, type, 0)) < 0)
		err_sys("Socket error");
	if (bind(sockfd, addrp, len) < 0) 
		err_sys("Bind errror");

	printf("Now listening...\n");
	if (listen(sockfd, qlen) < 0)
		err_sys("Listen error");
	return sockfd;
}
	
void server(int listenfd)
{
	FILE	*fp;
	int	connfd;
	char	buf[BUFSIZE];
	
	printf("Here\n");
	connfd = accept(listenfd, NULL, NULL);
	if (connfd < 0) {
		fprintf(stderr, "Ruptimed: accept error: %s", strerror(errno));
		exit(1);
	}
	printf("Have accept\n");

	for (;;) {
		if ((fp = popen("usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "Error: %s\n", strerror(errno));
			printf("%s\n", buf);
			send(connfd, buf, strlen(buf), 0);
		}
		else {
			while (fgets(buf, BUFSIZE, fp) != NULL) 
				send(connfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(connfd);
	}
}

int 
main(void)
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo hint;
	int	listenfd, err, n;
	char	*host;

#ifdef	_SC_HOST_NAME_MAX
	n = sysconf(_SC_HOST_NAME_MAX);
	if (n < 0)
#endif
		n = HOST_NAME_MAX;			
	host = malloc(n);
	if (host == NULL)
		err_sys("Malloc error");
	if (gethostname(host, n) < 0)
		err_sys("Gethostname error");
	
	hint.ai_flags = AI_CANONNAME;
	hint.ai_protocol = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_addrlen = 0;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	hint.ai_canonname = NULL;
	if ((err = getaddrinfo(host, NULL, &hint, &ailist)) != 0) {
		fprintf(stderr, "ruptimed: getaddinfo errror: %s", gai_strerror(err));
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip -> ai_next) {
		if ((listenfd = initserver(SOCK_STREAM, aip -> ai_addr, aip -> ai_addrlen, QLEN)) >= 0) {
		server(listenfd);
		exit(0);
		}
	}
	exit(1);
}


