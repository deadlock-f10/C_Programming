#include <stdio.h>
#include <stdlib.h>
#define alphabeta (26)
//#define index(alpha) (()((alpha) - 'a') % 26)
int Index(char c)
{
	if( c >= 'a' && c <= 'z')
		return c-'a';
	else if(c >= 'A' && c <= 'Z')
		return c-'A';
	else
		return -1;
}
struct Freq{
	char alpha;
	int freq;
};
typedef struct Freq *frequency;
int compare(const void *a,const void *b)
{
	if((*(frequency *)a)->freq > (*(frequency *)b)->freq)
		return -1;
	else if((*(frequency *)a)->freq == (*(frequency *)b)->freq)
		return 0;
	else
		return 1;
}
int main()
{
	FILE *in,*out;
	in = fopen("freq.in","r");
	out = fopen("freq.out","w");
	int total=0;
	//int freq[alphabeta];
	frequency *freq = calloc(alphabeta,sizeof(frequency));
	int i=0;
	for(i=0; i < alphabeta ; i++){
		freq[i] = calloc(1,sizeof(struct Freq));
		freq[i]->alpha = 'a'+i;
	}
	char c;
	while((c = fgetc(in)) != EOF){
		int INdex = Index(c);
		if(INdex == -1)
			continue;
		freq[INdex]->freq++;
		total++;
	}
/*	int i = 0;
	int max = 0;
	for(i = 0; i < 10 ; i++){
		int max_index = 0;
		int j = 0;
		for(; j < alphabeta ; j++)
			if(freq[j] > freq[max_index])
				max_index = j;
		fprintf(out,"%c%d ",'a'+max_index,freq[max_index]);
		max = freq[max_index];
		freq[max_index] = 0;
	}
	do{
		int max_index = 0;
		int j = 0;
		for(; j < alphabeta ; j++)
			if(freq[j] > freq[max_index])
				max_index = j;
		if(max > freq[max_index])
			break;
		fprintf(out,"%c%d ",'a'+max_index,freq[max_index]);
		freq[max_index] = 0;
	}while(1);*/
	qsort(freq,alphabeta,sizeof(frequency),compare);
	int j = 0;
	for(; j < 10 ; j++)
		fprintf(out,"%c%d ",freq[j]->alpha,freq[j]->freq);
	while(j < 26 && freq[j]->freq == freq[9]->freq){
		fprintf(out,"%c%d ",freq[j]->alpha,freq[j]->freq);
		j++;
	}
	fprintf(out,"\n%d\n",total);
	return 0;

}
