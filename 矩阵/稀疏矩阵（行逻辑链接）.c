#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAXSIZE 20	//矩阵非零元最大个数
#define MAXRC 10	//矩阵最大行数
#define MAXCC 10	//矩阵最大行数
typedef struct {
	int row;	//非零元行下标
	int col;	//非零元列下标
	int elem;	//非零元
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];	//非零元三元组表
	int rpos[MAXRC + 1];	//各行第一个非零元的位置表，用于矩阵相乘
	int cpos[MAXCC + 1];	//各列第一个非零元的位置表，用于快速转置
	int rows;	//矩阵行数
	int cols;	//矩阵列数
	int elems;	//矩阵非零元数
}RLSMatrix;

//初始化rpos cpos向量，init()会调用这个函数
void cal_rpos_cpos(RLSMatrix *M)
{
	int num_row[M->rows];
	for(int i = 0; i < M->rows; i++)
	{
		num_row[i] = 0;
	}
	for(int i = 1; i <= M->elems; i++)
	{
		//求M中每一行非零元个数
		++num_row[M->data[i].row];
	}
	
	M->rpos[1] = 1;
	for(int i = 2; i <= M->rows; i++)
	{
		M->rpos[i] = M->rpos[i - 1] + num_row[i - 1];
	}
	
	int num_col[M->cols];
	for(int i = 0; i < M->cols; i++)
	{
		num_col[i] = 0;
	}
	for(int i = 1; i <= M->elems; i++)
	{
		//求M中每一行非零元个数
		++num_col[M->data[i].col];
	}
	
	M->cpos[1] = 1;
	for(int i = 2; i <= M->cols; i++)
	{
		M->cpos[i] = M->cpos[i - 1] + num_col[i - 1];
	}
}
//初始化矩阵
void init(RLSMatrix *M)
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
	
	cal_rpos_cpos(M);
}

//清空矩阵
void clear(RLSMatrix *M)
{
	memset(M->data,0,sizeof(int) * (MAXSIZE + 1));
	memset(M->rpos,0,sizeof(int) * (MAXRC + 1));
	memset(M->cpos,0,sizeof(int) * (MAXCC + 1));
	M->rows = 0;
	M->cols = 0;
	M->elems = 0;
}

//打印
void print(RLSMatrix *M)
{
	//打印三元组
	printf("row\tcol\telem\n");
	for(int i = 1; i <= M->elems; i++)
	{
		printf("%d\t%d\t%d\n",M->data[i].row, M->data[i].col, M->data[i].elem);
	}
	printf("\n");
	
	//打印rpos
	printf("row\t\t");
	for(int i = 1; i <= M->rows; i++)
	{
		printf("%d\t", i);
	}
	printf("\nrpos[row]\t");
	for(int i = 1; i <= M->rows; i++)
	{
		printf("%d\t", M->rpos[i]);
	}
	printf("\n\n");
	
	//打印cpos
	printf("col\t\t");
	for(int i = 1; i <= M->cols; i++)
	{
		printf("%d\t", i);
	}
	printf("\ncpos[col]\t");
	for(int i = 1; i <= M->cols; i++)
	{
		printf("%d\t", M->cpos[i]);
	}
	printf("\n\n");
}

void print_rpos_cpos(RLSMatrix *M)
{
	
}
//复制矩阵
void copy(RLSMatrix *T, RLSMatrix *S)
{
	*T = *S;
}

//M1加M2
void add(RLSMatrix *M, RLSMatrix *M1, RLSMatrix *M2)
{
	clear(M);
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
	cal_rpos_cpos(M);
}

//M1减M2
void sub(RLSMatrix *M, RLSMatrix *M1, RLSMatrix *M2)
{
	clear(M);
	RLSMatrix temp;
	copy(&temp, M2);
	for(int i = 1; i <= temp.elems; i++)
	{
		temp.data[i].elem *= -1;
	}
	add(M, M1, &temp);
}

//M1左乘M2(未完成)，为求M的值，只需在M1 M2中找到相应的各对元素（M1.data的列 == M2.data的行）相乘再累加即可
void mul(RLSMatrix *M, RLSMatrix *M1, RLSMatrix *M2)
{
	if(M1->cols != M2->rows)
	{
		printf("Can't multiply\n");
		exit(-1);
	}
	M->rows = M1->rows;
	M->cols = M2->cols;
	if(M1->elems * M2->elems != 0)	//M是非零矩阵
	{
		int *ctemp = malloc(sizeof(int) * M1->rows);	//行累加器
		for(int M1_row = 1; M1_row <= M1->rows; M1_row++)
		{
			ctemp[M1_row] = 0;	//清空当前行累加器
			M->rpos[M1_row] = M->elems + 1;
			
			//tp指向当前行的最后一个元素
			int tp;	
			if(M1_row < M1->rows)
			{
				tp = M1->rpos[M1_row + 1] - 1;
			}
			else
			{
				tp = M1->elems;
			}
			
			int M2_col;
			for(int p = M1->rpos[M1_row]; p <= tp; p++)	//对当前行每个非零元
			{
				int M2_row = M1->data[p].col;	//找到对应元在M2中的行号
				
				//t指向当前行的最后一个元素
				int t;
				if(M2_row < M2->rows)
				{
					t = M2->rpos[M2_row + 1] - 1;
				}
				else
				{
					t = M2->elems;
				}
				
				for(int q = M2->rpos[M2_row]; q <= t; q++)
				{
					M2_col = M2->data[q].col;
					ctemp[M2_col] += M1->data[p].elem * M2->data[q].elem;//这里看不懂，估计有错误
				}
			}
			
			M->elems = 0;
			for(M2_col = 1; M2_col <= M->cols; M2_col++)	//压缩存储该行
			{
				if(ctemp[M2_col])	//累积和不为零
				{
					if(++M->elems > MAXSIZE)
					{
						printf("非零元过多\n");
						exit(-1);
					}
					M->data[M->elems].row = M1_row;
					M->data[M->elems].col = M2_col;
					M->data[M->elems].elem = ctemp[M2_col];
				}
			}
		}
	}
	cal_rpos_cpos(M);
}


//快速转置,M转置为T，按照M中三元组次序进行转置，通过rpos[],将转置后的三元组插入T恰当的位置
void tran(RLSMatrix *M, RLSMatrix *T)
{
	clear(T);
	T->rows = M->cols;
	T->cols = M->rows;
	T->elems = M->elems;
	if(!T->elems)
	{
		return;
	}
	for(int i = 1; i <= M->elems; i++)
	{
		int row = M->data[i].row;
		int col = M->data[i].col;
		int index = M->cpos[col];	//找到恰当的位置
		
		T->data[index].row = col;
		T->data[index].col = row;
		T->data[index].elem = M->data[i].elem;
		++M->cpos[col];	//下次恰当的位置要+1
	}
	cal_rpos_cpos(T);
}

int main()
{
	RLSMatrix M1;
	RLSMatrix M2;
	RLSMatrix M3;
	init(&M1);
	init(&M2);
	/*print(&M1);
	print_rpos_cpos(&M1);
	print(&M2);
	print_rpos_cpos(&M2);
	add(&M3, &M2, &M1);
	print(&M3);
	sub(&M3, &M1, &M2);
	print(&M3);
	print(&M2);
	tran(&M2, &M3);
	print(&M3);*/
	mul(&M3, &M1, &M2);
	print(&M3);
	printf("相乘没做出来，是错的\n");
	return 0;
}
