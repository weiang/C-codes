/*
 *find max subsequence sum
 */
/*version four*/

int MaxSubsequenceSum(const int sequence[],int length)
{
	int	this_sum,max_sum;
	int 	i;
	
	this_sum = max_sum = 0;
	for (i = 0;i < length;i ++){
		this_sum += sequence[i];
		if (this_sum > max_sum)
			max_sum = this_sum;
		else if (this_sum < 0)
			this_sum = 0;
	}
	return max_sum;
}
