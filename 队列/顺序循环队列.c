//采用计数器来判断队满
#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 10

typedef struct{
	int data[QUEUE_SIZE];
	int count;	//计数器，用于判断队列满
	int front;	//头指针
	int rear;	//尾指针，最后一个的下个元素
}CircleQueue;

//初始化置队空
void init(CircleQueue *Q)
{
	Q->front = Q->rear = 0;		//front、rear都初始化为0
	Q->count = 0;
}

//判队空
int empty(CircleQueue *Q)
{
	return Q->count == 0;
}

//判队满
int full(CircleQueue *Q)
{
	return Q->count == QUEUE_SIZE;
}

//入队
void enqueue(CircleQueue *Q, int elem)
{
	if(full(Q))
	{
		printf("Queue overflow\n");
		exit(-1);
	}
	Q->data[Q->rear] = elem;
	Q->rear = (Q->rear + 1) % QUEUE_SIZE;
	Q->count++;
}

//出队
void dequeue(CircleQueue *Q)
{
	if(empty(Q))
	{
		printf("Queue underflow\n");
		exit(-1);
	}
	Q->front = (Q->front + 1) % QUEUE_SIZE;
	Q->count--;
}

//取队头元素
int getFront(CircleQueue *Q)
{
	if(empty(Q))
	{
		printf("Queue empty\n");
		exit(-1);
	}
	return Q->data[Q->front];
}

int main()
{
	CircleQueue Q;
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
