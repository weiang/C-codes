#include "../csapp.h"

void foo(void);
void bar(void);

int	error1 = 0;
int	error2 = 1;

jmp_buf	buf;

int main(void)
{
	int	rv;
	
	rv = setjmp(buf);
	if (rv == 0)
		foo();
	else if (rv == 1) {
		fprintf(stdout, "Detected an error1 condition from foo()!\n");
	}
	else if (rv == 2) {
		fprintf(stdout, "Detected an error2 condition from foo()!\n");
	}
	else 
		fprintf(stdout, "Unknown error condition from foo()!\n");
	exit(EXIT_SUCCESS);
}

/* Deeply nested function foo */
void foo(void)
{
	if (error1)
		longjmp(buf, 1);
	bar();
	return;
}

void bar(void)
{
	if (error2)
		longjmp(buf, 2);
	return;
}
