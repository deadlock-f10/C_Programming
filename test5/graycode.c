#include <stdio.h>
#include <stdlib.h>
#define MaxLenth 50
#define ctoi(x) ((x) - '0')
#define itoc(x) ((x) + '0')
int main()
{
	char *str = malloc(sizeof(char) * MaxLenth);
	while(fgets(str,MaxLenth,stdin) != NULL){
		char *result = malloc(sizeof(char) * MaxLenth);
		if(str[1] == 'g'){
			str += 2;			
			result[0] = str[0];
			int i = 1;
			while(str[i] != '\n'){
				result[i] = itoc(ctoi(str[i]) ^ ctoi(str[i-1])); 
				i++;
			}
			result[i] = '\0';
		}
		else{
			if(str[0] == '-')
				str += 2;
			result[0] = str[0];
			int i = 1;
			while(str[i] != '\n'){
				result[i] = itoc(ctoi(str[i]) ^ ctoi(result[i-1])); 
				i++;
			}
			result[i] = '\0';
		}
		while(*result != '\0')
			printf("%c",*(result++));
		printf("\n");
	}
	return 0;
}

