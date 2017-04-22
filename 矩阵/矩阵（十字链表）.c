//两个稀疏矩阵相加，相乘结果不一定是稀疏矩阵
//当矩阵的非零元个数和位置在操作过程中变化较大时，不易采用顺序存储结构，用十字链表比较合适
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct OLNode {
	int row,col;	//非零元的行和列下标
	int elem;
	struct OLNode *right;	//该非零元所在行的后继链域
	struct OLNode *down;	//该非零元所在列的后继链域
}OLNode, *OLink;

typedef struct {
	OLink *rhead;	//行链表的头指针(类型为OLink)数组，由create分配
	OLink *chead;	//列链表的头指针(类型为OLink)数组，由create分配
	int rows;		//行数
	int cols;		//列数
	int elems;		//非零元个数
}CrossList;



void create(CrossList *M)
{
	if(M)
	{
		free(M);
	}
	printf("输入矩阵的行数、列数、非零元个数：");
	int rows, cols, elems;
	scanf("%d%d%d", &rows, &cols, &elems);
	printf("%d %d %d\n", rows, cols, elems);
	
	M->rhead = (OLink *)malloc(sizeof(OLink) * (rows + 1));
	M->chead = (OLink *)malloc(sizeof(OLink) * (cols + 1));
	for(int i = 0; i <= rows; i++)
	{
		M->rhead[i] = NULL;
		M->rhead[0] = NULL;
	}
	//memset(M->rhead, 0, sizeof(OLink) * (rows + 1));
	
	memset(M->chead, 0, sizeof(OLink) * (cols + 1));
	return;
	M->rows = rows;
	M->cols = cols;
	M->elems = elems;
	
	
	for(int i = 1; i <= elems; i++)
	{
		
		printf("输入第%d个非零元的行数、列数、值：", i);
		M->rhead[0] = NULL;
		int row, col, elem;
		
		scanf("%d%d%d", &row, &col, &elem);
		
		
		OLNode *node = (OLNode *)malloc(sizeof(OLNode));
		node->row = row;
		node->col = col;
		node->elem = elem;
		
		
		//非零元初始化完毕，开始插入
		if(M->rhead[row] == NULL || col < M->rhead[row]->col)	//M->rhead[row]有问题
		{
			
			//在行头插入
			node->right = M->rhead[row];
			M->rhead[row] = node;
			
		}
		else
		{
			//在行中插入
			OLNode *ptr = M->rhead[row];
			while(ptr != NULL && col > ptr->right->col)
			{
				ptr = ptr->right;
			}
			node->right = ptr->right;
			ptr->right = node;
		}
		if(M->chead[col] == NULL || row < M->chead[col]->row)
		{
			//在列顶插入
			node->down = M->chead[col];
			M->chead[col] = node;
			
		}
		else
		{
			//在列中插入
			OLNode *ptr = M->chead[col];
			while(ptr != NULL && row > ptr->down->row)
			{
				ptr = ptr->down;
			}
			node->down = ptr->down;
			ptr->down = node;
		}
	}
}

void print(CrossList *M)
{
	printf("row\tcol\telem\n");
	for(int row = 1; row <= M->rows; row++)
	{
		OLNode *ptr = M->rhead[row];
		if(!ptr)
		{
			continue;
		}
		while(ptr != NULL)
		{
			printf("%d\t%d\t%d\n", ptr->row, ptr->col, ptr->elem);
			ptr = ptr->right;
		}
	}
}
int main()
{
	//printf("aaa");
	CrossList *M1 = (CrossList *)malloc(sizeof(CrossList));
	create(M1);
	//print(M1);
	return 0;
}
