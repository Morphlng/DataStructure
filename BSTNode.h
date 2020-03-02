#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef int KeyType;

typedef struct node {	//二叉排序树的定义
	KeyType key;	//关键字的值
	struct node *lchild, *rchild;	//左右指针
}BSTNode,*BSTree;

void InsertBST(BSTree &T, KeyType key)	 //若在二叉排序树中不存在关键字为key的元素，则插入该元素
{
	if (T==NULL)	//如果根结点不存在，则插入为根结点（换言之，每次插入的新结点都作为叶子结点）
	{
		T = (BSTree)malloc(sizeof(BSTNode));	   //申请新的结点
		T->key = key;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else
	{
		if (key < T->key)
			InsertBST(T->lchild, key);	 //将s插入左子树
		else
			if (key > T->key)
				InsertBST(T->rchild, key);	 //将s插入右子树
	}
}
//中序遍历一个二叉排序树可以得到一个有序序列，因为他的定义就是左子树比根结点小，右子树比根结点大

void CreateBST_pre(BSTree &T)	//按照扩展的先序遍历建立二叉排序树
{
	int key;
	scanf_s("%d", &key);
	if (key == 0)
	{
		T = NULL;
	}
	else
	{
		if (!(T = (BSTree)malloc(sizeof(BSTNode))))
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		T->key = key;	//为根节点赋值
		CreateBST_pre(T->lchild);	//构造左子树
		CreateBST_pre(T->rchild);	//构造右子树
	}
}

void CreateBST(BSTree &T)	//根据输入数据大小关系建立二叉排序树
{	//如果用这个方法初始化，那么主函数要注明T=NULL
	int key;
	scanf_s("%d", &key);
	while (key != 0)
	{
		InsertBST(T, key);
		scanf_s("%d", &key);
	};
}

BSTree SearchBST(BSTree bst, KeyType key)   //查找关键字key，如果找到，返回指向该元素结点的指针，反之返回空指针
{
	BSTree q;
	q = bst;
	while (q) {
		if (q->key == key)
		{
			printf("%d ", q->key);
			return q;	//查找成功
		}
		if (key < q->key)
		{
			printf("%d ", q->key);
			q = q->lchild;	//在左子树中查找
		}
		else
		{
			printf("%d ", q->key);
			q = q->rchild;	//在右子树中查找
		}
	}
	return NULL;	//查找失败
}

bool SearchBST_bool(BSTree T, KeyType key)   //确认关键字key是否在树T中
{
	if (!T)	//空树或没有找到
	{
		printf("Not Found!\n");
		return false;
	}
	else
		if (T->key == key)
		{
			printf("Find key:%d, Continue\n", T->key);
			return true;
		}
		else
			if (T->key > key)
				SearchBST_bool(T->lchild, key);
			else
				if (T->key < key)
					SearchBST_bool(T->rchild, key);
}

bool Delete(BSTree &T)	//删除二叉排序树中的结点T
{
	BSTree L;
	if (!T->lchild && !T->rchild)	//若T既没有左子树也没有右子树，即其为叶子结点
	{
		T = NULL;
		free(T);
	}
	else
		if (!T->lchild)	//如果只有右子树
			T = T->rchild;	//则让右子树代替当前结点
		else
			if (!T->rchild)	//如果只有左子树
				T = T->lchild;	//则让左子树代替当前结点
			else	//如果既有左子树，又有右子树
			{
				L = T->lchild;	//L指向被删除结点的左子树
				while (L->rchild)	//寻找L的最右孩子
					L = L->rchild;
				L->rchild = T->rchild;  //把T的右子树接到左子树最右孩子的右子树上
				T = T->lchild;	//T的左子树直接作为T父结点的左子树
			}
	return true;
}

bool DeleteBST(BSTree &T, int key)	//删除键值为key的结点
{
	if (!T)
	{
		printf("Empty Tree!\n");
		return false;
	}
	else
		if (key == T->key)
		{
			Delete(T);
			return true;
		}
		else
			if (key < T->key)
				return DeleteBST(T->lchild, key);
			else
				return DeleteBST(T->rchild, key);
}

void PrintBST(BSTree T)	//按中序遍历输出二叉排序树，得到有序顺序
{
	if (!T)
	{
		return;
	}
	PrintBST(T->lchild);
	printf("%d ", T->key);
	PrintBST(T->rchild);
}