//队头在链头，队尾在链尾
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	int data;
	struct QueueNode *next;
}QueueNode;

typedef struct {
	QueueNode *front;
	QueueNode *rear;
}LinkQueue;

//初始化置队空
void init(LinkQueue *Q)
{
	Q->front = NULL;
	Q->rear = NULL;
}

//判队空
int empty(LinkQueue *Q)
{
	if(Q->front == NULL)
		return 1;
	else
		return 0;
}

//入队
void enqueue(LinkQueue *Q, int elem)
{
	QueueNode *p = (QueueNode *)malloc(sizeof(QueueNode));
	p->data = elem;
	p->next = NULL;
	
	if(empty(Q))
	{
		Q->front = p;
		Q->rear = p;
	}
	else
	{
		//在链表尾插入
		Q->rear->next = p;
		Q->rear = p;
	}
}

//出队
void dequeue(LinkQueue *Q)
{
	if(empty(Q))
	{
		printf("Queue underflow\n");
		exit(-1);
	}
	
	QueueNode *temp = Q->front;
	Q->front = temp->next;
	if(Q->rear == temp)	//如果出队前只有一个元素，不加此if，Q->rear会变成野指针
	{
		Q->rear = NULL;
	}
	free(temp);
}

//取队首元素
int getFront(LinkQueue *Q)
{
	if(empty(Q))
	{
		printf("Queue empty\n");
		exit(-1);
	}
	return Q->front->data;
}

int main()
{
	LinkQueue Q;
	init(&Q);
	
	for(int i = 0; i < 10; i++)
	{
		enqueue(&Q, i);
	}
	
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", getFront(&Q));
		dequeue(&Q);
	}
	printf("\n");
	return 0;
}
