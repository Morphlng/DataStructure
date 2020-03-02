#pragma once
#include<stdio.h>
#include<stdlib.h>
//#include"BiTree.h"	//在二叉树非递归遍历算法中需要用到栈

const int STACK_INIT_SIZE = 100;
const int STACKINCREMENT = 100;

typedef int SElemtype;	//在图的深度优先非递归算法中需要使用

//typedef BiTree SElemtype; //在二叉树算法中需要把结点压入栈中

typedef struct {	//顺序栈定义
	SElemtype *base;	//栈底指针
	SElemtype *top;		//栈顶指针
	int stacksize;		//当前栈最大容量
}SqStack;

void InitStack(SqStack &S)	//初始化空栈
{
	S.base = (SElemtype*)malloc(STACK_INIT_SIZE * sizeof(SElemtype));
	if (!S.base)
	{
		printf("ERROR\n");
		exit(0);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

void DestroyStack(SqStack &S)
{
	if (S.base == S.top)	//如果为空栈
	{
		free(S.base);
		S.stacksize = 0;
	}
	else
		if(S.base != NULL)	//如果不是空栈
		{
			free(S.base);
			free(S.top);
			S.stacksize = 0;
		}
}

void ClearStack(SqStack &S)
{
	if (S.base == NULL)
	{
		printf("ERROR\n");
		exit(0);
	}
	else
		S.top = S.base;
}

SElemtype GetTop(SqStack S)	//返回栈顶元素的值
{
	if (S.top == S.base)
	{
		printf("ERROR\n");
		exit(0);
	}
	SElemtype e = *(S.top - 1);
	return e;
}

int StackLength(SqStack S)	//返回栈的长度
{
	return S.top - S.base;	//同类型指针可做加减操作
}

void Push(SqStack &S, SElemtype e)	//将元素e推入栈
{
	if (S.top - S.base >=S.stacksize)	//如果栈已满，则扩容
	{
		S.base = (SElemtype*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemtype));
		if (!S.base)
		{
			printf("ERROR\n");
			exit(0);
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
}

SElemtype Pop(SqStack &S)	//若栈不为空，删除栈顶元素，返回其值
{
	if (S.top == S.base)	//栈为空
	{
		printf("EMPTY STACK\n");
		exit(0);
	}
	SElemtype e = *--S.top;
	return e;
}

bool StackEmpty(SqStack &S)	//判断是否为空栈
{
	if (S.base == NULL)	//判断栈是否存在
	{
		printf("ERROR\n");
		exit(0);
	}
	else
	{
		if (S.top == S.base)
			return true;	//若栈顶指针和栈底指针指向同一位置，则为空栈
		else
			return false;
	}
}