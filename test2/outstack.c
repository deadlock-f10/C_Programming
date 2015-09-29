#include <stdio.h>
#include <stdlib.h>
#define EmptyTOS (-1)
typedef int ElementType;
struct StackRecond{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};
typedef struct StackRecond *Stack;
Stack CreateStack(int MaxElements);
int IsEmpty(Stack S);
int IsFull(Stack S);
void Push(ElementType X, Stack S);
void Pop(Stack S);
ElementType Top(Stack S);
int main()
{
	int N;
	scanf("%d\n",&N);
	Stack stack = CreateStack(N);
	int i;
	int max=0;
	int e;
	for(i = 0 ; i < N ; i++){
		scanf("%d",&e);
		while(max < e)
			Push(++max , stack);
		if(Top(stack) != e)
			goto No;
		Pop(stack);
	}
	printf("YES\n");
	return 0;
No: printf("NO\n");
	return -1;
}

ElementType 
Top(Stack S)
{
	if(!IsEmpty(S))
	return S->Array[S->TopOfStack];
	return 0;
}
void Pop(Stack S)
{
	if(IsEmpty(S))
		return ;
	else
	S->TopOfStack--;
}
void
Push(ElementType X, Stack S)
{
	if(IsFull(S))
		;
	else
		S->Array[++S->TopOfStack]=X;
}
Stack
CreateStack(int MaxElements)
{
	Stack S;
	S=malloc(sizeof(struct StackRecond));
	if(S==NULL)
		;
	S->Capacity=MaxElements;
	S->TopOfStack = EmptyTOS;
	S->Array=malloc(sizeof(int)*MaxElements);
	if(S->Array==NULL)
		;
	return S;
}
int IsEmpty(Stack S)
{
	return S->TopOfStack==EmptyTOS; 
}
int IsFull(Stack S)
{
	return S->TopOfStack==S->Capacity-1;
}
