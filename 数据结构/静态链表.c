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

//�����±�Ϊk�Ľ��
void Free_SL(SLinkLisk space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//�ھ�̬�����i��Ԫ��֮ǰ����Ԫ��e
int Inert_SLL(SLinkLisk space, int i, Elemtype e)
{
	int j, k, l;
	k = MAXSIZE-1;
	if (i<1 || i> Length(space) + 1)  //i=1ʱ��������Ӳ�����Ȼ�ɳɹ�
		return 1;
	j = Malloc_SL(space);
	if (j)
	{
		//�ҵ���̬�����i-1��Ԫ�ص��±�
		for (l = 1; l <= i - 1; l++)  //��һ��ѭ���õ���һ��Ԫ�ص��±꣬�ڶ����ǵڶ���Ԫ�أ��Դ�����
			k = space[k].cur;
		space[j].cur = space[k].cur;
		space[j].data = e;
		space[k].cur = j;
		return 0;
	}
	else
		return 1;
}

//ɾ����̬�����i��Ԫ��
int Delete_SSL(SLinkLisk space, int i)
{
	int j, k, l;
	k = MAXSIZE - 1;
	if (i<1 || i > Length(space))  //i=1��ʱ����İ�ͷ��㣨��һ��Ԫ�أ�ɾ���ˣ�Ц��
		return 1;
	for(l=1;l<=i-1;l++)
		k = space[k].cur;
	j = space[k].cur;
	space[k].cur = space[j].cur;
	Free_SL(space, j);
	return 0;
}

