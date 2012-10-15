#include "../csapp.h"

int main(int argc, char *argv[])
{
	struct stat	state;
	char	*readper, *type;

	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return -1;
	}

	stat(argv[1], &state);
	
	if (S_ISREG(state.st_mode)) 
		type = "Regular";
	else if (S_ISDIR(state.st_mode))
		type = "Directory";
	else if (S_ISSOCK(state.st_mode))
		type = "Socket";
	else 
		type = "Others";
	
	if (S_IRUSR & state.st_mode)
		readper = "Yes";
	else 
		readper = "No";

	printf("type :%s, readpermission:%s\n", type, readper);
	return 0;
}
