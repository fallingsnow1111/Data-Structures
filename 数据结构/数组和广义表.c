#include <stdio.h>

/*
数组
*/
//稀疏矩阵的三元组顺序表示
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
	int mu, nu, tu;	//行，列，非零元数
}TSMatrix;

//稀疏矩阵三元组下的转置
void TransMatrix(TSMatrix M, TSMatrix* T)
{
	T->mu = M.nu; T->nu = M.mu; T->tu = M.tu;
	if (T->tu != 0)
	{
		int p = 1;	//转置后矩阵非零元个数
		int q;		//遍历M中元素的游标
		for (int col = 1; col <= M.nu; col++)	//遍历每一列元素找到非零元并转置
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
	printf("转置完成");
}

//稀疏矩阵的十字链表表示
typedef struct OLNode
{
	int i, j;
	Elemtype e;
	struct OLNode* right, * down;
}OLNode, *OLink;
typedef struct
{
	//使用二级指针创建一个头指针数组以便通过rhead[i]或chead[j]快速找到每一行的链表头结点
	OLink* rhead, * chead;
	int mu, nu, tu;
}CrossList;

/*
广义表
*/
typedef int AtomType;
typedef enum { ATOM, LIST }ElemTag;	//枚举类型默认第一个变量为0

//头尾链表存储表示
typedef struct GLNode
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct
		{
			struct GLNode* hp, * tp;
		}ptr;	//ptr是一个结构体，内含ptr.hp和ptr.tp
	};
}GLNode, *GList;

//拓展线性链表存储表示
typedef struct GLNode1
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct GLNode1* hp;
	};
	struct GLNode1* tp;	//和头尾链表不同的是原子结点也有尾指针指向下一元素
}GLNode1, *GList1;