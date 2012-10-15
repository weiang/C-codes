#include "../apue.h"

int initserver(int type, const struct sockaddr *addr, socklen_t	alen, int qlen)
{
	int	listenfd;
	
	if ((listenfd = socket(addr -> sa_family, type, 0)) < 0) 
		err_quit("Socket error");
	if (bind(listenfd, addr, alen) < 0)
		err_quit("Bind error");
	if ((type == SOCK_STREAM) || (type == SOCK_SEQPACKET)) {
		if  (listen(listenfd, qlen) < 0) {
			close(listenfd);
			err_quit("Listen error");
		}
	}
	return listenfd;
}	
