/*
 *find max subsequence sum
 */
/*version one*/

int MaxSubsequenceSum(const int sequence[],int length)
{
	int	this_sum,max_sum = 0;
	int	i,j,k;

	for (i = 0;i < length;i ++){
		for (k = i;k < length;k ++){
			this_sum = 0;
			for (j = i;j <= k;j ++){
				this_sum += sequence[j];
			}
			if (this_sum > max_sum){
				max_sum = this_sum;
			}
		}
	}
	return max_sum;
}
