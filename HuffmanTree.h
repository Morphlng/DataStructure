#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int weight;	//���Ȩֵ
	int parent, lchild, rchild;	//ָ��˫�׺����Һ��ӵ�ָ��
}HTNode,*HuffmanTree;	//��̬��������շ�����

typedef char **HuffmanCode;	//��̬��������洢�շ�������

void Select(HuffmanTree HT, int size, int &s1, int &s2) //�ҵ�1-size֮��������С�Ľ��s1��s2
{
	int min, secmin;	//��Сֵ�ʹ�Сֵ
	int i,min_loc,secmin_loc;	//��С����Сֵ��Ӧλ��

	for (i = 1; i <= size; i++)
	{
		if (HT[i].parent == 0)
		{
			min_loc = i;	//�����һ��parent��Ϊ0�Ľ������С���
			min = HT[i].weight;
			break;
		}
	}
	for (i = 1; i <= size; i++)	//�ҵ���Сֵ
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
			secmin_loc = i;	//�����һ��parent��Ϊ0�Ľ���Ҳ�����Сֵ�Ľ������С���
			secmin = HT[i].weight;
			break;
		}
	}
	for (i = 1; i <= size; i++)
	{
		if(i!=min_loc)	//��������Сֵָ��ͬһλ��
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
{	//w���n���ַ���Ȩֵ������շ�����HT�������n���ַ��ĺշ�������HC
	int i, m, s1, s2;
	if (n <= 1)
		return;
	HTNode *p;	//ָ��
	m = 2 * n - 1;	//m���ܵĽ����
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));  //0�ŵ�Ԫδʹ��
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)
	{
		*p = { *w,0,0,0 };	//Ҷ�ӽ���ʼ��
	}
	for (i = n + 1; i <= m; i++, p++)
	{
		*p = { 0,0,0,0 };	//��Ҷ�ӽ���ʼ��
	}
	for (i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}	//�շ������������

	//��շ��������׼������
	HC = (HuffmanCode)malloc((n - 1) * sizeof(char*));  //����n���ַ������ͷָ������
	char *cd = (char*)malloc(n * sizeof(char)); //������ǰ����Ĺ����ռ�
	cd[n - 1] = '\0';	//����������λ��ű��룬���ȴ�ű��������

	int start, c, f;
	for (i = 1; i <= n; i++)
	{
		start = n - 1;	//��ʼ��������ʼָ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	 //��Ҷ�ӽ�㵽��������������
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';	//���֧��0
			else
				cd[--start] = '1';	//�ҷ�֧��1
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}