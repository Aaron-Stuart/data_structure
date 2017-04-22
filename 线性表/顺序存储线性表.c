//顺序存储，location从1开始，插入、删除、修改、查找、排序
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

typedef struct Linear_Table{

	int data[MAXSIZE];
	int length;	//当前元素个数
}List;

void insert(List *L, int location, int a)	//插入成为第Location个元素
{
	if(L->length == MAXSIZE)
	{
		printf("already full\n");
		exit(-1);
	}
	//后移
	for(int i = L->length; i != location - 1; i--)
	{
		L->data[i] = L->data[i - 1];
	}
	//赋值
	L->data[location - 1] = a;
	L->length++;
}

void delete(List *L, int location)	//删除第location个元素
{
	if(location > L->length)
	{
		printf("can't delete\n");
		exit(-1);
	}
	for(int i = location; i < L->length; i++)
	{
		L->data[i - 1] = L->data[i];
	}
	L->length--;
	
}

int locate(List *L, int key)	//搜索key，返回key是第几个元素，不存在则返回0
{
	for(int i = 0; i < L->length; i++)
	{
		if(L->data[i] == key)
		{
			return i + 1;
		}
	}
	return 0;
}

void modify(List *L, int location, int a)	//修改第location个元素为a
{
	L->data[location - 1] = a;
}

void sort(List *L)	//冒泡排序，从小到大
{
	for(int i = 0; i < L->length - 1; i++)
	{
		for(int j = 0; j < L->length - i - 1; j++)
		{
			if(L->data[j] > L->data[j + 1])
			{
				int temp = L->data[j];
				L->data[j] = L->data[j + 1];
				L->data[j + 1] = temp;
			}
		}
	}
}

void print(List *L)
{
	for(int i = 0; i < L->length; i++)
	{
		printf("%d ",L->data[i]);
	}
	printf("\n");
}

int main()
{
	List L;
	L.length = 0;
	insert(&L, 1, 1);
	insert(&L, 1, 2);
	insert(&L, 3, 3);
	print(&L);
	delete(&L, locate(&L, 3));
	print(&L);
	sort(&L);
	print(&L);
	modify(&L, locate(&L, 1), 5);
	print(&L);
	return 0;
}
