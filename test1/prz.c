#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define Max_Intval 50000
typedef uint32_t Int;
struct interval{
	Int begin;
	Int end;
};
struct Cluster{
	Int Cluster_begin;
	Int Cluster_end;
//	Priority_Queue PQ;             // Key = Int.end , big top 
}; 
typedef struct interval* Interval;
void SORT(Interval *A, int total_Intval);
Interval Array[Max_Intval];
int main()
{
	FILE *in , *out;
	in = fopen("prz.in","r");
	out = fopen("prz.out","w");
	Int int_begin,int_end;

	int i = 0;
	while(fscanf(in , "%d%d",&int_begin,&int_end) != EOF){
		Array[i] = malloc(sizeof(struct interval));						
		Array[i]->begin = int_begin;
		Array[i]->end = int_end;
		i++;
	}
	fclose(in);
	int total_Intval = i;
	SORT(Array,total_Intval);
	i = 0;
	while( i < total_Intval){
		// invarint :  Every time we reach this line, variable i indicates the position of Interval from which  next cluster begin .
		struct Cluster cluster;
		cluster.Cluster_begin = Array[i]->begin;
		cluster.Cluster_end = Array[i]->end;
		i++;
		//Interval * max_end = Array[i];
//		do{
	//		for( ; (Array[i]->begin <= cluster.end) && (i < total_Intval); i++)
	//			push(PQ , Array[i]);
	//		max_end = pop(PQ);
//		}while(max_end->int_end > cluster.end);
		while((i < total_Intval)  &&(Array[i]->begin <= cluster.Cluster_end) ){
			cluster.Cluster_end = Array[i]->end > cluster.Cluster_end  ? Array[i]->end : cluster.Cluster_end;
			i++;
		}
		fprintf(out,"%d %d\n",cluster.Cluster_begin , cluster.Cluster_end);
	}
	fclose(out);
}
int compar(const void* a , const void* b)
{
	if((*(Interval *)a)->begin < (*(Interval *)b)->begin) 
		return -1;
	else if((*(Interval *)a)->begin > (*(Interval *)b)->begin) 
		return 1;
	else{
		if((*(Interval *)a)->end < (*(Interval *)b)->end) 
			return -1;
		if((*(Interval *)a)->end > (*(Interval *)b)->end) 
			return 1;
		else 
			return 0;
	}
}
void SORT(Interval *A, int total_Intval)
{
	qsort(A,total_Intval,sizeof(Interval),compar);
}

