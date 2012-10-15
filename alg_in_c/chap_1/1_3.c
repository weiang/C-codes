/*************************************************************************
	> File Name: 1_3.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Sun 14 Oct 2012 09:29:05 PM CST
	> Describition: “ 加权快速合并算法”
 ************************************************************************/

#include <stdio.h>

#define N	10

int main(void)
{
	int i, j, id[N], sz[N], p, q;

	for (i = 0; i < N; i ++) {
		id[i] = i;
		sz[i] = 1;
	}

	while (scanf("%d%d", &p, &q) == 2) {
		for (i = p; i != id[i]; i = id[i])
			;
		for (j = q; j != id[j]; j = id[j])
			;
		if (i == j) {
			printf("%d -- %d\t", p, q);
			for (i = 0; i < N; i ++)
				printf("%d ", id[i]);
			printf("\n");
			continue;
		}

		if (sz[i] < sz[j]) {
			id[i] = j;
			sz[j] += sz[i];
		}
		else {
			id[j] = i;
			sz[i] += sz[j];
		}
		printf("%d -- %d\t", p, q);
		for (i = 0; i < N; i ++)
			printf("%d ", id[i]);
		printf("\n");
		}
	return 0;
}
