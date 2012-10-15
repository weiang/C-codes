/*
 *find max subsequence sum 
 */
/*version three*/
static int MaxSubSum(const int *,int,int);
static int Max3(int,int,int);

static int Max3(int i,int j,int k)
{
	int tmp;
	tmp = (i > j ? i : j);
	if (tmp > k)
		return tmp;
	else return k;
}

int MaxSubsequenceSum(const int sequence[],int length)
{
	return MaxSubSum(sequence,0,length - 1);
}

static int MaxSubSum(const int sequence[],int left,int right)
{
	int max_left_sum,max_right_sum;
	int max_left_border_sum,max_right_border_sum;
	int left_border_sum,right_border_sum;
	int center,i;
	
	if (left == right){
		if (sequence[left] > 0){
			return sequence[left];
		}
		else 
			return 0;
	}	/*base case*/
	
	center = (left + right) / 2;
	max_left_sum = MaxSubSum(sequence,left,center);
	max_right_sum = MaxSubSum(sequence,center + 1,right);
	
	max_left_border_sum = 0;
	left_border_sum = 0;
	for (i = center;i >= left;i --){
		left_border_sum += sequence[i];
		if (left_border_sum > max_left_border_sum){
			max_left_border_sum = left_border_sum;
		}
	}
	
	max_right_border_sum = 0;
	right_border_sum = 0;
	for (i = center + 1;i <= right;i ++){
		right_border_sum += sequence[i];
		if (right_border_sum > max_right_border_sum){
			max_right_border_sum = right_border_sum;
		}
	}
	return Max3(max_left_sum,max_right_sum,max_left_border_sum + max_right_border_sum);
}
