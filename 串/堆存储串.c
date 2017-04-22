//动态分配存储空间，克服了定长存储时，链接、插入、置换有可能发生截尾的弊病
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *ch;
	int length;
}HString;

void init(HString *T)
{
	T->ch = NULL;
	T->length = 0;
}

//常量赋值
void assign(HString *T, char *chars)
{
	if(T->ch)
		free(T->ch);
		
	int count;
	for(count = 0; chars[count] != '\0'; count++)
	{
		;
	}
	
	if(!count)
	{
		T->ch = NULL;
		T->length = 0;
	}
	else
	{
		T->ch = (char *)malloc(sizeof(char) * count);
		
		for(int i = 0; i < count; i++)
		{
			T->ch[i] = chars[i];
		}
		T->length = count;
	}
}

//变量赋值
void copy(HString *T, HString *S)
{
	if(T->ch)
		free(T->ch);
	T->ch = (char *)malloc(sizeof(char) * S->length);
	
	for(int i = 0; i < S->length; i++)
	{
		T->ch[i] = S->ch[i];
	}
	T->length = S->length;
}

//判空
int empty(HString *S)
{
	return S->length == 0;
}

//字符串比较，S>T,返回值>0
int compare(HString *S, HString *T)
{
	for(int i = 0; i <= S->length && i <= T->length; i++)
	{
		if(S->ch[i] != T->ch[i])
			return S->ch[i] - T->ch[i];
	}
	return S->length - T->length;
}

//求串长
int length(HString *S)
{
	return S->length;
}

//串清空
void clear(HString *S)
{
	free(S->ch);
	S->length = 0;
}

//串链接
void concat(HString *S, HString *S1, HString *S2)
{
	//用temp是因为有可能S和S1是同一个指针，这样为S动态分配时会把S1释放掉
	HString temp1, temp2;
	init(&temp1);
	init(&temp2);
	copy(&temp1, S1);
	copy(&temp2, S2);
	
	S->length = length(&temp1) + length(&temp2);
	S->ch = (char *)malloc(sizeof(char) * length(S));
	
	for(int i = 0; i < length(&temp1); i++)
	{
		S->ch[i] = temp1.ch[i];
	}
	for(int i = 0; i < length(&temp2); i++)
	{
		S->ch[length(&temp1) + i] = temp2.ch[i];
	}
}

//求子串，用sub返回S从第pos个字符起，长度为len的子串，非法时返回空串
//非法时返回空串可增加程序的健壮性
void subString(HString *Sub, HString *S, int pos, int len)
{
	if(pos < 1 || pos > length(S) || len <= 0 || pos + len > length(S) + 1)
	{
		Sub->ch = NULL;
		Sub->length = 0;
		return;
	}
	
	Sub->ch = (char *)malloc(sizeof(char) * len);
	Sub->length = len;
	
	for(int i = 0; i < len; i++)
	{
		Sub->ch[i] = S->ch[pos - 1 + i];
	}
}

//子串定位(返回S中从第pos个字符起第一个T子串的位置，否则返回0)
int index(HString *S, HString *T, int pos)
{
	//注意for边界
	for(int i = pos - 1; i <= length(S) - length(T); i++)
	{
		int flag = 1;
		for(int j = 0; j < length(T); j++)
		{
			if(S->ch[i + j] != T->ch[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			return i + 1;
		}
	}
	return 0;
}

//串置换，用串V置换串S中的不重叠的子串T
void replace(HString *S, HString *T, HString *V)
{
	
}

//插入串，在S的第pos个元素前插入串T
void insert(HString *S, int pos, HString *T)
{
	if(pos < 1 || pos > length(S))
	{
		printf("insert string error\n");
		exit(-1);
	}
	
	HString temp1, temp2;
	init(&temp1);
	init(&temp2);
	
	subString(&temp1, S, 1, pos - 1);
	subString(&temp2, S, pos, length(S) - pos + 1);
	
	concat(S, &temp1, T);
	concat(S, S, &temp2);
}

//删除子串，从S中删除第pos个字符起长度为len的子串
void delete(HString *S, int pos, int len)
{
	if(pos < 1 || pos > length(S) || len < 0 || pos + len > length(S) + 1)
	{
		printf("delete substring error\n");
		exit(-1);
	}
	HString temp1, temp2;
	init(&temp1);
	init(&temp2);
	
	subString(&temp1, S, 1, pos - 1);
	subString(&temp2, S, pos + len, length(S) - pos - len + 1);
	
	concat(S, &temp1, &temp2);
}

void print(HString *S)
{
	for(int i = 0; i < length(S); i++)
	{
		printf("%c",S->ch[i]);
	}
	printf("\n");
}

int main()
{
	HString S1;
	init(&S1);
	assign(&S1,"abc");
	print(&S1);
	
	HString S2;
	init(&S2);
	assign(&S2,"de");
	print(&S2);
	
	concat(&S1, &S1, &S2);
	print(&S1);
	
	HString S3;
	init(&S3);
	subString(&S3, &S1, 1, 2);
	print(&S3);
	
	printf("%d\n", index(&S1, &S2, 1));
	
	delete(&S1, 4, 2);
	print(&S1);
	
	insert(&S1, 3, &S2);
	print(&S1);
	return 0;
}
