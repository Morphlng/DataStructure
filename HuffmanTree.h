#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int weight;	//结点权值
	int parent, lchild, rchild;	//指向双亲和左右孩子的指针
}HTNode,*HuffmanTree;	//动态分配数组赫夫曼树

typedef char **HuffmanCode;	//动态分配数组存储赫夫曼编码

void Select(HuffmanTree HT, int size, int &s1, int &s2) //找到1-size之间两个最小的结点s1，s2
{
	int min, secmin;	//最小值和次小值
	int i,min_loc,secmin_loc;	//最小及次小值对应位置

	for (i = 1; i <= size; i++)
	{
		if (HT[i].parent == 0)
		{
			min_loc = i;	//假设第一个parent不为0的结点是最小结点
			min = HT[i].weight;
			break;
		}
	}
	for (i = 1; i <= size; i++)	//找到最小值
	{
		if ((HT[i].parent==0) && (HT[i].weight < min))
		{
			min = HT[i].weight;
			min_loc = i;
		}
	}

	for (i = 1; i <= size; i++)
	{
		if (HT[i].parent == 0 && i!=min_loc)
		{
			secmin_loc = i;	//假设第一个parent不为0的结点且不是最小值的结点是最小结点
			secmin = HT[i].weight;
			break;
		}
	}
	for (i = 1; i <= size; i++)
	{
		if(i!=min_loc)	//不能与最小值指向同一位置
			if ((HT[i].parent == 0) && (HT[i].weight < secmin))
			{
				secmin = HT[i].weight;
				secmin_loc = i;
			}
	}

	s1 = min_loc;
	s2 = secmin_loc;
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{	//w存放n个字符的权值，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
	int i, m, s1, s2;
	if (n <= 1)
		return;
	HTNode *p;	//指针
	m = 2 * n - 1;	//m是总的结点数
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));  //0号单元未使用
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)
	{
		*p = { *w,0,0,0 };	//叶子结点初始化
	}
	for (i = n + 1; i <= m; i++, p++)
	{
		*p = { 0,0,0,0 };	//非叶子结点初始化
	}
	for (i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}	//赫夫曼树建立完毕

	//求赫夫曼编码的准备工作
	HC = (HuffmanCode)malloc((n - 1) * sizeof(char*));  //分配n个字符编码的头指针向量
	char *cd = (char*)malloc(n * sizeof(char)); //分配求当前编码的工作空间
	cd[n - 1] = '\0';	//从右向左逐位存放编码，首先存放编码结束符

	int start, c, f;
	for (i = 1; i <= n; i++)
	{
		start = n - 1;	//初始化编码起始指针
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	 //从叶子结点到根结点逆向求编码
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';	//左分支标0
			else
				cd[--start] = '1';	//右分支标1
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}