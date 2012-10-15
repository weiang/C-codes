/*************************************************************************
	> File Name: 1_2.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Sun 14 Oct 2012 09:08:28 PM CST
	> Describition: “连通问题的快速合并算法 ( Quick-union algorithm)”
 ************************************************************************/

#include <stdio.h>

#define N	6	

int main(void)
{
	int	i, id[N], j, p, q, cnt_i = 1, cnt_j = 1;

	for (i = 0; i < N; i ++) {
			id[i] = i;
			printf("%d ", id[i]);
	}
	printf("\n");

	while (scanf("%d%d", &p, &q) == 2) {
		for (i = p; i != id[i]; i = id[i])
				cnt_i ++;
		for (j = q; j != id[j]; j = id[j])
				cnt_j ++;
		if (i == j) {
			printf("%d %d (%d %d)\t", p, q, cnt_i, cnt_j);
			for (i = 0; i < N; i ++)
				printf("%d ", id[i]);
			printf("\n");
			continue;
		}
		id[i] = j;
		printf("%d %d (%d %d)\t", p, q, cnt_i, cnt_j);
		for (i = 0; i < N; i ++)
			printf("%d ", id[i]);
		printf("\n");
	}
	return 0;
}
