#include <stdio.h>

/*
˳��ջ
*/
#define MAXSIZE 100
#define STACK_INCREMENT 10
typedef int SElemtype;  //���涨�����������Elemtype������

typedef struct
{
	SElemtype* base;
	SElemtype* top;
	int stacksize;
}SqStack;

int push(SqStack *S, SElemtype e)  //��*�ű�ʾ����ָ�����͵Ĳ���
{
	if (S->top - S->base >= S->stacksize)  //stacksize����ʼ��ΪMAXSIZE
	{
		S->base = (SElemtype*)realloc(S->base, (MAXSIZE + STACK_INCREMENT)*sizeof(SElemtype));  //ջ��������10���ռ䣬realloc����ʧ���򷵻�null
		if (!S->base)
			return 1;
		S->top = S->base + S->stacksize;
		S->stacksize += STACK_INCREMENT;  //ջ��������
	}
	*S->top++ = e;  //++�ں��ʾ��ʹ��������
	return 0;
}

int pop(SqStack *S, SElemtype *e)
{
	if (S->top == S->base)
		return 1;
	*e = *(--S->top);  //���Լ��ٵ�������Ϊջ������ָ��һ���յĿ��õĿռ�
	return 0;
}


/*
��ջ
*/
typedef int LSelemtype;
typedef struct Node
{
	LSelemtype data;
	struct Node* next;
}LinkStack;

int Push(LinkStack* top, LSelemtype e)
{
	if (top == NULL)
	{
		top = (LinkStack*)malloc(sizeof(LSelemtype));
		if (!top)
			return 1;
		top->data = e;
		top->next = NULL;
		return 0;
	}

	LinkStack* Newnode = (LinkStack*)malloc(sizeof(LSelemtype));
	if (!top)
		return 1;
	Newnode->data = top->data;
	Newnode->next = top->next;
	top->next = Newnode;
	top->data = e;
	return 0;
}

void Pop(LinkStack* top, LSelemtype* e)
{
	if (top == NULL)
		printf("ջ��");
	else
	{
		LinkStack* Oldtop = top;  //��Ҫ������ջ���ĵ�ַ�Ժ��ͷ�
		*e = top->data;
		top = top->next;
		free(Oldtop);
	}
}