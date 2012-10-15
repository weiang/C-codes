#include "../csapp.h"

/*
 * Created by weiang
 * Date: 8/20/2012
 */

void mmapcopy(int fd, int size)
{
	char	*bufp;

	bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (bufp == MAP_FAILED)
		unix_error("Map error");
	
	if (write(STDOUT_FILENO, bufp, size) < 0)
		unix_error("Write error");

	return;
}

/* Mmapcopy driver */
int main(int argc, char *argv[])
{
	struct stat	stat;
	int	fd;

	/* Check for required command */
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Copy the input argument to stdout */
	fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0)
		unix_error("Open error");

	fstat(fd, &stat);
	mmapcopy(fd, stat.st_size);
	exit(EXIT_SUCCESS);
}
