#include <stdio.h>
int next_prime(int n)             //this n should be larger than 2 
{
	int p; 
	int m;
	for(p = n + 1; ; p++){
		for(m = 2 ; m*m <= p ; m++)
			if((p % m) == 0)
				goto rerun;
		return p;
rerun : ;
	}
}
int count_prime(int p , int N)
{
	int count = 0;
	int prime = p;
	while(prime <= N){
		count += (N / prime);
		prime *= p;
	}
	return count;
}
int main()
{
	int N;
	scanf("%d",&N);
	int prime = 2;
	int count;
	do{
		count = count_prime(prime , N);	
		if(count == 0)
			break;
		if(prime > 2)
			printf("*");
		if(count > 1)
			printf("%d^%d",prime,count);
		else
			printf("%d",prime);
		prime = next_prime(prime);
	}while(1);
	printf("\n");
	return 0;
}
