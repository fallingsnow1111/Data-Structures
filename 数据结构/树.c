#include <stdio.h>

typedef char TElemtype;
//二叉链表定义
typedef struct BiTNode
{
	TElemtype data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

//三叉链表定义
typedef struct TriTNode
{
	TElemtype data;
	struct TriTNode *lchild, *rchild;
	struct TriTNode* parent;
}TriTNode, *TriTree;

/*
二叉树遍历
*/
void visit(BiTree T)
{
	printf("节点值：%c\n", T->data);
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
利用前序遍历构建二叉树
*/

BiTNode* CreatBiTNode(char x)
{
	BiTNode* NewNode = (BiTNode*)malloc(sizeof(BiTNode));
	if (!NewNode)
	{
		printf("空间不足，创建新节点失败\n");
		return NULL;
	}
	NewNode->data = x;
	NewNode->lchild = NULL;
	NewNode->rchild = NULL;

	return NewNode;		//返回创建的新节点的地址
}

//传入pi指针来保证它是全局变量，避免在深层栈中自增而回调至浅层栈时却未改变的情况
BiTNode* CreatBiTree(char* arr, int* pi)	
{
	if (arr[*pi] == "#")
	{
		*(pi)++;
		return NULL;
	}
		
	BiTNode* NewTree = CreatBiTNode(arr[*pi]);	//不是#号就创建新节点，并递归创建左右子树
	*(pi)++;	//继续往下遍历数组
	NewTree->lchild = CreatBiTree(arr, pi);
	NewTree->rchild = CreatBiTree(arr, pi);

	return NewTree;		//返回这个节点给上一层节点进行连接
}

/*
二叉线索树
*/
typedef struct TBTNode
{
	TElemtype data;
	struct TBTNode* lchild, * rchild;
	int ltag, rtag;		//0表示指针，1表示线索
}TBTNode;

//中序单向线索化
void CreatInThread(TBTNode* root)
{
	TBTNode** pre;
	(*pre) = NULL;	//前驱指针
	if (root != NULL)
	{
		InThread(root, pre);
		(*pre)->rchild = NULL;
		(*pre)->rtag = 1;
	}
}

//一级指针通过修改解引用后的值来保存值的变化，同理二级指针通过修改解引用后的地址来保存地址的变化
void InThread(TBTNode* p, TBTNode** pre)	//pre用来保存已遍历过的节点地址
{
	if (p != NULL)
	{
		InThread(p->lchild, pre);	//递归线索化左子树
		if (p->lchild == NULL)	//连接前驱
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (*pre != NULL && (*pre)->rchild == NULL)
		{
			(*pre)->rchild = p;
			(*pre)->rtag = 1;
		}
		(*pre) = p;		//标记刚刚访问的节点为前驱结点
		InThread(p->rchild, pre);
	}
}

void VisitTBTNode(TBTNode* T)
{
	printf("节点值：%c\n", T->data);
}

//封装函数：找到中序线索二叉树的第一个结点，后面要递归调用
TBTNode* First(TBTNode* p)
{
	while (p->ltag == 0)
		p = p->lchild;
	return p;
}

//找到中序线索二叉树中第一个节点的后继
TBTNode* Next(TBTNode* p)
{
	//若右孩子为指针，则右孩子最左下的结点才是当前节点的后继
	if (p->rtag == 0)
	{
		p = First(p->rchild);
		return p;
	}

	//若右孩子为线索则直接右孩就是后继
	return p->rchild;
}

//中序遍历线索二叉树
void InOrderTraverseTBT(TBTNode* root)
{
	TBTNode* p;
	for (p = root; p != NULL; p = Next(p))
		VisitTBTNode(p);
}

/*
树的储存表示
*/

#define MAX_TREE_SIZE 100
//双亲表示法
typedef struct PTNode
{
	TElemtype data;
	int parent;		//指示双亲在数组中的位置
}PTNode;

typedef struct
{
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;
}PTree;

//孩子表示法
typedef struct CTNode	
{
	TElemtype data;
	struct CTNode* next;
}*ChirdPtr;		//第一个孩子通过next遍历所有孩子
typedef struct
{
	TElemtype data;
	ChirdPtr firstchild;	//头结点先找到第一个孩子
}CTBox;
typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int r, n;
}CTree;

//双亲表示法
typedef struct CSTNode
{
	TElemtype data;
	struct CSTNode* firstchild, * nextsibing;	//结合孩子表示法和双亲表示法
}CSTNode, *CSTree;
