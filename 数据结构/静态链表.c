#include <stdio.h>

#define  MAXSIZE 100
typedef char Elemtype;

typedef struct
{
	Elemtype data;
	int cur;
}component, SLinkLisk[MAXSIZE];

void InitSpace_SL(SLinkLisk space)
{
	int i;
	for (i = 0; i < MAXSIZE - 1; i++) space[i].cur = i + 1;
	space[i].cur = 0;
}

int Malloc_SL(SLinkLisk space)
{
	int i;
	i = space[0].cur;
	if (space[i].cur) space[0].cur = space[i].cur;
	return i;
}

//回收下标为k的结点
void Free_SL(SLinkLisk space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//在静态链表第i个元素之前插入元素e
int Inert_SLL(SLinkLisk space, int i, Elemtype e)
{
	int j, k, l;
	k = MAXSIZE-1;
	if (i<1 || i> Length(space) + 1)  //i=1时下面的连接操作仍然可成功
		return 1;
	j = Malloc_SL(space);
	if (j)
	{
		//找到静态链表第i-1个元素的下标
		for (l = 1; l <= i - 1; l++)  //第一次循环得到第一个元素的下标，第二次是第二个元素，以此类推
			k = space[k].cur;
		space[j].cur = space[k].cur;
		space[j].data = e;
		space[k].cur = j;
		return 0;
	}
	else
		return 1;
}

//删除静态链表第i个元素
int Delete_SSL(SLinkLisk space, int i)
{
	int j, k, l;
	k = MAXSIZE - 1;
	if (i<1 || i > Length(space))  //i=1的时候真的把头结点（第一个元素）删除了，笑了
		return 1;
	for(l=1;l<=i-1;l++)
		k = space[k].cur;
	j = space[k].cur;
	space[k].cur = space[j].cur;
	Free_SL(space, j);
	return 0;
}

