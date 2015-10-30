#include <stdio.h>
/* For any given antiprime(highly composite number),the k distinct prime must be precisely the first k prime numbers.

   Hence for input less than 2,000,000,000, the biggest prime could ever be involved is 29 (2*3*5*7*11*13*17*19*23*29 = 6469693230)*/
int prime[] = {2,3,5,7,11,13,17,19,23,29};
int NN;
int M = 1;
int max_product(int N,int position,int most,int pre_product)
{
	int product = prime[position];
	int i;
	int max_m = 1;
	int max_p = 1;
		for(i = 1; i <= most && product <= N; i++){
			int x = product*max_product(NN/(product*pre_product),position+1,i,product*pre_product);
			if( M*(i+1) > max_m || (M*(i+1) == max_m && max_p > x) ){
				max_m = M*(i+1);
				max_p = x;
			}
			product *= prime[position];
		}
		M = max_m;
		return max_p;
}
int main()
{
	FILE *in = fopen("antiprime.in","r"), *out = fopen("antiprime.out","w");
	fscanf(in,"%d",&NN);
	fprintf(out,"%d",max_product(NN,0,16,1));
	printf("%d\n",max_product(NN,0,16,1));
	return 0;
}
