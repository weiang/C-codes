#include "../csapp.h"

int main(int argc, char *argv[])
{
	void	*bufp;
	char	readbuf[MAXBUF];
	int	fd;	
	int	size = 0, n;

	if (argc != 2) {
		fprintf(stdout, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) 
		unix_error("open error");
	
	/* Count the size of file argv[1] */
	while ((n = read(fd, &readbuf, sizeof(readbuf))) > 0)
		size += n;
//	printf("%d\n", size);

	/* Map file argv[1] on disk to virtual memory start at bufp */
	bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (bufp == MAP_FAILED)
		unix_error("Map error");
	if (write(STDOUT_FILENO, bufp, size) < 0)
		unix_error("Write error");

	close(fd);
	exit(EXIT_SUCCESS);
}
