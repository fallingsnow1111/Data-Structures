#include <stdio.h>

/*
链队列
*/
typedef int QElemtype;
typedef struct QNode
{
	QElemtype data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;  //结构体指针类型
	QueuePtr rear;
}LinkQueue;

void EnQueue(LinkQueue* Q, QElemtype e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		printf("开辟空间失败");
	else
	{
		p->data = e; p->next = NULL;	//结构体指针的->运算符访问的是结构体成员变量，故p->data是变量
		Q->rear->next = p; Q->rear = p;	//先把新节点连接到队尾再让队尾指向新节点
		printf("入队成功");
	}
}

void DeQueue(LinkQueue* Q, QElemtype* e)
{
	if (Q->front == Q->rear)
		printf("栈空");
	else
	{
		QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
		if (!p)
			printf("空间不足无法执行出队操作");  //一般不会发生，想到了顺手写
		else
		{
			p = Q->front->next;
			*e = p->data;
			Q->front->next = p->next;
			//若头结点后一个就是尾节点，即删除的是最后一个节点，则需将尾结点指向头结点表示栈空
			if (Q->rear == p)	
			{
				Q->rear = Q->front;
			}
			free(p);
		}
	}
}

/*
循环队列（顺序队列）
*/
#define MAXSIZE 100

typedef struct
{
	QElemtype* base;	//base指向一段连续空间的基地址
	int front;
	int rear;			//尾指针指向队尾元素的下一位置 
}SqQueue;

void Init_SqQueue(SqQueue* Q)
{
	//Q->base是基地址，而Q->base[Q->rear]是指向QElemtype的变量，而不是QElemtype*
	Q->base = (QElemtype*)malloc(MAXSIZE * sizeof(QElemtype));	
	if (!Q->base)
		printf("开辟空间失败\n");
	else
	{
		Q->front = Q->rear = 0;
		printf("队列初始化成功\n");
	}
}

void EnSqQueue(SqQueue* Q, QElemtype e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		printf("栈满");
	else
	{
		Q->base[Q->rear] = e;
		Q->rear = (Q->rear + 1) % MAXSIZE;
		printf("入队成功");
	}
}

void DeSqQueue(SqQueue* Q, QElemtype* e)
{
	if (Q->front == Q->rear)
		printf("栈空");
	else
	{
		*e = Q->base[Q->front];
		Q->front = (Q->front + 1) % MAXSIZE;
		printf("出队成功");
	}
}