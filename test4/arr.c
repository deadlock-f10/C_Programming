#include <stdio.h>
#include <stdlib.h>
#define max 200
#define true 1
int k=0;
int m = 1;
int n=0;
int multiply(int a[],int b[])
{
	int i = 1;
	int result = 0;
	while(i <= k){
		result += a[i]*b[i];
		i++;
	}
	return result;
}
int main()
{
	FILE *in,*out;
	in = fopen("arr.in","r");
	//out = fopen("arr.out","w");
	int A[max+1][max+1],B[max+1][max+1];
	char c;
	int i;
	do{
		fscanf(in,"%d",&A[1][++k]);
		while((c = fgetc(in)) == ' ')
			;
		if(c == '\n')
			break;
		ungetc(c,in);
	}while(1);
	do{
		c = fgetc(in);
		if(c == '\n')
			break;
		ungetc(c,in);
		m++;
		i=0;
		do{
			fscanf(in,"%d%c",&A[m][++i],&c);
		}while(i < k);
	}while(true);
	do{
		fscanf(in,"%d",&B[++n][1]);
		while((c = fgetc(in)) == ' ')
			;
		if(c == '\n')
			break;
		ungetc(c,in);
	}while(1);
	int j=1;
	while(j < k){
		j++;
		i=0;
		do{
			fscanf(in,"%d",&B[++i][j]);
		}while(i < n);
	}
	for(i=1; i <= m ; i++){
		for(j=1 ; j <= n ; j++)
			fprintf(stdout,"%12d",multiply(A[i],B[j]));
		fprintf(stdout,"\n");
	}
	return 0;
}
