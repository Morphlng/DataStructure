#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef int KeyType;
typedef struct {
	KeyType key;
}Elemtype;

typedef struct {	//顺序表示的静态查找表（集合）
	Elemtype *elem;	//数据元素存储空间基地址，建表时按实际长度分配，0号单元留空
	int length;	//表长度
}SSTable;

void init_SSTable(SSTable &ST)	//初始化顺序表
{
	int length, i;
	printf("请输入要建立的表长：\n");
	scanf_s("%d", &length);
	ST.elem = (Elemtype*)malloc(length+1 * sizeof(Elemtype));
	printf("请输入表中数据：\n");
	for (i = 1; i <= length ; i++)
	{
		scanf_s("%d", &ST.elem[i].key);
	}
	ST.length = length;
}

int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;	//哨兵，省略对越界下标的检查
	for (i = ST.length; ST.elem[i].key != key; --i);	 //从后往前找
	return i;	//找不到返回0
}

void sortTable(SSTable &ST)	//将顺序表排序
{
	int i, j;
	for (i = 1; i <= ST.length; i++)	  //冒泡法排序
	{
		for (j = 1; j <= ST.length - i; j++)
		{
			if (ST.elem[j].key > ST.elem[j + 1].key)
			{
				Elemtype temp = ST.elem[j];
				ST.elem[j] = ST.elem[j + 1];
				ST.elem[j + 1] = temp;
			}
		}
	}
}

int Search_Bin(SSTable ST, KeyType key) //对有序表进行折半查找的非递归算法
{
	sortTable(ST); //将顺序表ST有序化
	int low = 1, high = ST.length, mid;	//区间的左右标志位
	while (low <= high)	//若子表存在
	{
		mid = (low + high) >> 1;	//计算中间位置
		if (key == ST.elem[mid].key)
			return mid;	//找到待查找元素
		else
			if (key < ST.elem[mid].key)
				high = mid - 1;	//没有找到且当前mid指向小于所查找项，则在前半区间查找
			else
				low = mid + 1;	//反之在后半区间查找
	}
	return 0;	//没有查到
}

int Search_Bin_recur(SSTable ST, KeyType key,int low,int high) //对有序表进行折半查找的递归算法
{
	sortTable(ST); //将顺序表ST有序化
	int i = low;
	int j = high;
	int mid = (low + high) >> 1;
	if (i > j)
		return 0;	//如果不再有子区间，说明没有找到
	if (key == ST.elem[mid].key)
		return mid;	//找到待找项
	else
		if (key > ST.elem[mid].key)
			return (Search_Bin_recur(ST, key, mid + 1, j)); //对右区间折半查找
		else
			return (Search_Bin_recur(ST, key, i, mid - 1)); //对左区间折半查找
	return 0;	//没有找到
}

void printTable(SSTable ST)
{
	int i;
	for (i = 1; i <= ST.length; i++)
	{
		printf("%d ", ST.elem[i].key);
	}
	printf("\n");
}