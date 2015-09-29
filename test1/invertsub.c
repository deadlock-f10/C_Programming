#include <stdio.h>
#include <string.h>
#define max_length (100)
int next[max_length];
char pattern[max_length];
char text[max_length];
int m , n ;
void compute_next();
void KMP();
int main()
{

	FILE *in , *out;
	in = fopen("invertsub.in","r");
	out = fopen("invertsub.out","w");
	fgets(text+1,max_length,in);
	fgets(pattern+1,max_length,in);
	n = strlen(text+1);
	m = strlen(pattern+1);
	pattern[m--] = '\0';
	text[n--] = '\0';
	compute_next();
	int i=1,j=1;
	while(i <= n && j <= m){
		while( j > 0 && pattern[j] != text[i])
			j = next[j];
		i++,j++;
	}
	if(i > n && j <= m)
	{
		fprintf(out,"searching failed");
		return -1;
	}
	int k;
	for(k = 0; k < m ; k++){
		text[i-m+k] = pattern[m-k];
	}
	fprintf(out,"%s\n",text+1);

	return 0;
}
void compute_next()
{
	int j = 2;
	next[1] = 0;
	int t = 0;          // t = f[j-1]
	for (j = 2 ;j <= m ; j++){
		while( t > 0 && (pattern[j-1] != pattern[t]))
			t = next[t];
		t += 1;
		if( pattern[j] != pattern[t])
			next[j] = t;	
		else
			next[j] = next[t];
	}
}
