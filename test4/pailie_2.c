#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int m;
int * permutation;
void print();
void recurrence(char str[],int i);
int compar(const void *a,const void *b)
{
	if( *(char *)a < *(char *)b ) 
		return -1;
	else if( *(char *)a > *(char *)b ) 
		return 1;
	else 
		return 0;
}
int main()
{
	char str[100];
	scanf("%s",str+1);
	m = strlen(str+1);
	qsort(str+1,m,sizeof(char),compar);
	permutation = malloc(sizeof(int) * (m+1));
	//printf("m=%d",m);
	recurrence(str,m);
	return 0;
}
char * exclude(char str[],int i,int n)
{
	char *s = malloc(sizeof(char) * n);
	s[0] = '\n';
	int j = 1;
	for(; j < i ; j++)
		s[j]=str[j];
	for(; j < n ; j++)
		s[j]=str[j+1];
	return s;
}
void recurrence(char str[],int i)
{
	int index = m-i+1;
	int j=1;
	if(i == 1)
	{
		permutation[index] = str[1];
		print();
	}
	else{
		do{
			while(str[j] == str[j-1]){
				j++;
				if( j == i+1)
					goto die;
			}
			permutation[index] = str[j];
			recurrence(exclude(str,j,i),i-1);
			j++;
		}
		while(j <= i);
die:    ;
	}
}
void print(){
	int i=1;
	for(; i <= m ; i++)
		printf("%c",permutation[i]);
	printf("\n");
}
