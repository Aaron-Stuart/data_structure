#include <stdio.h>
#include <stdlib.h>

typedef struct stacknode{
	int data;
	struct stacknode *next;
}StackNode;

typedef struct{
	StackNode *top;	//栈顶指针
}LinkStack;

//初始化置栈空
void init(LinkStack *S)
{
	S->top = NULL;
}

//判栈空
int empty(LinkStack *S)
{
	return S->top == NULL;
}

//进栈
void push(LinkStack *S, int elem)
{
	StackNode *p = (StackNode *)malloc(sizeof(StackNode));
	
	p->data = elem;
	p->next = S->top;
	S->top = p;
}

//出栈
void pop(LinkStack *S)
{
	if(empty(S))
	{
		printf("stack underflow\n");
		exit(-1);
	}
	StackNode *temp = S->top;
	
	S->top = temp->next;
	free(temp);
}

//取栈顶元素
int getTop(LinkStack *S)
{
	if(empty(S))
	{
		printf("Stack empty\n");
		exit(-1);
	}
	return S->top->data;
}

int main()
{
	LinkStack S;
	init(&S);
	
	for(int i = 0; i < 20; i++)
	{
		push(&S, i);
	}
	printf("top : %d\n",getTop(&S));
	pop(&S);
	push(&S,100);
	printf("top : %d\n",getTop(&S));
	return 0;
	return 0;
}
