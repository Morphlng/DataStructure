#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef char TElemtype;
typedef enum PointerTag{Link,Thread}; //如LTag为0，则lchild指向左孩子/RTag为0，rchild指向右孩子。如果LTag为1，则lchild指向前驱结点/Rtag为1，rchild指向后继结点
typedef struct BiThrNode {
	TElemtype data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;	//左右标志
}BiThrNode, *BiThrTree;

BiThrTree pre = (BiThrTree)malloc(sizeof(BiThrNode));	//pre用来指向p(当前结点)的前驱

void CreateBiThrTree(BiThrTree &T) //按先序次序输入二叉树中结点的值，构造二叉树
{
	char ch;
	scanf_s("%c", &ch,sizeof(ch));
	if (ch == '.')T = NULL;
	else
	{
		if (!(T = (BiThrNode*)malloc(sizeof(BiThrNode))))
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		T->data = ch;	//为根节点赋值
		CreateBiThrTree(T->lchild);	//构造左子树
		CreateBiThrTree(T->rchild);	//构造右子树
		T->LTag = Link;	//先赋予默认值，按某种顺序线索化后才是真正赋值
		T->RTag = Link;
	}
}

void InThreading(BiThrTree &p)
{
	if (p)
	{
		InThreading(p->lchild);	//左子树线索化
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;	//保持pre指向p的前驱
		InThreading(p->rchild);	//右子树线索化
	}
}

void InOrderThreading(BiThrTree &Thrt, BiThrTree &T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))	//Thrt是头结点
	{
		printf("OVERFLOW\n");
		exit(0);
	}
	Thrt->LTag = Link;	//建立头结点
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;	//右指针回指
	if (!T)	//如果是空树，则左指针回指
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;
		pre = Thrt;	//pre指向前驱结点
		InThreading(T);	//中序遍历线索化
		pre->rchild = Thrt;	//最后一个结点线索化
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
}

//如果BiTree和BiThrNode同时include则需要注释掉，否则重复定义
bool visit(TElemtype e)
{
	if (e)
	{
		printf("%c ", e);
		return true;
	}
	else
		return false;
}


void InOrderTraverse(BiThrTree T,BiThrTree Thrt)	//中序遍历线索二叉树,Thrt为头结点，指向T
{
	BiThrTree p = (BiThrTree)malloc(sizeof(BiThrNode));
	p = Thrt->lchild;	//p指向根结点
	while (p != Thrt)	//空树或者遍历完成时p==T
	{
		while (p->LTag == Link)	//先将向左走到头
			p = p->lchild;
		if (!visit(p->data))	//访问左子树为空的结点
		{
			printf("ERROR\n");
			exit(0);
		}
		while ((p->RTag == Thread) && (p->rchild != Thrt))	//如果rchild指向直接后继结点，并且不是整个遍历的最后一个结点，则访问它的直接后继结点
		{
			p = p->rchild;	//访问后继节点
			visit(p->data);
		}
		p = p->rchild;	//如果有右孩子，则走右孩子
	}
}
