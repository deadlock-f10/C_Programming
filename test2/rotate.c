#include <stdio.h>
int f(int N, int i, int j){
	if(i == 1 && j < N)
		return j;
	else if(j == N)
		return i+j-1;
	else
		return (f(N-1,N+1-i,N-j) + 2*N - 1) ;
}
int main(){
	int i,j,N;
	scanf("%d",&N);
	for(i=1 ; i <= N ; i++){
		for(j=1; j <= N ; j++)
			printf("%5d",f(N,i,j));
		printf("\n");
	}
}
