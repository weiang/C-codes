/*************************************************************************
	> File Name: 1_4.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Sun 14 Oct 2012 09:37:10 PM CST
	> Describition: “等分路径压缩 (Path compression)”
 ************************************************************************/

#include <stdio.h>

#define N	10

int main(void)
{
	int	i, id[N], j, p, q;

	for (i = 0; i < N; i ++) {
			id[i] = i;
			printf("%d ", id[i]);
	}
	printf("\n");

	while (scanf("%d%d", &p, &q) == 2) {
		for (i = p; i != id[i]; i = id[i])
				id[i] = id[id[i]];
		for (j = q; j != id[j]; j = id[j])
			id[j] = id[id[j]];
		if (i == j) {
			printf("%d %d\t", p, q);
			for (i = 0; i < N; i ++)
				printf("%d ", id[i]);
			printf("\n");
			continue;
		}
		id[i] = j;
		printf("%d %d\t", p, q);
		for (i = 0; i < N; i ++)
			printf("%d ", id[i]);
		printf("\n");
	}
	return 0;
}
