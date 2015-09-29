#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
// leveraging the fact that the number of primes not exceeding x is Pi(x) approximatly x/ln(x) ,we find a 5*E5 with suffice
#define Max_Primes 500000
uint32_t Array1[Max_Primes];
uint32_t Array2[Max_Primes];
bool test_prime(int p)
{
	int m;
	for(m = 2 ; m*m <= p ; m++)
		if((p % m) == 0)
			return false;
	return true;
}
int nprime(int N);
int main()
{
	int N;
	scanf("%d",&N);
	int total = nprime(N);
	int i;
	if( N % 2 == 0)
		for(i = 0 ; i < total ; i++)
			printf("%d\n",Array2[i]);
	else
		for(i = 0 ; i < total ; i++)
			printf("%d\n",Array1[i]);
	return 0;
}
int nprime(int N)
{
	if( N == 1)
	{
		Array1[0] = 2;
		Array1[1] = 3;
		Array1[2] = 5;
		Array1[3] = 7;
		return 4;
	}
	int num = nprime(N - 1);
	int total=0;
	int i = 0;
	if(N % 2 == 0){
		for(; i < num ; i++){
			if(test_prime(Array1[i] * 10 + 1))
				Array2[total++] =Array1[i] * 10 + 1;
			if(test_prime(Array1[i] * 10 + 3))
				Array2[total++] =Array1[i] * 10 + 3;
			if(test_prime(Array1[i] * 10 + 7))
				Array2[total++] =Array1[i] * 10 + 7;
			if(test_prime(Array1[i] * 10 + 9))
				Array2[total++] =Array1[i] * 10 + 9;
		}
	}
	else{
		for(; i < num ; i++){
			if(test_prime(Array2[i] * 10 + 1))
				Array1[total++] =Array2[i] * 10 + 1;
			if(test_prime(Array2[i] * 10 + 3))
				Array1[total++] =Array2[i] * 10 + 3;
			if(test_prime(Array2[i] * 10 + 7))
				Array1[total++] =Array2[i] * 10 + 7;
			if(test_prime(Array2[i] * 10 + 9))
				Array1[total++] =Array2[i] * 10 + 9;
		}
	}
	return total;
}


