/* _CSAPP_H_ */
#ifndef	_CSAPP_H_	
#define _CSAPP_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <wait.h>
#include <setjmp.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXLINE	1024
#define MAXBUF	1024
#define MAX_HEAP	1024
#define RIO_BUFSIZE	8192
#define LISTENQ	100

typedef struct sockaddr SA;

typedef struct {
	int	rio_fd;
	int	rio_cnt;
	char	*rio_bufptr;
	char	rio_buf[RIO_BUFSIZE];
} rio_t;


pid_t Fork(void);

/* Error handling */
void unix_error(char *msg);
void posix_error(int code, char *msg);
void dns_error(char *msg);
void app_error(char *msg);

/* Unix I/O */
ssize_t	rio_readn(int fd, void *usrbuf, size_t n);
ssize_t	rio_writen(int fd, void *usrbuf, size_t	n);
void rio_readinitb(rio_t *rp, int fd);
ssize_t	rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t	rio_readnb(rio_t *rp, void *usrbuf, size_t n);

int open_clientfd(char *hostname, int port);
int open_listenfd(int port);

#endif	/* _CSAPP_H_ */
