/* First program of "Pointers ON c" */
/* To get used to c programming */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_COLS	20
#define	MAX_INPUT	1000

int	read_column_numbers(int columns[],int max);
void	rearrange(char *output,char const *input,int,int const columns[]);

int main(void)
{
	int	n_columns;
	int	columns[MAX_COLS];
	char	input[MAX_INPUT];
	char	output[MAX_INPUT];

	n_columns = read_column_numbers(columns,MAX_COLS);
	
	while (gets(input) != NULL){	
		printf("Original input: %s\n",input);
		rearrange(output,input,n_columns,columns);
		printf("Rearrange line: %s\n",output);
	}
	return EXIT_SUCCESS;
}

int read_column_numbers(int columns[],int max)
{
	int	count = 0;
	int	ch;

	while (count < max && scanf("%d",&columns[count]) == 1 && columns[count] >= 0){
//		printf("%d\t",columns[count]);
		count ++;
	}
	if (count & 0x01){
		puts("Last column number is not paired!\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = getchar()) != EOF && ch != '\n')
			;

	return count;
}


void rearrange(char *output,char const *input,int n_columns,int const columns[])
{
	int	col;
	int	out_col;
	int	len;
	
	len = strlen(input);
	out_col = 0;

	for (col = 0;col < n_columns;col += 2){
		int nchars = columns[col + 1] - columns[col] + 1;

		if (columns[col] >= len || out_col == MAX_INPUT - 1)
			break;
		if (out_col + nchars > MAX_INPUT - 1)
			nchars = MAX_INPUT - out_col - 1;
		
	strncpy(output + out_col,input + columns[col],nchars);
	out_col += nchars;
	}
	output[out_col] = '\0';
}
