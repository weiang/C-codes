#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


int	x[2] = {1, 2};
int	y[2] = {1, 2};
int	z[2];

int main(void)
{
	void	*handle;
	void	(*addvec)(int *, int *, int *, int);
	char	*error;

	/* Dynamically load shared library that contains addvec() */
	handle = dlopen("./libvector.so",RTLD_LAZY);
	if (!handle) {
		fprintf(stderr,"%s\n",dlerror());
		exit(EXIT_FAILURE);
	}

	/* Get a pointer to the addvec() function we just loaded */
	addvec = dlsym(handle,"addvec");
	if ((error = dlerror()) != NULL) {
		fprintf(stderr,"%s\n",error);
		exit(EXIT_FAILURE);
	}
	
	/* Now we can call addvec() */
	addvec(x, y, z, 2);
	printf("z = [%d %d]\n",z[0], z[1]);

	/* Unload the shared library */
	if (dlclose(handle) < 0){
		fprintf(stderr,"%s\n",dlerror());
		exit(EXIT_FAILURE);
	}

	return 0;
}
