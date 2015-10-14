#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_number 200000
#ifndef _HashQuad_H

typedef unsigned int Index;
typedef Index Position;

struct HashTb1;
typedef struct HashTb1 *HashTable;
typedef int ElementType;                    //默认类型为int

HashTable InitializeTable(int TableSize);
Position Find(char *Key, HashTable H);
void Insert(char *Key,ElementType Element,HashTable H);
ElementType Retrieve(Position P , HashTable H);
HashTable Rehash(HashTable H);
Position Hash(const char *Key,int TableSize);
/*Routines such as Delete and MakeEmpty are omitted */

#endif /* _HashQuad_H */

enum KindOfEntry{Legitimate,Empty,Deleted};                       //For more about enum .see C bible page 215

struct HashEntry
{
	char *Name;
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTb1 
{
	int TableSize;
	Cell *TheCells;
};
#define MinTableSize 1
#define MaxNameLength 100

char* number2string(int n){
	char * str = malloc(sizeof(char) * MaxNameLength);
	int i=0;
	while(n != 0){
		str[i++] = n%10;
		n /= 10;
	}
	str[i]='\0';
	return str;
}
HashTable htable;
int *compact;
int M=0;
int compar(const void *a , const void *b)
{
	return (*(int*)a)-(*(int *)b);
}
int rank(int n);
int main()
{
	int N=0;
	int a;
	char c;
	int origin[Max_number];
	do{
		scanf("%d%c",&a,&c);
		origin[N++]=a;
	}
	while(c != '\n');
	//free(origin+N);
	int i;
	int sort[N];
	for(i = 0 ; i < N ; i++)
		sort[i] = origin[i];
	qsort(sort,N,sizeof(int),compar);
	compact = malloc(sizeof(int) * (N+1));
	for(i = 0 ; i < N ;i++){
		int b=sort[i];
		compact[++M]=b;
		while(i+1 < N && sort[i+1] == b)
			i++;
	}
	//free(compact+M+1);
	htable = InitializeTable(M);
	for(i = 0; i <= M ; i++)
		Insert(number2string(compact[i]),i,htable);
	for(i = 0; i < N-1; i++)
		printf("%d ",rank(origin[i]));
	printf("%d\n",rank(origin[i]));
	return 0;
}
int rank(int n)
{
	return Retrieve(Find(number2string(n),htable),htable);
}
Index
Hash(const char *Key,int Tablesize)
{
	unsigned int HashVal=0;

	while(*Key!='\0')
		HashVal = (HashVal << 5)+ *Key++;

	return HashVal % Tablesize;
}
ElementType Retrieve(Position P, HashTable H)
{
	return H->TheCells[P].Element;
}
int NextPrime(int TableSize);
HashTable 
InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if(TableSize<MinTableSize)
	{
		printf("Table size too small!!!");
		return NULL;
	}

	H=malloc(sizeof(struct HashTb1));
	if(H==NULL)
	{
		printf("Out Of Space!!!");
		return NULL;
	}

	H->TableSize=NextPrime(TableSize);
	
	H->TheCells=malloc(sizeof(Cell)*(H->TableSize));
	if(H->TheCells==NULL)
		printf("Out Of Space!!!");
	for(i=0;i<H->TableSize;i++)
		H->TheCells[i].Info=Empty;
	return H;
}
int static TestPrime(int X)
{
	int i=2;
	for(i=2;i*i<=X;i++)
	{
		if(X%i==0)
			return 0;	
	}
	return 1;
}
int NextPrime(int X)
{
	int i;
	for(i=2*(X/2)+1;;i+=2)
		if(TestPrime(i)==1)
			return i;
}
void Insert(char *Key,ElementType Element,HashTable H)
{
	Position Pos;
	Pos=Find(Key,H);
	if(H->TheCells[Pos].Info!=Legitimate)
	{
		H->TheCells[Pos].Name=malloc(sizeof(char)*MaxNameLength);
		H->TheCells[Pos].Name=strcpy(H->TheCells[Pos].Name,Key);
		H->TheCells[Pos].Info=Legitimate;       //Probably need strcpy
		H->TheCells[Pos].Element=Element;
	}

}
Position Find(char *Key, HashTable H)
{
	Position CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos=Hash(Key,H->TableSize);           //Name that are marked deleted count as in this table 
	while(H->TheCells[CurrentPos].Info!=Empty&&(strcmp(H->TheCells[CurrentPos].Name,Key)!=0))           //Probably need strcmp!!!
	{
		CurrentPos +=2 * ++CollisionNum-1;
		if(CurrentPos>=H->TableSize)
			CurrentPos-=H->TableSize;
	}
	return CurrentPos;
}
