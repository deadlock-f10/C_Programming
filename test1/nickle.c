#include <stdio.h>
#define n  (N * 10)
/* Using generating function , this problem can be solved within one line*/
/* result = 7 * (n choose 2) + 2 (n+1 choose 2) + (n+2 choose 2) */

int main(){
	int N;
	scanf("%d",&N);
	printf("%d\n",(n*(n-1)) + (7*(n+1)*n)/2+((n+2)*(n+1))/2);
	return 0;
}
