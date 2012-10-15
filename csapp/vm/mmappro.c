/*	
 * Use mmap to change "Hello world!\n" in file hello.txt to "Jello,world!\n"
 */

#include "../csapp.h"

int main(void)
{
	int	fd;
	char	*bufp;
	size_t	size;
	struct stat	stat;	

	if ((fd = open("hello.txt", O_RDONLY)) < 0)
		unix_error("Open error");
	
	if (fstat(fd, &stat) < 0)
		unix_error("Stat error");
	if (mmap(bufp, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0) == NULL)
		unix_error("Mmap error");
	bufp[0] = 'J';
	printf("%s", bufp);
	fflush();
	close(fd);
	exit(EXIT_SUCCESS);
}
