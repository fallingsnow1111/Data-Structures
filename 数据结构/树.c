#include <stdio.h>

typedef char TElemtype;
//����������
typedef struct BiTNode
{
	TElemtype data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

//����������
typedef struct TriTNode
{
	TElemtype data;
	struct TriTNode *lchild, *rchild;
	struct TriTNode* parent;
}TriTNode, *TriTree;

/*
����������
*/
void visit(BiTree T)
{
	printf("�ڵ�ֵ��%c\n", T->data);
}

void PreOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		visit(T);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		InOrderTraverse(T->lchild);
		visit(T);
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		visit(T);
	}
}

/*
����ǰ���������������
*/

BiTNode* CreatBiTNode(char x)
{
	BiTNode* NewNode = (BiTNode*)malloc(sizeof(BiTNode));
	if (!NewNode)
	{
		printf("�ռ䲻�㣬�����½ڵ�ʧ��\n");
		return NULL;
	}
	NewNode->data = x;
	NewNode->lchild = NULL;
	NewNode->rchild = NULL;

	return NewNode;		//���ش������½ڵ�ĵ�ַ
}

//����piָ������֤����ȫ�ֱ��������������ջ���������ص���ǳ��ջʱȴδ�ı�����
BiTNode* CreatBiTree(char* arr, int* pi)	
{
	if (arr[*pi] == "#")
	{
		*(pi)++;
		return NULL;
	}
		
	BiTNode* NewTree = CreatBiTNode(arr[*pi]);	//����#�žʹ����½ڵ㣬���ݹ鴴����������
	*(pi)++;	//�������±�������
	NewTree->lchild = CreatBiTree(arr, pi);
	NewTree->rchild = CreatBiTree(arr, pi);

	return NewTree;		//��������ڵ����һ��ڵ��������
}

/*
����������
*/
typedef struct TBTNode
{
	TElemtype data;
	struct TBTNode* lchild, * rchild;
	int ltag, rtag;		//0��ʾָ�룬1��ʾ����
}TBTNode;

//������������
void CreatInThread(TBTNode* root)
{
	TBTNode** pre;
	(*pre) = NULL;	//ǰ��ָ��
	if (root != NULL)
	{
		InThread(root, pre);
		(*pre)->rchild = NULL;
		(*pre)->rtag = 1;
	}
}

//һ��ָ��ͨ���޸Ľ����ú��ֵ������ֵ�ı仯��ͬ�����ָ��ͨ���޸Ľ����ú�ĵ�ַ�������ַ�ı仯
void InThread(TBTNode* p, TBTNode** pre)	//pre���������ѱ������Ľڵ��ַ
{
	if (p != NULL)
	{
		InThread(p->lchild, pre);	//�ݹ�������������
		if (p->lchild == NULL)	//����ǰ��
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (*pre != NULL && (*pre)->rchild == NULL)
		{
			(*pre)->rchild = p;
			(*pre)->rtag = 1;
		}
		(*pre) = p;		//��Ǹոշ��ʵĽڵ�Ϊǰ�����
		InThread(p->rchild, pre);
	}
}

void VisitTBTNode(TBTNode* T)
{
	printf("�ڵ�ֵ��%c\n", T->data);
}

//��װ�������ҵ����������������ĵ�һ����㣬����Ҫ�ݹ����
TBTNode* First(TBTNode* p)
{
	while (p->ltag == 0)
		p = p->lchild;
	return p;
}

//�ҵ����������������е�һ���ڵ�ĺ��
TBTNode* Next(TBTNode* p)
{
	//���Һ���Ϊָ�룬���Һ��������µĽ����ǵ�ǰ�ڵ�ĺ��
	if (p->rtag == 0)
	{
		p = First(p->rchild);
		return p;
	}

	//���Һ���Ϊ������ֱ���Һ����Ǻ��
	return p->rchild;
}

//�����������������
void InOrderTraverseTBT(TBTNode* root)
{
	TBTNode* p;
	for (p = root; p != NULL; p = Next(p))
		VisitTBTNode(p);
}

/*
���Ĵ����ʾ
*/

#define MAX_TREE_SIZE 100
//˫�ױ�ʾ��
typedef struct PTNode
{
	TElemtype data;
	int parent;		//ָʾ˫���������е�λ��
}PTNode;

typedef struct
{
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;
}PTree;

//���ӱ�ʾ��
typedef struct CTNode	
{
	TElemtype data;
	struct CTNode* next;
}*ChirdPtr;		//��һ������ͨ��next�������к���
typedef struct
{
	TElemtype data;
	ChirdPtr firstchild;	//ͷ������ҵ���һ������
}CTBox;
typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int r, n;
}CTree;

//˫�ױ�ʾ��
typedef struct CSTNode
{
	TElemtype data;
	struct CSTNode* firstchild, * nextsibing;	//��Ϻ��ӱ�ʾ����˫�ױ�ʾ��
}CSTNode, *CSTree;
