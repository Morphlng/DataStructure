#include<stdio.h>
#include<stdlib.h>

int main()
{
	while (true)
	{
		int i, j;
		int n;
		printf("请输入行数n:\n");
		scanf_s("%d", &n);
		for (i = 0; i < n; i++)	//n行
		{
			for (j = 0; j < n - (i + 1); j++)
			{
				printf(" ");
			}
			for (j = 0; j < 2 * n; j++)	//每行2n个
			{
				if (j < 2 * i + 1)	//*的个数是1、3、5，从0开始计数用2i+1
					printf("*");
				else
					printf("#");
			}
			printf("\n");
		}
		system("pause");
		printf("\n");
	}
	return 0;
}