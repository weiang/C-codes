#include "csapp.h"

void echo(int connfd);
void command(void);

int main(int argc,char *argv[])
{
	int	listenfd,connfd,port;
	socklen_t	clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in	clientaddr;
	fd_set	read_set,ready_set;

	if (argc != 2){
		fprintf(stderr,"Usage:%s <port> \n",argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	port = atoi(argv[1]);
	listenfd = open_linstenfd(port);
	
	FD_ZERO(&read_set);	/* Clear read set */
	FD_SET(STDIN_FILENO,&read_set);	/* Add stdin to read set */
	FD_SET(listenfd,&read_set);	/* Add listenfd to read set */

	while (1){
		ready_set = read_set;
		select(listenfd + 1,&ready_set,NULL,NULL,NULL);
		if (FD_ISSET(STDIN_FILENO,&ready_set)){
			command();
		}	/* Read command line from stdin */
		if (FD_ISSET(listenfd,&ready_set)){
			connfd = accept(listenfd,(struct socketaddr *)&clientaddr,&clientlen);
			echo(connfd);
			close(connfd);
		}	/* Echo client input until EOF */
	}

	return 0;
}

/* Command routine */
void command(void)
{
	char	buf[MAXLINE];
	if (!fgets(buf,MAXLINE,stdin))
		exit(EXIT_SUCCESS);	/* EOF */
	printf("%s",buf);	/* Process the input command */
}
