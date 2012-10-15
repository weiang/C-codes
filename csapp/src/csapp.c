#include "../csapp.h"

/*
handler_t *Signal(int signum, handler_t *handler)
{
	struct sigaction	action, old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);	// Block sigs of type being handled 
	action.sa_flags = SA_RESTART;	// Restart syscall if possible 

	if (sigaction(signum, &action, &old_action) < 0)
		unix_error("Signal error");
	return (old_action.sa_handler);
}
*/

/*
 * Robust I/O routain version
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
	size_t	nleft = n;
	char	*interbuf = usrbuf;
	ssize_t	nread;

	while (nleft > 0) {
		if ((nread = read(fd, interbuf, nleft)) < 0) {
			if (errno == EINTR)	/* Interrupted by sig handler return and call read() again */
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		interbuf += nread;
	}
	return (n - nleft);
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
	size_t	nleft = n;
	size_t	nwritten;
	char	*bufp = usrbuf;

	while (nleft > 0) {
		if (nwritten = write(fd, usrbuf, nleft) < 0) {
			if (errno == EINTR)
				nwritten = 0;
			else 
				return -1;	/* Errno set by write() */
		}
		nleft -= nwritten;
		bufp += nwritten;
	}
	return n;
}
		
void rio_readinitb(rio_t *rp, int fd)
{
	rp -> rio_fd = fd;
	rp -> rio_cnt = 0;
	rp -> rio_bufptr = rp -> rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
	int	cnt;
	
	while (rp -> rio_cnt <= 0) {
		rp -> rio_cnt = read(rp -> rio_fd, rp -> rio_buf, sizeof(rp -> rio_buf));
		if (rp -> rio_cnt < 0) {
			if (errno != EINTR)
				return -1;
		}
		else if (rp -> rio_cnt == 0)
			return 0;	/* EOF */		
		else 
				rp -> rio_bufptr = rp -> rio_buf;	/* Reset buffer ptr */
	}	
/* Copy min(n, rp -> rio_cnt) bytes from internal buf to user buf */	
	cnt = n;
	if (rp -> rio_cnt < n)
		cnt = rp -> rio_cnt;
	memcpy(usrbuf, rp -> rio_bufptr, cnt);
	rp -> rio_bufptr += cnt;
	rp -> rio_cnt -= cnt;
	return cnt;
}

ssize_t	rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
	int	n,rc;
	char	c, *bufp = usrbuf;
	
	for (n = 1;n < maxlen; n ++) {
		if ((rc = rio_read(rp, &c, 1)) == 1) {
			*bufp ++ = c;
			if (c == '\n')
				break;
		}
		else if (rc == 0) {
			if (n == 1)
				return 0;
			else 
				break;
		}
		else
			return -1;
	}
	*bufp = 0;
	return n;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
	size_t	nleft = n;
	ssize_t	nread;
	char 	*bufp = usrbuf;
	
	while (nleft > 0) {
		if ((nread = rio_read(rp, bufp, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;
			else 
				return -1;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}
	return (n - nleft);
}

int open_clientfd(char *hostname, int port)
{
	int	clientfd;
	struct hostent	*hp;
	struct sockaddr_in	serveraddr;

	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
 
	if ((hp = gethostbyname(hostname)) == NULL)
		return -2;
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)hp -> h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, hp -> h_length);
	serveraddr.sin_port = htons(port);
	
	if (connect(clientfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
		return -1;
	return clientfd;
}

int open_listenfd(int port)
{
	int	listenfd, optval = 1;
	struct sockaddr_in	serveraddr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
			(const void *)&optval, sizeof(int)) < 0)
		return -1;
	
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);
	if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
		return -1;
	
	if (listen(listenfd, LISTENQ) < 0)
		return -1;

	return listenfd;
}

/*
 *Error handling 
 */

void unix_error(char *msg)	/* Unix-style error */
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}

void posix_error(int code, char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(code));
	exit(0);
}

void dns_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, h_errno);
	exit(0);
}

void app_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

