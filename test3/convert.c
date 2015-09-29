#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numberOfOperator 15
#define token_lenth 1000
#define EmptyTOS (-1)
#define notOp(x) ( x != '+' && x != '-'&& x != '*'&& x != '/')
typedef struct token{
	int Type;
	char *str;
}* Token;
typedef Token ElementType;
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
ElementType TopAndPop(Stack S);

typedef char Operator;
enum{
	Term = 0,Expression = 1
};
Token concatenate(Token token1,Token token2,Operator Op);
int main()
{
	Stack S = CreateStack(2*numberOfOperator);
	char string[1000];
	fgets(string,1000,stdin);
	char* str =NULL;
	str = strtok(string, " \n"); 
	while(str != NULL){
		if(notOp(str[0]))
		{
			Token t= malloc(sizeof(struct token));
			t->str=str;
			t->Type = Term;
			Push(t,S);
		}
		else{
			Operator Op = str[0];
			Token token2 = TopAndPop(S);
			Token token1 = TopAndPop(S);
			Token token3 = concatenate(token1,token2,Op);
			Push(token3,S);
		}
		str = strtok(NULL, " \n"); 
	}
	printf("%s\n",TopAndPop(S)->str);
	return 0;
}
void addParenthsis(char *str1 , char *str2 , int l2)
{
	str1[0] = '(';
	strcpy(str1+1,str2);
	str1[l2+1] = ')';
	str1[l2+2] = '\0';
}

Token concatenate(Token token1,Token token2,Operator Op)
{
	int l1 = strlen(token1->str);
	int l2 = strlen(token2->str);
	Token t = malloc(sizeof(struct token));	
	t->str= malloc(sizeof(char) * (l1 + l2 +6));
	if(Op == '+' || Op == '-'){
		strcpy(t->str,token1->str);
		t->str[l1] = Op;
		strcpy(t->str + l1 + 1,token2->str);
		t->Type = Expression;
	}
	else if(Op == '*' || Op == '/'){
		if(token1->Type == Expression){
			addParenthsis(t->str,token1->str,l1);
			t->str[l1+2] = Op;
			if(token2->Type == Expression)
				addParenthsis(t->str+l1+3,token2->str,l2);
			else
				strcpy(t->str+l1+3,token2->str);
		}
		else{
			strcpy(t->str,token1->str);
			t->str[l1] = Op;
			if(token2->Type == Expression)
				addParenthsis(t->str+l1+1,token2->str,l2);
			else
				strcpy(t->str+l1+1,token2->str);
		}
		t->Type = Term;
	}
	return t;
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
ElementType
TopAndPop(Stack S)
{
	if(!IsEmpty(S))
	{
		ElementType Tmp;
		Tmp=Top(S);
		Pop(S);
		return Tmp;
	}
	printf("Empty Stack");
	return 0;
}
