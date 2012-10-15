#include "apue.h"

/*check what kind of buffer standard I/O use*/
void pr_stdio(const char *,FILE *);

int main(void)
{
	FILE	*fp;
	
	fputs("enter any character\n",stdout);
	if (getc(stdin) == EOF){
		err_sys("getc error");
	}
	fputs("one lne to standard err\n",stderr);

	pr_stdio("stdin",stdin);
	pr_stdio("stdout",stdout);
	pr_stdio("stderr",stderr);

	if ((fp = fopen("/etc/motd","r")) == NULL){
		err_sys("fopen error");
	}
	if (getc(fp) == EOF){
		err_sys("getc error");	/*check whether /etc/motd is empty*/
	}
	pr_stdio("/etc/motd",fp);
	exit(0);
}

void pr_stdio(const char *name,FILE *fp)
{
	printf("stream = %s ",name);

/*The following code checking method is not portable*/
	if (fp -> _IO_file_flags & _IO_UNBUFFERED){
		printf("unbuffered,");
	}
	else if (fp -> _IO_file_flags & _IO_LINE_BUF){
		printf("line buffered,");
	}
	else	printf("full buffered,");
	printf("buffer size = %ld\n",fp -> _IO_buf_end - fp -> _IO_buf_base);
}

