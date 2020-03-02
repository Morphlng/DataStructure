#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef char TElemtype;

typedef struct BiTNode {	//二叉树的链式表示
	TElemtype data;
	struct BiTNode *lchild, *rchild; //左右孩子指针
}BiTNode,*BiTree;

#include"SqStack.h"				//这里头文件的顺序是有讲究的，如果在定义二叉树之前引入，相当于
#include"SqQueue.h"				//在还没有定义BiTree的时候就将SElemtype定义为BiTree，会报错

void CreateBiTree(BiTree &T) //按先序次序输入二叉树中结点的值，构造二叉树
{
	char ch;
	scanf_s("%c", &ch,sizeof(ch));
	if (ch == '.')T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		T->data = ch;	//为根节点赋值
		CreateBiTree(T->lchild);	//构造左子树
		CreateBiTree(T->rchild);	//构造右子树
	}
}

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

void PreOrderTraverse_recur(BiTree T)	//先序遍历二叉树的递归算法
{
	if (T != NULL)	//如果根节点不为空
	{
		visit(T->data);	//访问根节点
		PreOrderTraverse_recur(T->lchild);	 //先序遍历左子树
		PreOrderTraverse_recur(T->rchild);	 //先序遍历右子树
	}
}

void PreOrderTraverse(BiTree T)	//先序遍历二叉树的非递归算法，空指针不进栈
{
	SqStack S;
	InitStack(S);
	BiTree p = T;
	while (p || !StackEmpty(S))	//这里兼具判断根结点为空和循环继续条件
	{
		if (p)	//这里可以确保空指针不进栈
		{
			if (!visit(p->data))	//访问根结点，左子树进栈
				exit(1);
			Push(S, p);
			p = p->lchild;
		}
		else
		{	//如果不再有左子树，则压右子树进栈
			p = Pop(S);
			p = p->rchild;
		}
	}
}

void InOrderTraverse(BiTree T)	//中序遍历二叉树的非递归算法
{
	SqStack S;	
	InitStack(S);
	Push(S, T);	//将根指针进栈
	BiTree p;
	while (!StackEmpty(S))
	{
		while ((p = GetTop(S)) && p)
		{
			Push(S, p->lchild);	//向左走到尽头，最后一个结点是叶子结点，左孩子为空，所以马上退栈
		}
		p=Pop(S);	//空指针退栈
		if (!StackEmpty(S))	//访问结点，向右一步
		{
			p = Pop(S);
			if (!visit(p->data))
			{
				printf("Empty Node!\n");
				exit(1);
			}
			Push(S, p->rchild);
		}
	}
	DestroyStack(S);
}

void PostOrderTraverse(BiTree T) {	//后序遍历二叉树的非递归算法
	SqStack S;
	InitStack(S);
	BiTNode *pre = (BiTNode*)malloc(sizeof(BiTNode));	//建立辅助指针指向最近访问过结点，从而判断是左孩子还是右孩子
	pre = NULL;		//初始化前一个结点为空
	BiTree p = T;
	while (p||!StackEmpty(S))
	{
		while (p)
		{
			Push(S, p);
			p = p->lchild;
		}
		p = GetTop(S);
		if (p->rchild == NULL || pre == p->rchild)	//如果根结点没有右孩子或者访问的前一个结点为根结点右孩子，则访问根结点（这里把每一个结点都看作根结点）
		{
			if (!visit(p->data))
			{
				printf("Empty Node!\n");
				exit(1);
			}
			pre = Pop(S);
			p = NULL;	//防止重新进入p的左子树
		}
		else
			p = p->rchild;	//反之则应该先访问它的右孩子
	}

}//PostOrderTraverse

void PostOrderTraverse_recur(BiTree T)	//后序遍历二叉树的递归算法
{
	if (T != NULL)
	{
		PostOrderTraverse_recur(T->lchild);	//后序遍历左子树
		PostOrderTraverse_recur(T->rchild);	//后序遍历右子树
		visit(T->data);	//访问根结点
	}
}

int LeafCount = 0;	//叶子结点数
int leaf1(BiTree T)	//统计叶子结点数目方法一，依靠后序遍历每次访问到根节点+1
{
	if (T != NULL)
	{
		leaf1(T->lchild);	//后序遍历的方法
		leaf1(T->rchild);
		if (T->lchild == NULL && T->rchild == NULL) //如果没有孩子结点，则找到了叶子结点
			LeafCount++;
	}
	return LeafCount;
}

int leaf2(BiTree T)	//统计叶子结点数法2，递归叠加法
{
	int count;
	if (T == NULL)	//如果为空树，则返回0
		count = 0;
	else
		if ((T->lchild == NULL) && (T->rchild == NULL)) //如果只有一个结点，返回1
			count = 1;
		else
			//否则的话求左右子树叶子结点之后
			count = leaf2(T->lchild) + leaf2(T->rchild);
	return count;
}

int PostTreeDepth(BiTree bt)	//后序遍历求二叉树的高度（深度）递归算法
{
	int hl, hr, max;
	if (bt != NULL)
	{
		hl = PostTreeDepth(bt->lchild); //求左子树高度
		hr = PostTreeDepth(bt->rchild); //求右子树高度
		max = hl > hr ? hl : hr;	   //得到左右子树高度较大者
		return (max + 1);	//返回树的高度
	}
	else
		return 0;	//空树为0
}

int Max(int a, int b)
{
	return a > b ? a : b;
}

int TreeDepth(BiTree T)	//求树的深度
{
	if (!T)		//叶子结点的左右孩子是不存在的，所以应当返回-1
	{
		return 0;
	}
	return 1 + Max(TreeDepth(T->lchild), TreeDepth(T->rchild));
}


void LayerOrder(BiTree T)	//层序遍历二叉树
{
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q, T);	//需要用的时候，把Queue中的数据类型改正
	while (!QueueEmpty(Q))
	{
		BiTree p;
		p=DeQueue(Q);
		if (visit(p->data))
		{
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
		}

	}
	DestoryQueue(Q);
}

int LevelWidth(BiTree T, int level)		//求指定level的宽度
{
	if (!T)
		return 0;
	else
	{
		if (level == 1)return 1;
		level = LevelWidth(T->lchild, level - 1) + LevelWidth(T->rchild, level - 1);
	}
	return level;
}

int Width(BiTree T)	//求树的最大宽度
{
	int width, i;
	int w[20];
	for (i = 0; i < 20; i++)
		w[i] = 0;
	if (!T)width = 0;	//如果是空树，返回0
	else
	{
		for (i = 0; i <= PostTreeDepth(T); i++)	//否则求出每一层的宽度
			w[i] = LevelWidth(T, i + 1);
	}
	i = 0;
	while (w[i])	//求得最大宽度
	{
		if (w[i] > width)width = w[i];
		i++;
	}
	return width;
}
