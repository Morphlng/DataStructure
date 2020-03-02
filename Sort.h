#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"SqList.h" //对顺序表排序
#include"LNode.h"

void InsertSort(SqList &L)	//直接插入排序
{
	int i, j;
	for (i = 2; i <= L.length; ++i)
	{
		L.elem[0] = L.elem[i];	//哨兵位复制当前值
		for (j = i - 1; L.elem[0] < L.elem[j]; --j)
		{
			L.elem[j + 1] = L.elem[j];	//记录后移
		}
		L.elem[j + 1] = L.elem[0];	//插入到正确位置
	}
}

void InsertSort_Node(LinkList &L)	//单链表的直接插入排序。方向从左到右
{
	LNode *p, *q, *insert;
	p = L->next;	//p指向开始结点
	q = p->next;	//q指向第二个结点
	p->next = NULL;	//将L链表开始结点以后置空
	p = q;	//让p从原L表的第二个结点开始。相当于顺序表中从第二个元素开始循环
	while (p)
	{
		q = p->next;	//q用来指向原链表，防止丢链
		insert = L;	//从表头开始找插入位置
		while (insert->next != NULL && insert->next->data < p->data)
		{
			insert = insert->next;	//找到插入位置
		}
		p->next = insert->next;
		insert->next = p;
		p = q;
	}
}

void BInsertSort(SqList &L)	//对顺序表进行折半插入排序
{
	int i, j, low, high, mid;
	for (i = 2; i <= L.length; i++)
	{
		L.elem[0] = L.elem[i];	//哨兵位复制当前值
		low = 1;
		high = i - 1;
		while (low <= high)	//这里相当于折半查找查询不存在的元素，结束时的low值(high+1)恰好是应该插入的位置
		{
			mid = (low + high) / 2;
			if (L.elem[0] < L.elem[mid])
				high = mid - 1;	//如果L.elem[0]<L.elem[mid]则插入在低半区
			else
				low = mid + 1;	//反之插入高半区
		}
		for (j = i - 1; j >= high + 1; --j)
			L.elem[j + 1] = L.elem[j];	//记录后移
		L.elem[high + 1] = L.elem[0];
	}
}

void TwoPathInsert(SqList &L)	//2路排序
{
	int *d;	//辅助数组d，存储最终排序后结果，并且把d想象成循环的，所以设first和final指针
	int first = 0, final = 0; //first和final分别是d中的最小值和最大值指向，初始为0（枢轴）
	int i, j;

	d = (int*)malloc(L.length * sizeof(int));	//初始化辅助数组
	for (i = 1; i < L.length; i++)
	{
		d[i] = 0;
	}
	d[0] = L.elem[1];
	printf("进入for循环之前:\n");
	printf("d[%d]=%d, L.elem[%d]=%d\n\n", 0, d[0], 1, L.elem[1]);

	for (i = 2; i <= L.length; i++)	//在d中完成排序
	{
		printf("当前指向：%d \n", L.elem[i]);
		if (L.elem[i] >= d[final])	//如果当前值大于等于d中最大值
		{
			d[++final] = L.elem[i];	//final后移并在d中插入值
			printf("执行第一个if语句\n");
			printf("first=%d, final=%d\n", first, final);
			printf("d[%d]=%d，L.elem[%d]=%d\n\n",final, d[final],i,L.elem[i]);
		}
		else
			if (L.elem[i] <= d[first])	//如果当前值小于等于d中最小值
			{
				first = (first - 1 + L.length) % L.length;	//从尾部开始，往前插值(类似循环队列)
				d[first] = L.elem[i];
				printf("执行第二个if语句\n");
				printf("first=%d, final=%d\n", first, final);
				printf("d[%d]=%d，L.elem[%d]=%d\n\n",first, d[first],i,L.elem[i]);
			}
			else
				if (L.elem[i] >= d[0] && L.elem[i] < d[final])	//如果当前值在右侧区间，这里必须是大于等于，因为这样才能保证排序算法是稳定的，否则与第一个元素相等的值会排在其之前，记录的顺序就乱了
				{
					for (j = final++; L.elem[i] < d[j]; j--)	//直接插入排序，注意插入后final位置后移
					{
						d[j+1] = d[j];
					}
					d[j + 1] = L.elem[i];
					printf("执行第三个if语句\n");
					printf("first=%d, final=%d\n", first, final);
					printf("d[%d]=%d，L.elem[%d]=%d\n\n", j+1, d[j+1], i, L.elem[i]);
				}
				else
					if (L.elem[i] > d[first] && L.elem[i] < d[0])	//如果当前值在左侧区间
					{
						for (j = first--; L.elem[i] > d[j] && j<L.length; j++)	//直接插入排序（方向相反），注意插入后first前移
						{
							printf("j=%d\n", j);
							d[j - 1] = d[j];
						}
						d[j-1] = L.elem[i];
						printf("执行第四个if语句\n");
						printf("first=%d, final=%d\n", first, final);
						printf("d[%d]=%d，L.elem[%d]=%d\n\n", j - 1, d[j - 1], i, L.elem[i]);
					}
	}

	printf("排序后d数组：\n");
	printf("first=%d, final=%d\n", first, final);
	j = first;
	for (i = 1,j; i <= L.length; i++,j=(j+1)%L.length)
	{
		printf("d[%d]=%d\n",j, d[j]);
		L.elem[i] = d[j];
	}
}

