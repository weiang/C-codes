/*************************************************************************
	> File Name: 1_1.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Sun 14 Oct 2012 08:48:37 PM CST
	> Described: “连通问题的快速查找算法 (Quick-find algorithm)”
 ************************************************************************/

#include <stdio.h>

#define N	10

int main()
{
	int	i, p, q, t, id[N];

	for (i = 0; i < N; i ++)
		id[i] = i;
	while (scanf("%d%d", &p, &q) == 2) {
		if (id[p] == id[q]){
			continue;
		}
		for (t = id[p], i = 0; i < N; i ++)
			if ( id[i] == t)
				id[i] = id[q];
		printf("%d -- %d\n", p, q);
		for (i = 0; i < N; i ++)
			printf("%d ", id[i]);
		printf("\n");
	}
}
			
