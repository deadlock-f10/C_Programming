#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MaxLength 2000
int i;
int N=0;
int M;
bool paintboard[MaxLength + 1][MaxLength + 1];
void paint(int k,int j);
int main(){
	FILE *in,*out;
	in = fopen("squares.in","r");
	out = fopen("squares.out","w");
	fscanf(in,"%d",&i);
	char line[MaxLength + 5];
	fscanf(in,"%s\n",line+1);
	M = strlen(line+1);	
	int j,k;
	do{
		N++;
		for(j = 1 ; j <= M ; j++)
			if(line[j] == '0')
				paint(N,j);
	}
	while(fgets(line+1,MaxLength,in) != NULL);
	int feasible=0;
	for(k = 1 ; k <= N-i+1 ; k++)
		for(j = 1 ; j <= M-i+1 ; j++)
			if(paintboard[k][j] == false)
				feasible++;
	fprintf(out,"%d\n",feasible);
	return 0;
}
void paint(int k,int j){
	int n=k;
	int m=j;
	int m_boundary = (j - i >= 0) ? (j - i + 1) : 1;
	int n_boundary = (k - i >= 0) ? (k - i + 1) : 1;
	for(; n >= n_boundary ; n--)
		for(m = j; m >= m_boundary ; m--)
			paintboard[n][m]=true;
}
