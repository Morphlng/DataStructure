#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int QElemtype;

typedef struct QNode {	//队列的链式表示
	QElemtype data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {	//链队列
	QueuePtr front;	//头指针
	QueuePtr rear;	//尾指针
}LinkQueue;

void InitQueue(LinkQueue &Q)	//构造空队列Q
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
	{
		printf("ERROR\n");
		exit(0);
	}
	Q.front->next = NULL;
}

void DestroyQueue(LinkQueue &Q)	//销毁队列Q
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

void ClearQueue(LinkQueue &Q)	 //将Q清为空队列
{
	Q.rear = Q.front;
	Q.front->next = NULL;
}

bool QueueEmpty(LinkQueue Q)	 //若队列Q为空则返回true
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

int QueueLength(LinkQueue Q)	 //返回Q的元素个数（队列长度）
{
	int i = 0;
	QNode *q = Q.front->next;
	while (q)
	{
		i++;
		q = q->next;
	}
}

QElemtype GetHead(LinkQueue Q)  //若Q不为空，返回头元素值
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue");
		return;
	}
	else
		return Q.front->next->data;
}

void EnQueue(LinkQueue &Q, QElemtype e)	//元素e插入队尾
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		printf("ERROR\n");
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;	//令原队尾元素指向p
	Q.rear = p;		//将p设为新的队尾
}

/*删除队头元素，一般仅需要更改头结点中的指针。但是如果最后一个元素被删除，则尾指针需要指向头指针*/
QElemtype DeQueue(LinkQueue &Q)	//删除队头元素，用e返回值
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue\n");
		exit(0);
	}
	QueuePtr p = Q.front->next;	//p指向队头元素
	QElemtype e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)	//若删除之后变为空队列
	{
		Q.rear = Q.front;
	}
	free(p);
	return e;
}