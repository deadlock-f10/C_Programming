#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _HashQuad_H

typedef unsigned int Index;
typedef Index Position;

struct HashTb1;
typedef struct HashTb1 *HashTable;
typedef int ElementType;                    //默认类型为int

HashTable InitializeTable(int TableSize);
//void DestroyTable(HashTable H);
Position Find(char *Key, HashTable H);
void Insert(char *Key,ElementType Element,HashTable H);
ElementType Retrieve(Position P , HashTable H);
HashTable Rehash(HashTable H);
Position Hash(const char *Key,int TableSize);
/*Routines such as Delete and MakeEmpty are omitted */

#endif /* _HashQuad_H */

#define Max_Str_Lenth (5)
#define Max_State (4096)
#define Max_INdex (4096)

typedef int INdex;
typedef int State;
struct Action{
	char Transition[3 * Max_Str_Lenth];			
	char Literal[Max_Str_Lenth + 1];
	State TState;
};
HashTable INdexTable,StateTable;
void InsertINdex(char *str,int INdex)
{
	Insert(str,INdex,INdexTable);
}
void InsertState(char *str,int State)
{
	Insert(str,State,StateTable);
}
INdex getINdex(char *str)
{
	return Retrieve(Find(str,INdexTable),INdexTable);
}
State getState(char *str)
{
	return Retrieve(Find(str,StateTable),StateTable);
}
FILE *in;
int probe_newline(){
	char c;
	while((c =fgetc(in)) == ' ')
		;
	if(c == '\n')
		return 1;
	ungetc(c,in);
	return 0;
}
int main()
{
	INdexTable = InitializeTable(Max_INdex);
	StateTable = InitializeTable(Max_State);
	in= fopen("dfa.in","r");
	fscanf(in,"Q\\\\X ");
	int M=0;
	//char c;
	char str[Max_Str_Lenth + 1];
	do{
		fscanf(in,"%s",str);
		InsertINdex(str,++M);
	}
	while(!probe_newline());
	int N=0;
	struct Action **ActTable = malloc(sizeof(struct Action *) * (Max_State + 1));
	//char string[Max_State + 1];
	//char str[Max_Str_Lenth + 1];
	while(1){
		//fgets(string,Max_State,in);
		/*sscanf(string,"%s%c",str,&c);
		if(c == '\n')
			break;*/
		fscanf(in,"%s",str);
		if(probe_newline())
			break;
		InsertState(str,++N);
		ActTable[N] = malloc(sizeof(struct Action) * (M + 1));
		int i = 1;
		char s[3*Max_Str_Lenth];
		while(i <= M){
			fscanf(in,"%s",s);
			int j = 0;
			while((ActTable[N][i].Transition[j] = s[j]) != ',')
				j++;
			ActTable[N][i].Transition[j++] = '\0';
			int k=0;
			while((ActTable[N][i].Literal[k] = s[j]) != '\0')
				k++,j++;
			i++;
		}
	}
	State cur_state = getState(str);
	int i,j;
	for(i = 1; i <= N ; i++)
		for(j = 1; j <= M ; j++)
			ActTable[i][j].TState = getState(ActTable[i][j].Transition); 
	/****************Excution*****************/
	struct Action *action;
	char ** string = malloc(sizeof(char *) * (Max_State));
	i=0;
	do{
		fscanf(in,"%s",str);
		action = &ActTable[cur_state][getINdex(str)];
		cur_state = action -> TState;
		//printf("%s ",action->Literal);
		string[i++] = action->Literal;
	}while(!probe_newline());
	printf("%s\n",action->Transition);
	int x = 0;
	for(; x < i ; x++)
		printf("%s ",string[x]);
	return 0;
}





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
Index
Hash(const char *Key,int Tablesize)
{
	unsigned int HashVal=0;

	while(*Key!='\0')
		HashVal = (HashVal << 5)+ *Key++;

	return HashVal % Tablesize;
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
HashTable
Rehash(HashTable H)
{
	int i,OldSize;
	Cell *OldCells;

	OldCells = H->TheCells;
	OldSize=H->TableSize;

	H=InitializeTable(2*OldSize);
	for(i=0;i<OldSize;i++)
		if(OldCells[i].Info==Legitimate)
			Insert(OldCells[i].Name,OldCells[i].Element,H);
	free(OldCells);
	return H;
}
ElementType Retrieve(Position P, HashTable H)
{
	return H->TheCells[P].Element;
}
