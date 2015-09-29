#include <stdio.h>
#include <stdlib.h>
#define right_cross(x)  ((x) >= p  ? (x)-p : (x))
#define left_cross(x)  ((x) < 0 ? (x)+p : (x))
int main(){
	int m,n,p,k,i;
	scanf("%d %d %d %d",&m,&n,&p,&k);
	int *Age = calloc(p,sizeof(int));
	Age[0] = 1;
	int Head = 0;
	for(i = 1 ; i <= k ; i++){
		int j = 0; 
		int birth = 0;
		for(;j <= n - m ; j++ ) 
			birth += Age[right_cross(Head + m -1 + j)];
		Head = left_cross(Head-1);		
		Age[Head] = birth; 
	}
	int total = 0;
	for(i = 0 ; i < p ; i++)
		total += Age[i];
	printf("%d\n",total);
	return 0;
}