void ShellSort(SqList &L)	//希尔排序
{
	int i, j, k;
	int gap; //gap是分组步长，这里我们定义开始长度为length/2，每次缩减为一半，但这并不是效率最高的分组
	for (gap = L.length / 2; gap >=1; gap /= 2)
	{
		for (i = 1; i <= gap; i++)	//用gap分组
		{
			for (j = i + gap; j <= L.length; j += gap)	//一次插入排序，用的直接插入排序
			{
				if (L.elem[j] < L.elem[j - gap])
				{
					L.elem[0] = L.elem[j];
					for (k = j - gap; L.elem[0] < L.elem[k] && k>0; k -= gap)	//注意因为每次往前gap，要判断有没有越界(k>0)
					{
						L.elem[k + gap] = L.elem[k];	//“移位”
					}
					L.elem[k + gap] = L.elem[0];
				}
			}
		}
	}
}

void BubbleSort(SqList &L)	//冒泡排序法
{
	int i, j, temp;	//稍微优化一下就是当走完一趟都没有发生交换时提前退出，更深层的优化可以记录上一次排序位置
	for (i = 1; i <= L.length; i++)	//确定排序趟数
	{
		int flag = 0;
		for (j = 1; j <= L.length - i; j++)	//确定比较次数
		{
			if (L.elem[j] > L.elem[j + 1])
			{
				temp = L.elem[j];
				L.elem[j] = L.elem[j + 1];
				L.elem[j + 1] = temp;
				flag = 1;	//交换了则标志位1
			}
		}
		if (flag == 0)	//没有发生交换，退出
			break;
	}
}

int Partition(SqList &L, int low, int high) //一趟快速排序（划分）
//交换顺序表L中子表r[low...high]的记录，枢轴记录到为，并返回其所在位置。此时它之前（后）的记录不大（小）于它
{
	L.elem[0] = L.elem[low];	//用子表的第一个记录作为枢轴记录
	int pivotkey = L.elem[0];	//这里其实是为了保存key值，因为Elemtype可能不止一个值
	while (low < high)	//从表的两端交替的向中间扫描
	{	//当low==high时，该位置即枢轴记录应该被放置的位置
		while (low < high && L.elem[high] >= pivotkey)
			--high;
		L.elem[low] = L.elem[high];	//将比枢轴记录小的记录移到低端
		while (low < high && L.elem[low] <= pivotkey)
			++low;
		L.elem[high] = L.elem[low];	//将比枢轴记录大的记录移到高端
	}
	L.elem[low] = L.elem[0];	//枢轴记录到位
	return low;	//返回枢轴位置
}

void QuickSort(SqList &L,int low,int high)  //快速排序，对顺序表L中子序列r[low..high]作快速排序
{
	int pivotloc;
	if (low < high)	//待排序区间长度大于1，否则函数直接返回
	{
		pivotloc = Partition(L, low, high);	//将r[low..high]一分为二，pivotloc是一趟快速排序结束后的枢轴位置
		QuickSort(L, low, pivotloc - 1);	 //对低子表递归排序
		QuickSort(L, pivotloc + 1, high);	 //对高子表递归排序
	}
}

