#include <stdio.h>

/*定长顺序存储表示*/
#define MAXSTRLEN 100
typedef unsigned char SString[MAXSTRLEN+1];

//串连接
void Concat(SString* T, SString s1, SString s2)
{
	int i,j;
	if (s1[0] + s2[0] <= MAXSTRLEN)
	{
		for (i = 1; i < s1[0]; i++)
		{
			*(T[i]) = s1[i];
		}
		*(T[0]) = s1[0];	
		printf("未截断\n");
	}
	else if (s1[0]<MAXSTRLEN && s1[0] + s2[0]>MAXSTRLEN)
	{
		for (i = 1; i < s1[0]; i++)
		{
			*(T[i]) = s1[i];
		}
		for (i = s1[0] + 1,j=1; i <= MAXSTRLEN; i++,j++)
		{
			*(T[i]) = s2[j];
		}
		*(T[0]) = MAXSTRLEN;
		printf("s2已截断\n");
	}
	else
	{
		for (i = 1; i <= MAXSTRLEN; i++)
		{
			*(T[i]) = s1[i];
		}
		*(T[0]) = MAXSTRLEN;
		printf("s1已截断\n");
	}
}

//求子串
void SubString(SString* T, SString s1, int pos, int len)
{
	if (pos<1 || len>s1[0] || len<0 || len>s1[0] - pos + 1)
		printf("非法操作！\n");
	for (int i = 1, j = pos; i < len ; i++, j++)
	{
		*T[i] = s1[j];

	}
	*T[0] = len;
}

/*堆分配表示*/
typedef struct
{
	char* ch;
	int length;
}HString;

//串连接
void Concat_HS(HString* T, HString* s1, HString* s2)
{
	int i, j;
	T->ch = (char*)malloc((s1->length+s2->length)*sizeof(char));
	if (!T)
		printf("空间不足");
	for (i = 0; i < s1->length; i++)
	{
		//T->ch[i]相当于*(T->ch + i),数组名如arr确实是指针，但加上arr[i]在访问数组元素，&arr[i]才是元素地址
		T->ch[i] = s1->ch[i];
	}
	for (i = s1->length, j = 0; j < s2->length; j++)
	{
		T->ch[i] = s2->ch[j];
	}
	T->length = s1->length + s2->length;
}

/*
KMP算法（定长顺序表示）
*/

void Index_KMP(SString S, SString T, int pos)
{
	//功能：求出模式串T在主串S的pos位置后的索引
	int i = pos; int j = 0;
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j])
		{
			i++; j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j > T[0])
		printf("匹配成功，索引为：%d", i - T[0]);
	else
		printf("匹配失败");
}

void get_next(SString T, int* next)
{
	int i = 1; int j = 0;
	next[1] = 0;
	while (i < T[0])	//next[1] = 0， 只需要求T[0]-1个
	{
		if (j == 0 || T[i] == T[j])
		{
			i++; j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}
