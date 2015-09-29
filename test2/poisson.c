#include <stdio.h>
#include <math.h>
int factorial(int k)
{
	int i;
	int factorial = 1;
	for(i = 2 ; i <= k ; i++) 
		factorial *=i;
	return factorial;
}
double approximate_e_m(int m){
	int i = m;
	double ret = 1;
	for(; i >= 1 ; i--){
		ret /= 2;
	}
	return pow(ret , (double)(1 / log(2)));
}
int main(){
	FILE *in , *out;
	in = fopen("poisson.in","r");
	out = fopen("poisson.out","w");
	int m,k;
	fscanf(in,"%d%d",&m,&k);
	fprintf(out,"%6e",pow(m,k)*approximate_e_m(m) / factorial(k));
	/*
	double difference = 0.000001 / factor ;
	double e_m;
	double diff ;
	do{
		e_m
	}while(diff > difference);*/
}
