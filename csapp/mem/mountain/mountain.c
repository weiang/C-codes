#define MAXBYTES	(1 << 23)
#define MAXELEMS	MAXBYTES / sizeof(int)

void test(int elems,int stride)	/* The test function */
{
	int	i,result = 0;
	volatile int	sink;
	extern int	data[MAXELEMS];	
	
	for (i = 0;i < elems;i += stride)
		result += data[i];
	sink = result;	/* So compiler doesn't optimize away the loop */
}

/* Run test(elems,stride) and return read throughput (MB/s) */
double run(int size,int stride,double Mhz)	/* Mhz represent CPU clock frequency */
{
	double	cycles;
	int	elems = size / sizeof(int);

	test(elems,stride);	/* Warm up the cache */
	cycles = fcyc2(test,elems,stride,0);	/* call test(elems,stride) */
	return (size /  stride) / (cycles /Mhz);	/* convert cycles to MB/s */
}
