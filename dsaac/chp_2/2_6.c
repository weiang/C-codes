/*
 *find max sub sequence sum 
 */
/*version two*/

int MaxSubsequenceSum(const int sequence[],int length)
{
	int	this_sum,max_sum;
	int	i,j;
	
	max_sum = 0;
	for (i = 0;i < length;i ++){
		this_sum = 0;
		for (j = i;j < length;j ++){
			this_sum += sequence[j];
			if (this_sum > max_sum){
				max_sum = this_sum;
			}
		}
	}
	return max_sum;
}
