#include<stdio.h>
#include<stdlib.h>

int main()
{
	while (true)
	{
		int i, j;
		int n;
		printf("����������n:\n");
		scanf_s("%d", &n);
		for (i = 0; i < n; i++)	//n��
		{
			for (j = 0; j < n - (i + 1); j++)
			{
				printf(" ");
			}
			for (j = 0; j < 2 * n; j++)	//ÿ��2n��
			{
				if (j < 2 * i + 1)	//*�ĸ�����1��3��5����0��ʼ������2i+1
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