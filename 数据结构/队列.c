#include <stdio.h>

/*
������
*/
typedef int QElemtype;
typedef struct QNode
{
	QElemtype data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;  //�ṹ��ָ������
	QueuePtr rear;
}LinkQueue;

void EnQueue(LinkQueue* Q, QElemtype e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		printf("���ٿռ�ʧ��");
	else
	{
		p->data = e; p->next = NULL;	//�ṹ��ָ���->��������ʵ��ǽṹ���Ա��������p->data�Ǳ���
		Q->rear->next = p; Q->rear = p;	//�Ȱ��½ڵ����ӵ���β���ö�βָ���½ڵ�
		printf("��ӳɹ�");
	}
}

void DeQueue(LinkQueue* Q, QElemtype* e)
{
	if (Q->front == Q->rear)
		printf("ջ��");
	else
	{
		QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
		if (!p)
			printf("�ռ䲻���޷�ִ�г��Ӳ���");  //һ�㲻�ᷢ�����뵽��˳��д
		else
		{
			p = Q->front->next;
			*e = p->data;
			Q->front->next = p->next;
			//��ͷ����һ������β�ڵ㣬��ɾ���������һ���ڵ㣬���轫β���ָ��ͷ����ʾջ��
			if (Q->rear == p)	
			{
				Q->rear = Q->front;
			}
			free(p);
		}
	}
}

/*
ѭ�����У�˳����У�
*/
#define MAXSIZE 100

typedef struct
{
	QElemtype* base;	//baseָ��һ�������ռ�Ļ���ַ
	int front;
	int rear;			//βָ��ָ���βԪ�ص���һλ�� 
}SqQueue;

void Init_SqQueue(SqQueue* Q)
{
	//Q->base�ǻ���ַ����Q->base[Q->rear]��ָ��QElemtype�ı�����������QElemtype*
	Q->base = (QElemtype*)malloc(MAXSIZE * sizeof(QElemtype));	
	if (!Q->base)
		printf("���ٿռ�ʧ��\n");
	else
	{
		Q->front = Q->rear = 0;
		printf("���г�ʼ���ɹ�\n");
	}
}

void EnSqQueue(SqQueue* Q, QElemtype e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		printf("ջ��");
	else
	{
		Q->base[Q->rear] = e;
		Q->rear = (Q->rear + 1) % MAXSIZE;
		printf("��ӳɹ�");
	}
}

void DeSqQueue(SqQueue* Q, QElemtype* e)
{
	if (Q->front == Q->rear)
		printf("ջ��");
	else
	{
		*e = Q->base[Q->front];
		Q->front = (Q->front + 1) % MAXSIZE;
		printf("���ӳɹ�");
	}
}