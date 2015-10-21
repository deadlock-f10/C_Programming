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
	FILE *in;
	in = fopen("arr.in","r");
	char line[4096];
	int total_lines = 0;
	while(fgets(line,4096,in) != NULL)
		total_lines++;
		/*if(feof(in))
			break;*/
	//printf("total_lines =%d",total_lines);
	//fflush(stdout);
	rewind(in);
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
	m = total_lines  - k;
	int j=1;
	/*printf("k=%d,m=%d,n=%d\n",k,m,n);
	fflush(stdout);*/
	while(j < m){
		j++;
		i=0;
		do{
			fscanf(in,"%d",&A[j][++i]);
		}while(i < k);
	}
	/*printf("k=%d,m=%d,n=%d\n",k,m,n);
	fflush(stdout);*/
	do{
		fscanf(in,"%d",&B[++n][1]);
		while((c = fgetc(in)) == ' ')
			;
		if(c == '\n')
			break;
		ungetc(c,in);
	}while(1);
	/*printf("k=%d,m=%d,n=%d\n",k,m,n);
	fflush(stdout);*/
	j=1;
	while(j < k){
		j++;
		i=0;
		do{
			fscanf(in,"%d",&B[++i][j]);
		}while(i < n);
	}
	for(i=1; i <= m ; i++){
		for(j=1 ; j <= n ; j++)
			fprintf(stdout,"%10d",multiply(A[i],B[j]));
		fprintf(stdout,"\n");
	}
	return 0;
}
