#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 20
typedef struct SeqStack{
	int data[STACK_SIZE];
	int top;	//栈顶元素的下标
}SeqStack;


//栈满返回1
int full(SeqStack *S)
{
	if(S->top == STACK_SIZE - 1)
		return 1;
	else
		return 0;
}
//栈空返回1
int empty(SeqStack *S)
{
	if(S->top == -1)
		return 1;
	else
		return 0;
}

//初始化
void init(SeqStack *S)
{
	S->top = -1;
}

//入栈，top+1
void push(SeqStack *S, int elem)
{
	if(full(S))
	{
		printf("stack overflow\n");
		exit(-1);
	}
	S->data[++S->top] = elem;
}

//出栈，top-1
void pop(SeqStack *S)
{
	if(empty(S))
	{
		printf("stack underflow\n");
		exit(-1);
	}
	S->top--;
}

//取栈顶元素
int getTop(SeqStack *S)
{
	if(empty(S))
	{
		printf("stack empty\n");
		exit(-1);
	}
	return S->data[S->top];
}

int main()
{
	SeqStack S;
	init(&S);
	
	for(int i = 0; i < 20; i++)
	{
		push(&S, i);
	}
	printf("top : %d\n",getTop(&S));
	pop(&S);
	push(&S,100);
	printf("top : %d\n",getTop(&S));
	printf("full : %d\n",full(&S));
	return 0;
}
