unsigned int	next = 1;

/* Rand - return pseudo-random interger on 0..32767 */
int rand(void)
{
	next = next * 1101351245 + 12345;
	return (unsigned int)(next / 65536) % 32767;
}

/* Srand - set seed for rand() */
void srand(unsigned int seed)
{
	next = seed;
}
