#include <stdio.h>

/*
顺序栈
*/
#define MAXSIZE 100
#define STACK_INCREMENT 10
typedef int SElemtype;  //上面定义的数量就是Elemtype的数量

typedef struct
{
	SElemtype* base;
	SElemtype* top;
	int stacksize;
}SqStack;

int push(SqStack *S, SElemtype e)  //加*号表示传入指针类型的参数
{
	if (S->top - S->base >= S->stacksize)  //stacksize被初始化为MAXSIZE
	{
		S->base = (SElemtype*)realloc(S->base, (MAXSIZE + STACK_INCREMENT)*sizeof(SElemtype));  //栈满则增加10个空间，realloc开辟失败则返回null
		if (!S->base)
			return 1;
		S->top = S->base + S->stacksize;
		S->stacksize += STACK_INCREMENT;  //栈容量增加
	}
	*S->top++ = e;  //++在后表示先使用再自增
	return 0;
}

int pop(SqStack *S, SElemtype *e)
{
	if (S->top == S->base)
		return 1;
	*e = *(--S->top);  //先自减再弹出，因为栈顶总是指向一个空的可用的空间
	return 0;
}


/*
链栈
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
		printf("栈空");
	else
	{
		LinkStack* Oldtop = top;  //需要保留旧栈顶的地址稍后释放
		*e = top->data;
		top = top->next;
		free(Oldtop);
	}
}