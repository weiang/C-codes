#include <stdio.h>
#include <fcyc2.h>	/* K-best measurement timing routines */
#include "clock.h"	/* Routines to access the cycle counter */

#define MINBYTES	(1 << 10)	/* Working set size ranges from 1 KB */
#define MAXBYTES	(1 << 23)	/* ... up to 8 MB */
#define MAXSTRIDE	16		/* Stride range from 1 to 16 */
#define	MAXELEMS	MAXBYTES / sizeof(int)

int	data[MAXELEMS];	/* The array we'll be traversing */

/* Initialize each element in data to 1 */
void init_data(int *data,int size);

int main(void)
{
	int	size;	/* Working set size (in bytes) */
	int	stride;	/* Stride (in array elements) */
	double	Mhz;	/* Clock frequence */

	init_data(data,MAXELEMS);
	Mhz = mhz(0);	/* Estimate the clock frequency */
	for (size = MAXBYTES;size >= MINBYTES;size >> 1){
		for (stride = 1;stride <= MAXSTRIDE;stride ++){
			printf("%.1f\t",run(size,stride,Mhz));
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}


/* Initilize data array to 1 routain */
void init_data(int *data,int size)
{
	int	i;
	
	if (data != NULL){	
		for (i = 0;i < size;i ++){
			data[i] =  1;
		}
	}
	
	return;
}