int SelectMinKey(SqList L, int i)	//找到顺序表L[i..L.length]中最小记录的下标
{
	int min = L.elem[i], m, n = i;
	for (m = i+1; m <= L.length; m++)
	{
		if (L.elem[m] <= min)
		{
			min = L.elem[m];
			n = m;
		}
	}
	return n;
}

void SelectSort(SqList &L)	//选择排序，每次找到第n小的记录并移到位置n。如第一次找到第1小，移到L.elem[1]
{
	int i, j;
	for (i = 1; i < L.length; i++)
	{
		j = SelectMinKey(L, i);	//找到key最小的记录
		if (i != j)
		{
			int temp;
			temp = L.elem[i];
			L.elem[i] = L.elem[j];	//与第j个记录交换位置
			L.elem[j] = temp;
		}
	}
}

//下面是堆排序的部分
void Swap(SqList L, int i, int k)	//交换函数，主要用于堆顶和堆底调换
{
	int temp = L.elem[i];
	L.elem[i] = L.elem[k];
	L.elem[k] = temp;
}


void Max_Heapify(SqList L, int start, int end)	//将顺序表（数组）改造成最大堆
{
	//建立父节点下标和子节点下标
	int dad = start;	

	int son = dad * 2;	//当数组下标从0开始时，应为son=dad*2+1

	while (son <= end)
	{   //若子节点下标在范围内才做比较
		if (son + 1 <= end && L.elem[son] < L.elem[son + 1]) //先比较两个子节点大小，选择最大的
		{
			son++;
		}

		if (L.elem[dad] > L.elem[son]) //如果父节点大于子节点代表调整完毕,直接跳出
		{
			return;
		}
		else
		{   //否则交换父子节点的值再继续左右子节点值得比较
			Swap(L, dad, son);
			printf("dad=%d, son=%d\n", dad, son);
			dad = son;
			son = dad * 2;
		}
	}
}

void Heap_Sort(SqList L)
{
	int i;
	//初始化，i从最后一个父节点开始调整
	for (i = L.length / 2; i >= 1; i--)
	{
		Max_Heapify(L, i, L.length);
	}

	for (i = L.length; i >= 1; i--)
	{
		Swap(L, 1, i);
		Max_Heapify(L, 1, i);
	}
}

//2-路归并排序
void Merge(int* SR, int* TR, int i, int m, int n)
{//将有序的SR[i..m]和SR[m+1..n]归并成有序的TR[i..n]
	int j, k;
	for (j = m + 1, k = i; i <= m && j <= n; k++)
	{//将SR中记录由小到大并入TR，i是用于遍历SR[i..m]中元素的指针，j是用于遍历SR[m+1..n]中元素的指针
		if (SR[i] <= SR[j])
		{
			TR[k] = SR[i];
			i++;
		}
		else
		{
			TR[k] = SR[j];
			j++;
		}
	}
	if (i <= m)	//剩余SR[i..m]复制到TR
		for (k; k <= n; k++)
		{
			TR[k] = SR[i];
			i++;
		}
	if (j <= n)	//剩余SR[j..n]复制到TR
		for (k; k <= n; k++)
		{	
			TR[k] = SR[j];
			j++;
		}
}

void MSort(int* SR,int *TR1, int s, int t)	 //将SR[s..t]归并排序为TR1[s..t]
{
	int* TR2 = (int*)malloc(t * sizeof(int)); //与SR交换存储归并后的结果，可以看到需要的辅助空间不少，所以这种方法一般不用作内部排序
	int m;
	if (s == t)
		TR1[s] = SR[s];	//递归出口
	else
	{
		m = (s + t) / 2;	//将SR[s..t]平分为SR[s..m]和SR[m+1..t]
		MSort(SR, TR2, s, m);	//递归地将SR[s..m]归并为有序TR2[s..m]
		MSort(SR, TR2, m + 1, t);	//递归地将SR[m+1..t]归并为有序
			//TR2[m+1..t]
		Merge(TR2, TR1, s, m, t);	//将TR2[s..m]和TR2[m+1..t]归并到
			//TR1[s..t]
	}
}

void MergeSort(SqList &L)
{	//对顺序表L作归并排序
	MSort(L.elem, L.elem, 1, L.length);	//将待排序列L归并排序后返回到L中
}