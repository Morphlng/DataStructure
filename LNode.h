#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef int Elemtype;

typedef struct LNode {	//单链表定义
	Elemtype data;
	struct LNode *next;
}LNode,*LinkList;

void CreateList_HeadInsert(LinkList &L, int n)	//头插法创建单链表
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;	//建立带一个头结点的链表
	for (int i = n; i > 0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));	//生成新结点
		cin >> (p->data);
		p->next = L->next;
		L->next = p;
	}
}

void CreatList_TailInsert(LinkList &L,int n)	//尾插法创建单链表
{
	L = (LinkList)malloc(sizeof(LNode));          //  为头指针开辟内存空间
	LinkList Node = NULL;           //  定义结点
	LinkList end = NULL;            //  定义尾结点
	L->next = NULL;              //  初始化头结点指向的下一个地址为 NULL
	end = L;                     //  未创建其余结点之前，只有一个头结点
	int count = n;                 //  结点个数
	for (int i = 0; i < count; i++) {
		Node = (LinkList)malloc(sizeof(LNode));          //  为新结点开辟新内存
		Elemtype temp;
		scanf_s("%d",&temp);
		Node->data = temp;                                  //  新结点的数据域赋值
		end->next = Node;
		end = Node;
	}
	end->next = NULL;
}


void ListInsert(LinkList &L, int i, Elemtype e) //在链表第i个位置插入e
{
	LinkList p = L;	//p指向头结点
	int j = 0;
	while (p && j < i - 1)	//找到第i-1个结点
	{
		p = p->next;
		++j;		
	}
	if (!p || j > i - 1)
	{
		cerr << "ERROR";
		exit(1);
	}
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
}

Elemtype ListDelete(LinkList &L, int i) //删除第i个元素，返回值e
{
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1) //找到第i个结点
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
	{
		cerr << "ERROR";
		exit(1);
	}
	LinkList q = p->next;	//删除并释放
	p->next = q->next;
	Elemtype e = q->data;
	free(q);
	return e;
}

Elemtype GetElem(LinkList L, int i)	//得到单链表中第i个元素
{
	LinkList p = L->next;	//p指向开始结点
	int j = 1;
	while (p && j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
	{
		//cerr << "ERROR";
		return -1;
	}
	return p->data;
}

void ReverseList(LinkList &L)	//不占用额外空间将链表倒置
{
	LinkList p = L->next->next,q;	//p指向开始元素之后的元素
	L->next->next = NULL;	//将原链表一分为二，之后用头插法
	while (p)
	{
		q = p;			//每次从p中取结点，用q来记录其地址
		p = p->next;
		q->next = L->next;	//把q插入到L头结点之后
		L->next = q;
	}
}

void CopyList(LinkList &La, LinkList &Lb)	//将La复制到Lb
{
	Lb = (LinkList)malloc(sizeof(LNode)); //为Lb开辟空间
	Lb->next = NULL;	//设Lb为空链表
	LinkList p = La->next; //p为指向La的k开始结点
	int i = 1;
	while (p)
	{
		ListInsert(Lb, i, p->data);
		i++;
		p = p->next;
	}
}

void PrintLNode(LinkList L)
{
	LNode *p;
	p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
