#include <stdio.h>
#include <stdlib.h>
#define Max_number 200000
int *compact;
int M=0;
int compar(const void *a , const void *b)
{
	return (*(int*)a)-(*(int *)b);
}
int rank(int n);
int main()
{
	int N=0;
	int a;
	char c;
	int origin[Max_number];
	do{
		scanf("%d%c",&a,&c);
		origin[N++]=a;
	}
	while(c != '\n');
	//free(origin+N);
	int i;
	int sort[N];
	for(i = 0 ; i < N ; i++)
		sort[i] = origin[i];
	qsort(sort,N,sizeof(int),compar);
	compact = malloc(sizeof(int) * (N+1));
	for(i = 0 ; i < N ;i++){
		int b=sort[i];
		compact[++M]=b;
		while(i+1 < N && sort[i+1] == b)
			i++;
	}
	//free(compact+M+1);
	for(i = 0; i < N-1; i++)
		printf("%d ",rank(origin[i]));
	printf("%d\n",rank(origin[i]));
	return 0;
}
int rank(int n)
{
	int * ptr = (int *)bsearch(&n,compact+1,M,sizeof(int),compar);
	return (int) (ptr - compact);
}
