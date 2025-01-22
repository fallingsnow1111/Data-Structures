#include <stdio.h>

/*
����
*/
//ϡ��������Ԫ��˳���ʾ
#define MAXZISE 100
typedef int	Elemtype;
typedef struct
{
	int i, j;
	Elemtype e;
}Triple;
typedef struct
{
	Triple data[MAXZISE + 1];
	int mu, nu, tu;	//�У��У�����Ԫ��
}TSMatrix;

//ϡ�������Ԫ���µ�ת��
void TransMatrix(TSMatrix M, TSMatrix* T)
{
	T->mu = M.nu; T->nu = M.mu; T->tu = M.tu;
	if (T->tu != 0)
	{
		int p = 1;	//ת�ú�������Ԫ����
		int q;		//����M��Ԫ�ص��α�
		for (int col = 1; col <= M.nu; col++)	//����ÿһ��Ԫ���ҵ�����Ԫ��ת��
		{
			for (q = 1; q <= M.tu; q++)
			{
				if (M.data[q].j == col)
				{
					T->data[p].i = M.data[q].j; T->data[p].j = M.data[q].i; T->data[p].e = M.data[q].e;
					p++;
				}
			}
		}
	}
	printf("ת�����");
}

//ϡ������ʮ�������ʾ
typedef struct OLNode
{
	int i, j;
	Elemtype e;
	struct OLNode* right, * down;
}OLNode, *OLink;
typedef struct
{
	//ʹ�ö���ָ�봴��һ��ͷָ�������Ա�ͨ��rhead[i]��chead[j]�����ҵ�ÿһ�е�����ͷ���
	OLink* rhead, * chead;
	int mu, nu, tu;
}CrossList;

/*
�����
*/
typedef int AtomType;
typedef enum { ATOM, LIST }ElemTag;	//ö������Ĭ�ϵ�һ������Ϊ0

//ͷβ����洢��ʾ
typedef struct GLNode
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct
		{
			struct GLNode* hp, * tp;
		}ptr;	//ptr��һ���ṹ�壬�ں�ptr.hp��ptr.tp
	};
}GLNode, *GList;

//��չ��������洢��ʾ
typedef struct GLNode1
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct GLNode1* hp;
	};
	struct GLNode1* tp;	//��ͷβ����ͬ����ԭ�ӽ��Ҳ��βָ��ָ����һԪ��
}GLNode1, *GList1;