#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;

const int LIST_INIT_SIZE = 100;
const int LISINCREMENT = 10;
typedef int Elemtype;

typedef struct{		//顺序表定义
	Elemtype *elem;	//基地址
	int length;	//长度
	int listsize;	//容量
}SqList;

void InitList(SqList &L)	//初始化顺序表，开辟空间
{
	L.elem = (Elemtype*)malloc(LIST_INIT_SIZE * sizeof(Elemtype));
	if (!L.elem)
	{
		cerr << "OVERFLOW";
		exit(1);
	}
	L.length= 0;
	L.listsize = LIST_INIT_SIZE;
}
void DestroyList(SqList &L)	//摧毁顺序表
{
	if (L.elem)
	{
		cerr << "ERROR";
		exit(1);
	}
	free(L.elem);
	L.length = 0;
	L.listsize = 0;
}
void ListInsert(SqList &L, int i, Elemtype e)	//向顺序表第i个位置插入e
{
	if (i<1 || i>L.length + 1)	//判断插入位置是否有效, 注意从下标1开始保存
	{
		cerr << "ERROR";
		exit(1);
	}
	if (L.length >= L.listsize)	//判断顺序表是否已满
	{
		Elemtype *newbase = (Elemtype*)realloc(L.elem, (L.listsize + LISINCREMENT) * sizeof(Elemtype));
		if (!newbase)
		{
			cerr << "ERROR";
			exit(1);
		}
		L.elem = newbase;
		L.listsize += LISINCREMENT;
	}
	Elemtype *q = &(L.elem[i]);	//q指向插入位置
	for (Elemtype *p = &(L.elem[L.length - 1]); p >= q; --p)	//移位操作
	{
		*(p + 1) = *p;
	}
	*q = e;
	++L.length;
}
Elemtype ListDelete(SqList &L, int i)	//删除第i个元素，并返回值
{
	if ((i < 1) || (i > L.length))
	{
		cerr << "ERROR";
		exit(1);
	}
	Elemtype *p = &(L.elem[i]);	//删除元素位置
	Elemtype e = *p;
	Elemtype *q = L.elem + L.length - 1; //表尾位置
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;
	}
	--L.length;
	return e;
}
Elemtype GetElem(SqList &L, int i)	//返回顺序表第i个元素
{
	return L.elem[i];
}
bool compare(Elemtype a, Elemtype b)   //判断元素是否相等，若相等则找到相同元素，返回false
{
	if (a == b)
		return false;
	else
		return true;
}
Elemtype LocateElem(SqList &L, Elemtype e)	//在线性表中查找第一个与e相等的元素的位置
{
	int i = 1;
	Elemtype *p = L.elem;
	while (i <= L.length && compare(*p++, e))
		++i;
	if (i <= L.length)
		return i;
	else
		return 0;
}
SqList MergeList(SqList La, SqList Lb)	//将两个顺序表按元素从小到大合并
{
	SqList Lc;
	Elemtype* pa,*pb;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	Elemtype *pc;
	pc = Lc.elem = (Elemtype*)malloc(Lc.listsize * sizeof(Elemtype));
	if (!Lc.elem)
	{
		cerr << "ERROR";
		exit(1);
	}
	Elemtype *pa_last = La.elem + La.length - 1;
	Elemtype *pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
		{
			*pc++ = *pa++;
		}
		else
		{
			*pc++ = *pb++;
		}
	}
	while (pa <= pa_last)
	{
		*pc++ = *pa++;
	}
	while (pb <= pb_last)
	{
		*pc++ = *pb++;
	}
	return Lc;
}

SqList CombineList(SqList La, SqList Lb) //将Lb中元素插入到La尾部，保证不重复
{
	SqList Lc;
	Lc.listsize = La.length + Lb.length;
	Elemtype* pc = Lc.elem = (Elemtype*)malloc(Lc.listsize * sizeof(Elemtype));
	Lc.length = 0;
	Elemtype *pa = La.elem;
	Elemtype *pb = Lb.elem;
	Elemtype *pa_last = La.elem + La.length - 1;
	Elemtype *pb_last = Lb.elem + Lb.length - 1;
	int i = 0;
	for (i=1; pa < pa_last; pa++,i++)
	{
		ListInsert(Lc, i, *pa);		//将La中元素插入到Lc
	}
	for (pb; pb < pb_last; pb++)
	{
		if (!LocateElem(La, *pb))
		{
			ListInsert(Lc,i++,*pb);
		}
	}
	return Lc;
}

void PrintList(SqList L)
{
	int i;
	for (i = 1; i <= L.length; i++)
	{
		printf("%d ", GetElem(L, i));
	}
	printf("\n");
}