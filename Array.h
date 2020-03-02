#pragma once
#include<stdio.h>
#include<stdarg.h> //用于存取变长参数表
#include<stdlib.h>

const int MAX_ARRAY_DIM = 8;	//假定最大维数为8

typedef int Elemtype;

typedef struct {
	Elemtype *base;	//数组元素基址
	int dim;	//数组维数
	int *bounds;	//数组维界基址
	int *constants;	//数组映像函数常量基址	LOC(j1,...jn)=LOC(0,...0)+Σ(i=1,n)ci*ji，其中cn=L,c(i-1)=bi*ci
}Array;

void InitArray(Array &A, int dim, ...)	//...省略的是各维度长度
{
	if (dim<1 || dim>MAX_ARRAY_DIM)	//维数不合法
	{
		printf("ERROR: Dimension invalid\n");
		exit(1);
	}
	else
	{
		A.dim = dim;
		A.bounds = (int*)malloc(dim * sizeof(int));
		if (!A.bounds)
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		//若维数合法，将后续各维长度存入A.bounds
		int elemtotal = 1; //用elemtotal记录A的元素总数
		va_list ap;	//ap是存放变长参数表信息的数组
		va_start(ap, dim);
		for (int i = 0; i < dim; ++i)
		{
			A.bounds[i] = va_arg(ap, int);
			if (A.bounds[i] < 0)
			{
				printf("UnderFlow\n");
				exit(1);
			}
			elemtotal *= A.bounds[i];
		}
		va_end(ap);
		A.base = (Elemtype*)malloc(elemtotal * sizeof(Elemtype));	//根据元素个数分配数组空间
		if (!A.base)
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		//接下来求映像函数的常数ci，并存入A.constants[i-1]，i=1,...,dim
		A.constants = (int*)malloc(dim * sizeof(int));
		if (!A.constants)
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		A.constants[dim - 1] = 1; //L=1，指针的增减以元素的大小作为单位
		for (int i = dim - 2; i >= 0; --i)
		{
			A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
		}
	}
}

void DestroyArray(Array &A)	//摧毁数组A
{
	if (!A.base)
	{
		printf("ERROR\n");
		exit(1);
	}
	free(A.base);
	A.base = NULL;
	if (!A.bounds)
	{
		printf("ERROR\n");
		exit(1);
	}
	free(A.bounds);
	A.bounds = NULL;
	if (!A.constants)
	{
		printf("ERROR\n");
		exit(1);
	}
	free(A.constants);
	A.constants = NULL;
}

int Locate(Array A, va_list ap, int &off)	//若ap所指各下标值均合法，求出该元素再A中相对位置并返回
{
	int off = 0, ind, i;
	for (i = 0; i < A.dim; i++)
	{
		ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i])
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		off += A.constants[i] * ind;
	}
	return off;
}

int Value(Array A, ...)	//...省略n个下标值。如果各个下标不越界，则返回所指元素值
{
	int e, result, off;
	va_list ap;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0)
	{
		return A.base[result];
	}
}