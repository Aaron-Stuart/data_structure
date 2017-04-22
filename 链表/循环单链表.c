//与单链表区别在于，判断链表结束不是等于NULL，而是等于头指针
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node *next;
}Node,*LoopList;

LoopList CreateFromHead()	//在头结点后插入，属于倒序
{
	LoopList L = (LoopList)malloc(sizeof(Node));	//分配头结点
	L->next = L;	//空时，头节点指向自己
	
	int a;
	while(scanf("%d ", &a))	//scanf成功返回个数，失败返回EOF
	{
		Node *s = (LoopList)malloc(sizeof(Node));
		s->data = a;
		s->next = L->next;
		L->next = s; 
	}
	return L;
}

LoopList CreateFromTail()	//在链表尾插入，属于正序
{
	LoopList L = (LoopList)malloc(sizeof(Node));	//分配头结点
	L->next = L;
	
	Node *tail = L;	//尾指针
	int a;
	
	while(scanf("%d", &a))	//scanf成功返回个数，失败返回EOF
	{
		Node *s = (LoopList)malloc(sizeof(Node));
		s->data = a;
		s->next = L;
		tail->next = s;
		tail = s;
	}
	return L;
}

int Get(LoopList L, int location)	//返回第location个元素的值
{
	LoopList head = L;
	for(int i = 0; i < location; i++)
	{
		if(L->next == head)
		{
			printf("can't get\n");
			exit(-1);
		}
		L = L->next;
	}
	return L->data;
}

Node *Search(LoopList L, int key)	//成功返回key节点的位置，失败返回NULL
{
	LoopList head = L;
	while(L->next != head)
	{
		L = L->next;
		if(L->data == key)
			return L;
	}
	return NULL;
}

void Insert(LoopList L, int location, int a)	//插入a，使之成为地location个元素
{
	Node *pre = L;	//指向前一节点的指针
	for(int i = 0; i < location - 1; i++)
	{
		if(L->next == L)
		{
			printf("can't insert\n");
			exit(-1);
		}
		L = L->next;
	}
	pre = L;
	Node *s = (Node *)malloc(sizeof(Node));
	
	s->data = a;
	s->next = pre->next;
	pre->next = s;
}

void Delete(LoopList L, int location)	//删除第location个元素
{
	for(int i = 0; i < location - 1; i++)
	{
		L = L->next;
	}
	LoopList temp = L->next->next;	//保存第location+1个元素的地址
	free(L->next);					//释放第location个元素
	L->next = temp;					//重新链接链表
}

void Modify(Node *node, int a)
{
	node->data = a;
}

//合并两个循环单链表
LoopList Merge(LoopList LA, LoopList LB)
{
	LoopList tail_LA = LA;
	while(tail_LA->next != LA)
	{
		tail_LA = tail_LA->next;
	}
	tail_LA->next = LB->next;	//LA尾指针指向LB第一个元素
	
	LoopList tail_LB = LB;
	while(tail_LB->next != LB)
	{
		tail_LB = tail_LB->next;
	}
	tail_LB->next = LA;			//LB尾指针指向LA头结点
	
	free(LB);
	return LA;
}

void print(LoopList L)
{
	LoopList head = L;
	while(L->next != head)
	{
		L = L->next;
		printf("%d ", L->data);
	}
	printf("\n");
}

int main()
{
	LoopList L = CreateFromHead();
	getchar();
	LoopList L1 = CreateFromHead();
	
	L = Merge(L, L1);
	print(L);
	printf("%d\n", Get(L, 1));

	Insert(L, 6, 10);
	print(L);
	Modify(Search(L, 10), 9);
	print(L);
	
	return 0;
}
