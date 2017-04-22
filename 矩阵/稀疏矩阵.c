//稀疏矩阵的三元组顺序表存储，相乘未实现
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct {
	int row;	//非零元行下标
	int col;	//非零元列下标
	int elem;	//非零元
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];	//data[0]未用,按行序存储
	int rows;	//矩阵行数
	int cols;	//矩阵列数
	int elems;	//矩阵非零元数
}TSMatrix;

//初始化矩阵
void init(TSMatrix *M)
{
	printf("矩阵行数：");
	scanf("%d", &M->rows);
	putchar('\n');
	printf("矩阵列数：");
	scanf("%d", &M->cols);
	putchar('\n');
	printf("非零元个数：");
	scanf("%d", &M->elems);
	putchar('\n');
	for(int i = 1; i <= M->elems; i++)
	{
		printf("第%d个非零元行数：", i);
		scanf("%d", &M->data[i].row);
		putchar('\n');
		printf("第%d个非零元列数：", i);
		scanf("%d", &M->data[i].col);
		putchar('\n');
		printf("第%d个非零元：", i);
		scanf("%d", &M->data[i].elem);
		putchar('\n');
	}
}

//打印
void print(TSMatrix *M)
{
	printf("row\tcol\telem\n");
	for(int i = 1; i <= M->elems; i++)
	{
		printf("%d\t%d\t%d\n",M->data[i].row, M->data[i].col, M->data[i].elem);
	}
}

//复制矩阵
void copy(TSMatrix *T, TSMatrix *S)
{
	*T = *S;
}

//加
void add(TSMatrix *M, TSMatrix *M1, TSMatrix *M2)
{
	if(M1->rows != M2->rows || M1->cols != M2->cols)
	{
		printf("Can't add\n");
		exit(-1);
	}
	int i = 1;	//M1->data[]的索引
	int j = 1;	//M2->data[]的索引
	int k = 1;	//M3->data[]的索引
	while(i <= M1->elems && j <= M2->elems)
	{
		//行列数一致，非零元相加
		if(M1->data[i].row == M2->data[j].row && M1->data[j].col == M2->data[j].col)
		{
			M->data[k].elem = M1->data[i].elem + M2->data[j].elem;
			M->data[k].row = M1->data[i].row;
			M->data[k].col = M1->data[i].col;
			if(M->data[k].elem != 0)
			{
				k++;
			}
			i++;
			j++;
		}
		//M2在前，注意此处求值顺序
		if(M1->data[i].row > M2->data[j].row || M1->data[j].col > M2->data[j].col)
		{
			M->data[k].elem = M2->data[j].elem;
			M->data[k].row = M2->data[j].row;
			M->data[k].col = M2->data[j].col;
			k++;
			j++;
		}
		//M1在前，注意此处求值顺序
		if(M1->data[i].row < M2->data[j].row || M1->data[j].col < M2->data[j].col)
		{
			M->data[k].elem = M1->data[i].elem;
			M->data[k].row = M1->data[i].row;
			M->data[k].col = M1->data[i].col;
			k++;
			i++;
			
		}
	}
	//把剩下的非零元加入M
	if(i > M1->elems)
	{
		while(j <= M2->elems)
		{
			M->data[k].elem =M2->data[j].elem;
			M->data[k].row = M2->data[j].row;
			M->data[k].col = M2->data[j].col;
			k++;
			j++;
		}
	}
	else
	{
		while(i <= M1->elems)
		{
			M->data[k].elem =M1->data[i].elem;
			M->data[k].row = M1->data[i].row;
			M->data[k].col = M1->data[i].col;
			k++;
			i++;
		}
	}
	M->rows = M1->rows;
	M->cols = M1->cols;
	M->elems = k - 1;
}

//M1减M2
void sub(TSMatrix *M, TSMatrix *M1, TSMatrix *M2)
{
	TSMatrix temp;
	copy(&temp, M2);
	for(int i = 1; i <= temp.elems; i++)
	{
		temp.data[i].elem *= -1;
	}
	add(M, M1, &temp);
}

//M1左乘M2(未完成)
void mul(TSMatrix *M, TSMatrix *M1, TSMatrix *M2)
{
	if(M1->cols != M2->rows)
	{
		printf("Can't multiply\n");
		exit(-1);
	}
	M->rows = M1->rows;
	M->cols = M2->cols;
	
}

//慢速转置,M转置为T,该算法只在elems << rows * cols时效率高
void tran(TSMatrix *M, TSMatrix *T)
{
	T->rows = M->cols;
	T->cols = M->rows;
	T->elems = M->elems;
	if(!T->elems)
	{
		return;
	}
	int k = 1;	//T的下标
	for(int col = 1; col <= M->cols; col++)
	{
		for(int i = 1; i <= M->elems; i++)
		{
			//按M中col从大到小顺序转置，正好T是按行序
			if(M->data[i].col == col)
			{
				T->data[k].row = M->data[i].col;
				T->data[k].col = M->data[i].row;
				T->data[k].elem = M->data[i].elem;
				k++;
			}
		}
	}
}

int main()
{
	TSMatrix M1;
	TSMatrix M2;
	TSMatrix M3;
	init(&M1);
	init(&M2);
	print(&M1);
	print(&M2);
	add(&M3, &M2, &M1);
	print(&M3);
	sub(&M3, &M1, &M2);
	print(&M3);
	tran(&M2, &M3);
	print(&M3);
	return 0;
}

