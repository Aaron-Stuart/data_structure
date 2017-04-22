//串与线性表存储类似，区别在于操作的对象，线性表的操作对象一般是单个元素，串的操作对象一般是子串
//串用定长数组存储，S[0]存串长度，其实把串长拿出来存储更方便，只是北邮课件是这么存储的。。。考研党啊
#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 5
typedef unsigned char SString[MAX_STR_LEN + 1];

//常量赋值，未发生截断返回1，否则返回0
int assign(SString T, char *S)
{
	for(int i = 0; S[i] != '\0'; i++)
	{
		if(i == MAX_STR_LEN)
			return 0;
		T[i + 1] = S[i];
		T[0] = i + 1;
	}
	return 1;
}

//变量赋值，不会发生截断
int copy(SString T, SString S)
{
	for(int i = 0; i < S[0] + 1; i++)
	{
		T[i] = S[i];
	}
	return 1;
}

//判空
int empty(SString S)
{
	if(S[0] == 0)
		return 1;
	else
		return 0;
}

//字符串比较,S>T返回值>0
int compare(SString S, SString T)
{
	for(int i = 0; i <= S[0] && i <= T[0]; i++)
	{
		if(S[i] != T[i])
			return S[i] - T[i];
	}
	return S[0] - T[0];
}

//求串长
int length(SString S)
{
	return S[0];
}

//串清空
void clear(SString S)
{
	S[0] = 0;
}

//串连接，放在T中,未发生截断返回1，否则返回0
int concat(SString T, SString S1, SString S2)
{
	if(length(S1) + length(S2) <= MAX_STR_LEN)
	{
		copy(T,S1);
		for(int i = 1; i <= length(S2); i++)
		{
			T[length(S1) + i] = S2[i];
		}
		T[0] = S1[0] + S2[0];
		return 1;
	}
	else if(length(S1) < MAX_STR_LEN)
	{
		copy(T, S1);
		for(int i = length(S1) + 1, j = 1; i < MAX_STR_LEN + 1; i++, j++)
		{
			T[i] = S2[j];
		}
		T[0] = MAX_STR_LEN;
		return 0;
	}
	else
	{
		copy(T, S1);
		return 0;
	}
}

//求子串，用sub返回S从第pos个字符起，长度为len的子串，非法时返回空串
//非法时返回空串可增加程序的健壮性
void subString(SString Sub, SString S, int pos, int len)
{
	if(pos < 1 || pos > length(S) || len <= 0 || pos + len > length(S) + 1)
	{
		Sub[0] = 0;
		return;
	}
	
	for(int i = 1; i <= len; i++)
	{
		Sub[i] = S[pos + i - 1];
	}
	Sub[0] = len;
}

//子串定位(返回S中从第pos个字符起第一个T子串的位置，否则返回0)
int index(SString S, SString T, int pos)
{
	//注意for边界
	for(int i = pos; i <= length(S) - length(T) + 1; i++)
	{
		int flag = 1;
		for(int j = 1; j <= length(T); j++)
		{
			if(S[i + j - 1] != T[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			return i;
		}
	}
	return 0;
}

//串置换，用串V置换串S中的不重叠的子串T
void replace(SString S, SString T, SString V)
{
	
}

//插入串，在S的第pos个元素前插入串T
void insert(SString S, int pos, SString T)
{
	if(pos < 1 || pos >= length(S) || length(S) + length(T) > MAX_STR_LEN)
	{
		printf("insert string error\n");
		exit(-1);
	}
	
	SString temp1, temp2;
	subString(temp1, S, 1, pos - 1);
	subString(temp2, S, pos, length(S) - pos + 1);
	
	concat(S, temp1, T);
	concat(S, S, temp2);
}

//删除子串，从S中删除第pos个字符起长度为len的子串
void delete(SString S, int pos, int len)
{
	if(pos < 1 || pos > length(S) || len < 0 || pos + len > length(S) + 1)
	{
		printf("delete substring error\n");
		exit(-1);
	}
	SString temp1, temp2;
	subString(temp1, S, 1, pos - 1);
	subString(temp2, S, pos + len, length(S) - pos - len + 1);
	
	concat(S, temp1, temp2);
}

void print(SString S)
{
	for(int i = 1; i <= length(S); i++)
	{
		printf("%c",S[i]);
	}
	printf("\n");
}

int main()
{
	SString S1;
	printf("未截断 = %d\n", assign(S1,"abc"));
	print(S1);
	
	SString S2;
	printf("未截断 = %d\n", assign(S2,"de"));
	print(S2);
	
	printf("未截断 = %d\n", concat(S1, S1, S2));
	print(S1);
	
	SString S3;
	subString(S3, S1, 1, 2);
	print(S3);
	
	printf("%d\n", index(S1, S1, 1));
	
	delete(S1, 4, 2);
	print(S1);
	
	insert(S1, 3, S2);
	print(S1);
	return 0;
}
