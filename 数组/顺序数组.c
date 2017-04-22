#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>	//用于存取变长参数表，提供宏va_start、va_arg和va_end, va是variable-argument(可变参数)的意思
#define MAX_ARRAY_DIM 8

typedef struct {
	int *base;		//数组元素基址，由initArray()分配
	int dim;		//数组维数
	int *bounds;	//数组维界基址，由initArray()分配
	int *constants;	//数组映像函数常量基址，由initArray()分配
}Array;

//若维数dim和随后的各维长度合法，则构造数组A
void init(Array *A, int dim, ...)
{
	if(dim < 1 || dim > MAX_ARRAY_DIM)
	{
		printf("Invalid array dim\n");
		exit(-1);
	}
	A->dim = dim;
	A->bounds = (int *)malloc(sizeof(int) * dim);
	
	//若各维长度合法，则存入A->bounds,并求出A中元素总数
	int elemtotal = 1;
	va_list arg_ptr;		//存储参数地址的指针
	va_start(arg_ptr, dim);	//获取可变参数列表的第一个参数的地址(把函数的最后一个固定参数(这里是dim)之后的参数地址放到arg_ptr中)
	
	for(int i = 0; i < dim; i++)
	{
		A->bounds[i] = va_arg(arg_ptr, int);	//获取可变参数的当前参数，返回指定类型并将指针指向下一参数
		
		if(A->bounds[i] < 0)
		{
			printf("underflow\n");
			exit(-1);
		}
		
		elemtotal *= A->bounds[i];
	}
	va_end(arg_ptr);	//关闭初始化列表（将arg_ptr置空）。
	
	A->base = (int *)malloc(sizeof(int) * elemtotal);
	
	//求映像函数的常数，并存入A->constants[i - 1], i = 1,2,...,dim
	A->constants = (int *)malloc(sizeof(int) * dim);
	A->constants[dim - 1] = 1;
	for(int i = dim - 2; i >= 0; i--)
	{
		A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];
	}
}

void destroy(Array *A)
{
	if(!A->base)
	{
		printf("Destroy array error\n");
		exit(-1);
	}
	free(A->base);
	A->base = NULL;
	
	if(!A->bounds)
	{
		printf("Destroy array error\n");
		exit(-1);
	}
	free(A->bounds);
	A->bounds = NULL;
	
	if(!A->constants)
	{
		printf("Destroy array error\n");
		exit(-1);
	}
	free(A->constants);
	A->constants = NULL;
}

//若ap指示的各下标合法，则求出该元素在A中的相对地址off
void Locate(Array *A, va_list ap, int *off)
{
	*off = 0;
	for(int i = 0; i < A->dim; i++)
	{
		int ind = va_arg(ap, int);
		if(ind < 0 || ind >= A->bounds[i])
		{
			printf("overflow\n");
			exit(-1);
		}
		*off += A->constants[i] * ind;
	}
}

//A是n维数组，随后是n个下标值，若各下标不超界，则返回指定的元素值
int value(Array *A, ...)
{
	int off;
	va_list ap;
	va_start(ap, A);
	
	Locate(A, ap, &off);
	
	return *(A->base + off);
}

//A是n维数组，随后是n个下标值，若各下标不超界，则赋予e
void assign(Array *A, int e, ...)
{
	int off;
	va_list ap;
	va_start(ap, e);
	
	Locate(A, ap, &off);
	*(A->base + off) = e;
}

int main()
{
	Array A;
	init(&A, 3, 1, 2, 3);
	assign(&A, 100, 0, 1, 0);
	printf("%d\n", value(&A, 0, 1, 0));
	return 0;
}

