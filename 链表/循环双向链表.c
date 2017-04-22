//从双向链表复制过来的，注释可能有误
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node *next;
	struct Node *pre;
}Node,*LinkList;

LinkList CreateFromHead()	//在头结点后插入，属于倒序
{
	LinkList L = (LinkList)malloc(sizeof(Node));	//分配头结点
	L->next = L;
	L->pre = L;
	
	int a;
	while(scanf("%d", &a))	//scanf成功返回个数，失败返回EOF
	{
		Node *s = (LinkList)malloc(sizeof(Node));
		s->data = a;
		s->next = L->next;
		s->pre = L;
		L->next = s; 
	}
	return L;
}

LinkList CreateFromTail()	//在链表尾插入，属于正序
{
	LinkList L = (LinkList)malloc(sizeof(Node));	//分配头结点
	L->next = L;
	L->pre = L;
	
	Node *tail = L;	//尾指针
	int a;
	
	while(scanf("%d", &a))	//scanf成功返回个数，失败返回EOF
	{
		Node *s = (LinkList)malloc(sizeof(Node));
		s->data = a;
		s->next = L;
		s->pre = tail;
		tail->next = s;
		tail = s;
	}
	return L;
}

int Get(LinkList L, int location)	//返回第location个元素的值
{
	LinkList head = L;
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

Node *Search(LinkList L, int key)	//成功返回key节点的位置，失败返回NULL
{
	LinkList head = L;
	while(L->next != head)
	{
		L = L->next;
		if(L->data == key)
			return L;
	}
	return NULL;
}

void Insert(LinkList L, int location, int a)	//插入a，使之成为地location个元素
{
	LinkList head = L;
	for(int i = 0; i < location - 1; i++)
	{
		if(L->next == head)
		{
			printf("can't insert\n");
			exit(-1);
		}
		L = L->next;
	}
	LinkList pre = L;
	
	Node *s = (Node *)malloc(sizeof(Node));
	s->data = a;
	if(!pre->next)	//插入到队尾要特殊处理
	{
		pre->next = s;
		s->next = NULL;
		s->pre = pre;
	}
	else
	{
		s->next = pre->next;
		pre->next = s;
		s->next->pre = s;
		s->pre = pre;
	}
}

void Delete(LinkList L, int location)	//删除第location个元素
{
	for(int i = 0; i < location; i++)
	{
		L = L->next;
	}
	L->pre->next = L->next;
	free(L);
}

void Modify(Node *node, int a)
{
	node->data = a;
}

void print(LinkList L)
{
	LinkList head = L;
	while(L->next != head)
	{
		L = L->next;
		printf("%d ", L->data);
	}
	printf("\n");
}

int main()
{
	LinkList L = CreateFromHead();
	print(L);
	printf("%d\n", Get(L, 1));
	
	Insert(L, 6, 10);
	print(L);
	Modify(Search(L, 10), 9);
	print(L);
	return 0;
}
