#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <assert.h>
#define index(x) (x - 'a')
#define MaxLength (1024)
//int alphabeta[26] = {0};
int main(){
	char line[MaxLength];
	int *alphabeta = calloc(26,sizeof(int));
	while(fgets(line,MaxLength,stdin) != NULL){
		int tail = strlen(line) - 2 ;
		//assert(line[tail+1] == '\n');
		alphabeta[index(line[0])]++;		
		alphabeta[index(line[tail])]--;
	}
	int in = -1,out = -1;
	int i = 0;
	int zero_count = 0;
	while(i < 26){
		if(alphabeta[i] == 1){
			if(in == -1)
				in = i;
		}
		else if(alphabeta[i] == -1){
			if(out == -1)
				out = i;
		}
		else if(alphabeta[i] == 0)
			zero_count++;
		i++;
	}
	if(in >= 0 && out >= 0 && zero_count == 24)  
		printf("yes\n");
	else if(zero_count == 26)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}
