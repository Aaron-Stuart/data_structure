#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node *next;
}Node,*LinkList;

LinkList CreateFromHead()	//在头结点后插入，属于倒序
{
	LinkList L = (LinkList)malloc(sizeof(Node));	//分配头结点
	L->next = NULL;
	
	int a;
	while(scanf("%d", &a))	//scanf成功返回个数，失败返回EOF
	{
		Node *s = (LinkList)malloc(sizeof(Node));
		s->data = a;
		s->next = L->next;
		L->next = s; 
	}
	return L;
}

LinkList CreateFromTail()	//在链表尾插入，属于正序
{
	LinkList L = (LinkList)malloc(sizeof(Node));	//分配头结点
	L->next = NULL;
	
	Node *tail = L;	//尾指针
	int a;
	
	while(scanf("%d", &a))	//scanf成功返回个数，失败返回EOF
	{
		Node *s = (LinkList)malloc(sizeof(Node));
		s->data = a;
		s->next = NULL;
		tail->next = s;
		tail = s;
	}
	return L;
}

int Get(LinkList L, int location)	//返回第location个元素的值
{
	for(int i = 0; i < location; i++)
	{
		if(!L->next)
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
	while(L->next)
	{
		L = L->next;
		if(L->data == key)
			return L;
	}
	return NULL;
}

void Insert(LinkList L, int location, int a)	//插入a，使之成为地location个元素
{
	Node *pre = L;	//指向前一节点的指针
	for(int i = 0; i < location - 1; i++)
	{
		if(!L->next)
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

void Delete(LinkList L, int location)	//删除第location个元素
{
	for(int i = 0; i < location - 1; i++)
	{
		L = L->next;
	}
	LinkList temp = L->next->next;	//保存第location+1个元素的地址
	free(L->next);					//释放第location个元素
	L->next = temp;					//重新链接链表
}

void Modify(Node *node, int a)
{
	node->data = a;
}

void Sort(LinkList L)
{
	
}

void print(LinkList L)
{
	while(L->next)
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
	//printf("%d\n", Locate(L, 2)->data);
	Insert(L, 6, 10);
	print(L);
	Modify(Search(L, 10), 9);
	print(L);
	return 0;
}
