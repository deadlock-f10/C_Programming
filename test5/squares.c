#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MaxLength 2000
/*int i;
int N=0;
int M;
bool board[MaxLength + 1][MaxLength + 1];
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
}*/
#define cpt_obstacle(x) (((x) == '0') ? 1 : 0)
char board[MaxLength + 1][MaxLength + 1];
int **obstacle;
int i;
int N=1;
int M;
void compute_obstacle(int i); //obstacle[*][0]  = 0
int main(){
	FILE *in,*out;
	in = fopen("squares.in","r");
	out = fopen("squares.out","w");
	fscanf(in,"%d",&i);
	char line[MaxLength + 1];
	fscanf(in,"%s\n",line+1);
	M = strlen(line+1);	
	int j,k;
	for(j = 1 ; j <= M ; j++)
			board[1][j] = line[j];
	for(j = 1 ; j <= M ; j++)
			board[0][j] = '1';
	while(fgets(line+1,MaxLength,in) != NULL){
		N++;
		for(j = 1 ; j <= M ; j++)
			board[N][j] = line[j];
	}
	obstacle = malloc(sizeof(int *) * (N-i + 2)); 
	compute_obstacle(i);
	/*for(j = 1; j <= N-i+1 ; j++){
		for(k = 1 ; k <= M ; k++)
			printf("%d ",obstacle[j][k]);
		printf("\n");
	}*/
	int feasible = 0;
	for(j = 1 ; j <= N - i + 1 ; j++){
		int total_obstacle = 0;
		for(k = 1 ; k < i ; k++)
			total_obstacle += obstacle[j][k];
		for(k = 1 ; k <= M - i + 1 ; k++){
			total_obstacle += (obstacle[j][i+k-1] - obstacle[j][k-1]);
			if(total_obstacle == 0)
				feasible++;
		}
	}
	fprintf(out,"%d\n",feasible);
	return 0;
}
void compute_obstacle(int i)
{
	int j=0,k;
	for(;j <= N-i+1 ; j++)		
		obstacle[j] = calloc(M + 1 , sizeof(int));
	for(j=1 ; j <= M ; j++){
		int total_obstacle = 0;
		for(k = 1 ; k < i ; k++)
			total_obstacle += cpt_obstacle(board[k][j]);
		for(k = 1 ; k <= N-i+1 ; k++){
			total_obstacle += (cpt_obstacle(board[k+i-1][j]) - cpt_obstacle(board[k-1][j]));
			//printf("board[%d][%d]=%d,board[%d][%d]=%d\n",k+i-1,j,cpt_obstacle(board[k+i-1][j] ,k-1,j,cpt_obstacle(board[k-1][j]);
			obstacle[k][j] = total_obstacle;
		}//obstacle[0][*] = 0
	}
}
