#include <stdio.h>

/*����˳��洢��ʾ*/
#define MAXSTRLEN 100
typedef unsigned char SString[MAXSTRLEN+1];

//������
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
		printf("δ�ض�\n");
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
		printf("s2�ѽض�\n");
	}
	else
	{
		for (i = 1; i <= MAXSTRLEN; i++)
		{
			*(T[i]) = s1[i];
		}
		*(T[0]) = MAXSTRLEN;
		printf("s1�ѽض�\n");
	}
}

//���Ӵ�
void SubString(SString* T, SString s1, int pos, int len)
{
	if (pos<1 || len>s1[0] || len<0 || len>s1[0] - pos + 1)
		printf("�Ƿ�������\n");
	for (int i = 1, j = pos; i < len ; i++, j++)
	{
		*T[i] = s1[j];

	}
	*T[0] = len;
}

/*�ѷ����ʾ*/
typedef struct
{
	char* ch;
	int length;
}HString;

//������
void Concat_HS(HString* T, HString* s1, HString* s2)
{
	int i, j;
	T->ch = (char*)malloc((s1->length+s2->length)*sizeof(char));
	if (!T)
		printf("�ռ䲻��");
	for (i = 0; i < s1->length; i++)
	{
		//T->ch[i]�൱��*(T->ch + i),��������arrȷʵ��ָ�룬������arr[i]�ڷ�������Ԫ�أ�&arr[i]����Ԫ�ص�ַ
		T->ch[i] = s1->ch[i];
	}
	for (i = s1->length, j = 0; j < s2->length; j++)
	{
		T->ch[i] = s2->ch[j];
	}
	T->length = s1->length + s2->length;
}

/*
KMP�㷨������˳���ʾ��
*/

void Index_KMP(SString S, SString T, int pos)
{
	//���ܣ����ģʽ��T������S��posλ�ú������
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
		printf("ƥ��ɹ�������Ϊ��%d", i - T[0]);
	else
		printf("ƥ��ʧ��");
}

void get_next(SString T, int* next)
{
	int i = 1; int j = 0;
	next[1] = 0;
	while (i < T[0])	//next[1] = 0�� ֻ��Ҫ��T[0]-1��
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
