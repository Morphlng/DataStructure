#pragma once
#include<stdio.h>
#include<stdlib.h>
//#include"BiTree.h"		//应用二叉树时需要本句

const int MAXQSIZE = 100; //一般定义100，实验时定义为10
const int QUINCREMENT = 20;

typedef int QElemtype;
//typedef BiTree QElemtype;	//在以层序遍历二叉树时需要历用队列
//typedef ArcCell QElemtype;

typedef struct {		//循环队列——顺序结构
	QElemtype *base;	//初始分配空间
	int front;			//头指针
	int rear;			//尾指针
	int maxqsize;		//循环节最大长度
}SqQueue;

void InitQueue(SqQueue &Q)  //构造一个空循环队列
{
	Q.base = (QElemtype*)malloc(MAXQSIZE * sizeof(QElemtype));
	if (!Q.base)
	{
		printf("ERROR\n");
		exit(0);
	}
	Q.front = Q.rear = 0; //此处不一定为0
	Q.maxqsize = MAXQSIZE;
}

void DestoryQueue(SqQueue &Q) //销毁一个循环队列
{
	if (Q.base == NULL)
	{
		printf("ERROR\n");
		exit(0);
	}
	free(Q.base);
}

void ClearQueue(SqQueue &Q) //清空一个循环队列
{
	if (Q.base == NULL)
	{
		printf("ERROR\n");
		exit(0);
	}
	else
		Q.front = Q.rear;
}

bool QueueEmpty(SqQueue Q)	 //判断一个循环队列是否为空
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

int QueueLength(SqQueue Q)	 //得到循环队列元素个数
{
	return (Q.rear - Q.front + Q.maxqsize) % Q.maxqsize;
}

QElemtype GetHead(SqQueue Q)	   //得到队列Q的队头元素
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue\n");
		return 0;
	}
	else
		return Q.base[Q.front];
}

void SpecialEnqueue(SqQueue &Q, QElemtype e)	//10.14实验2的要求
{
	if ((Q.rear + 1) % Q.maxqsize == Q.front) //若队列已满，报错
	{
		printf("Queue FULL! exit\n");
		system("pause");
		exit(1);
	}
	else
	{
		Q.base[Q.rear] = e;
		Q.rear = (Q.rear + 1) % Q.maxqsize;	//队尾指针指向队尾元素的下一位置
	}

}

void EnQueue(SqQueue &Q, QElemtype e)  //插入元素e为Q的新队尾元素
{
	if ((Q.rear + 1) % Q.maxqsize == Q.front) //若队列已满
	{
		QElemtype* newBase = (QElemtype*)malloc((Q.maxqsize + QUINCREMENT) * sizeof(QElemtype));
		int j = 0;	//记录队列中元素个数
		int i = Q.front;
		while (i != Q.rear)	//将原来存放于Q.base中的队列元素拷贝到新地址中
		{
			newBase[j++] = Q.base[i];
			i = (i + 1) % Q.maxqsize;
		}
		Q.front = 0;	//将拷贝后头指针置0
		Q.rear = j;		//新队尾指针指向队尾元素下一位
		Q.maxqsize += QUINCREMENT;
		Q.base = newBase;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxqsize;
}

QElemtype DeQueue(SqQueue &Q)   //删除Q的队头元素并返回值
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue\n");
		return 0;
	}
	QElemtype e = Q.base[Q.front];	//把队头元素值赋予e并返回
	Q.front = (Q.front + 1) % Q.maxqsize;	//调整头指针到下一位置
	return e;
}