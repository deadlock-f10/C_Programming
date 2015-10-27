#include <stdlib.h>
#include <stdio.h>
//#define MAX_LEN (20)
int *limit;
void print(int A[] , int N)
{
	int i=1;
	for(i = 1; i <= N ; i++)
		printf("%d ",A[i]);
	printf("\n");
}
int find_unviolated(int A[], int N)        // if all position reaches it's limit , return 0;
{
	int i=N;
	while(A[i] == limit[i])                // set A[0] and limit[0] as sentinel ,which means A[0] and limit[0] must be distinct number.
		i--;
	return i;
}
int main()
{
	int m,n;
	scanf("%d%d",&n,&m);
	limit = malloc(sizeof(int) * (m + 1));
	int *sequence = malloc(sizeof(int) * (m + 1));
	limit[0] = -1;
	sequence[0] = -2;
	int i=0;
	for(i = 1 ; i <= m ; i++)
		limit[i] = n+i-m;
	for(i = 1 ; i <= m ; i++)
		sequence[i] = i;
	int p = 0;
	print(sequence , m);
	while((p = find_unviolated(sequence,m)) != 0){
		int j;
		sequence[p] += 1;
		for(j = p+1; j <= m ; j++)
			sequence[j] = sequence[j-1] + 1;
		print(sequence , m);
	}
	return 0;
}
