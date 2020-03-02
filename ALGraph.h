#pragma once	//图的链式表示法
#include<stdio.h>
#include<stdlib.h>
#define MAX_VNUM 20	//最多顶点个数
bool visited[MAX_VNUM]; //标记顶点是否被访问过
int indegree[MAX_VNUM]; //拓扑排序时用于存放各顶点的入度
typedef int InfoType;	//该弧相关信息的指针
typedef char VertexType;
typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef struct ArcNode {	//链表中的结点
	int adjvex;	//该弧指向的顶点的位置
	struct ArcNode *nextarc;	//指向下一条弧的指针
	InfoType info;	//与该弧相关的信息，例如对于网而言，此处可以存储弧上的权值
};
typedef struct VNode {	//表头结点
	VertexType data;	//顶点信息或顶点的名
	ArcNode *firstarc;	//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VNUM];
typedef struct {	//图的邻接表表示
	AdjList vertices;	//一维数组存放表头结点
	int vexnum, arcnum;	//图的当前顶点数和弧数
	GraphKind kind;	//图的种类标志
}ALGraph;

#include"SqQueue.h"
#include"SqStack.h"

int LocateVex(ALGraph G, VertexType v) 
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data == v)
			return i;
	return -1;
}

void CreateUDN(ALGraph &G) 
{
	//采用邻接表表示法，创建无向网G
	int i, k;
	G.kind = UDN;
	printf("请输入总顶点数，总边数。中间用空格隔开：\n");	
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("\n");
	printf("请根据提示输入点的名称，如A\n");
	for (i = 0; i < G.vexnum; i++) 
	{	//输入各点，构建表头结点
		printf("请输入第%d个顶点的名称:", (i + 1));
		scanf_s("%c",&G.vertices[i].data);
		G.vertices[i].firstarc = NULL;    //初始化表头结点的指针域为NULL
		getchar();
	}

	printf("\n");
	printf("请输入一条边依附的顶点，如:A B\n");
	for (k = 0; k < G.arcnum; k++)
	{
		VertexType v1, v2;
		int i, j, w;
		printf("请输入第%d条边依附的顶点:", (k + 1));
		scanf_s("%c", &v1);		//输入一条边依附的两个顶点
		getchar();
		scanf_s("%c", &v2);
		getchar();
		printf("\n");
		i = LocateVex(G, v1);	//确定v1和v2在G中的位置
		j = LocateVex(G, v2);	//即顶点在G.vertices(邻接表)中的序号
		printf("请输入该边的权值:");
		scanf_s("%d", &w);
		getchar();
		printf("\n");
		ArcNode *p1 =(ArcNode*)malloc(sizeof(ArcNode));	 //生成一个新的边结点*p1
		p1->adjvex = j;		//邻接点序号为j
		p1->nextarc = G.vertices[i].firstarc;	
		p1->info = w;
		G.vertices[i].firstarc = p1;	//将新节点*p1插入vi的边表头部

		ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode)); //生成另一个对称的新的边结点*p2
		p2->adjvex = i;					//邻接点序号为i
		p2->nextarc = G.vertices[j].firstarc;
		p2->info = w;
		G.vertices[j].firstarc = p2;	//将新结点*p2插入顶点vj的边表头部
	}
}

void CreateUDG(ALGraph &G)
{
	//采用邻接表表示法，创建无向图G
	int i, k;
	G.kind = UDG;
	printf("请输入总顶点数，总边数。中间用空格隔开：\n");
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("\n");
	printf("请根据提示输入点的名称，如A\n");
	for (i = 0; i < G.vexnum; i++)
	{	//输入各点，构建表头结点
		printf("请输入第%d个顶点的名称:", (i + 1));
		scanf_s("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;    //初始化表头结点的指针域为NULL
		getchar();
	}

	printf("\n");
	printf("请输入一条边依附的顶点，如:A B\n");
	for (k = 0; k < G.arcnum; k++)
	{
		VertexType v1, v2;
		int i, j, w;
		printf("请输入第%d条边依附的顶点:", (k + 1));
		scanf_s("%c", &v1);		//输入一条边依附的两个顶点
		getchar();
		scanf_s("%c", &v2);
		getchar();
		printf("\n");
		i = LocateVex(G, v1);	//确定v1和v2在G中的位置
		j = LocateVex(G, v2);	//即顶点在G.vertices(邻接表)中的序号
		printf("\n");
		ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));	 //生成一个新的边结点*p1
		p1->adjvex = j;		//邻接点序号为j
		p1->nextarc = G.vertices[i].firstarc;
		(p1->info) = NULL;
		G.vertices[i].firstarc = p1;	//将新节点*p1插入vi的边表头部

		ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode)); //生成另一个对称的新的边结点*p2
		p2->adjvex = i;					//邻接点序号为i
		p2->nextarc = G.vertices[j].firstarc;
		(p2->info) = NULL;
		G.vertices[j].firstarc = p2;	//将新结点*p2插入顶点vj的边表头部
	}
}

void CreateDG(ALGraph &G) {	//采用邻接表法，创建有向图
	G.kind = DG;
	int i, j, k;
	char v1, v2;
	ArcNode *p;
	printf("请输入总顶点数，总边数。中间用空格隔开：\n");
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请根据提示输入点的名称，如A\n");
	for (i = 0; i < G.vexnum; i++)
	{	//输入各点，构建表头结点
		printf("请输入第%d个顶点的名称:", (i + 1));
		scanf_s("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;    //初始化表头结点的指针域为NULL
		getchar();
	}
	printf("\n");
	printf("请输入图的边的信息：\n");
	for (k = 0; k < G.arcnum; k++)
	{
		printf("请输入第%d条边的弧尾:", (k + 1));
		scanf_s("%c", &v1);		//输入一条边依附的两个顶点
		getchar();
		printf("请输入第%d条边的弧头:", (k + 1));
		scanf_s("%c", &v2);
		getchar();
		printf("\n");
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i >= 0 && j >= 0) {
			p = (ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex = j;
			p->nextarc = G.vertices[i].firstarc;
			G.vertices[i].firstarc = p;
		}
	}
}

bool visit(ALGraph G, int v)	//访问G图中下标为v的顶点
{
	if (G.vertices[v].data)
	{
		printf("%c", G.vertices[v].data);
		return true;
	}
	return false;
}

void DFS_recur(ALGraph G, int v)	//深度优先遍历图的递归算法
{
	visit(G, v);	//访问顶点v0
	visited[v] = true;
	ArcNode *p = G.vertices[v].firstarc;
	while (p != NULL)	//如果存在邻接点
	{
		if (!visited[p->adjvex])	//递归访问邻接点
			DFS_recur(G, p->adjvex);
		p = p->nextarc;
	}
}

void DFSTraverse_recur(ALGraph G,int i)
{
	int v;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	if (!visited[i])
		DFS_recur(G, i);
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
			DFS_recur(G, v);
	}
}

void BFSTraverse(ALGraph G,int k)	//广度优先遍历算法
{
	int v, u;
	ArcNode *w;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;	//标志数组初始化
	}
	SqQueue Q;
	InitQueue(Q);	//初始化辅助队列Q
	for (v = k; v < G.vexnum; v++)
	{
		if (!visited[v])	//v尚未访问
		{
			visit(G,v);
			visited[v] = true;
			EnQueue(Q, v);	//v入队
			while (!QueueEmpty(Q))
			{
				u = DeQueue(Q);	//队头元素出队并置为u
				for (w = G.vertices[u].firstarc; w != NULL; w = w->nextarc) //w为u的尚未访问过的邻接结点
				{
					if (!visited[w->adjvex])
					{
						visit(G,w->adjvex);
						visited[w->adjvex] = true;
						EnQueue(Q, w->adjvex);
					}
				}
			}
		}
	}
	for (v = 0; v < k; v++)
	{
		if (!visited[v])	//v尚未访问
		{
			visit(G, v);
			visited[v] = true;
			EnQueue(Q, v);	//v入队
			while (!QueueEmpty(Q))
			{
				u = DeQueue(Q);	//队头元素出队并置为u
				for (w = G.vertices[u].firstarc; w != NULL; w = w->nextarc) //w为u的尚未访问过的邻接结点
				{
					if (!visited[w->adjvex])
					{
						visit(G, w->adjvex);
						visited[w->adjvex] = true;
						EnQueue(Q, w->adjvex);
					}
				}
			}
		}
	}
}

void FindInDegree(ALGraph G, int indegree[MAX_VNUM])	//求图G中各顶点的入度并存入数组indegree中
{
	int i;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++)	//初始化indegree数组
		indegree[i] = 0;
	for (i = 0; i < G.vexnum; i++)	//遍历邻接表
	{
		p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			indegree[p->adjvex]++;	//对图中位置为p->adjvex的顶点的入度加1
			p = p->nextarc;
		}
	}
}

void TopologicalSort(ALGraph G)	//有向图采用邻接表存储结构，若G无回路则输出G的顶点的一个拓扑序列
{
	FindInDegree(G, indegree);
	SqStack S;
	InitStack(S);	//初始化辅助栈
	ArcNode *p;
	int i, k, count = 0;	//count为对输出顶点的计数
	for (i = 0; i < G.vexnum; i++)
	{
		if (indegree[i] == 0)
			Push(S, i);	//将入度为0的顶点入栈
	}
	while (!StackEmpty(S))
	{
		i = Pop(S);
		printf("%c", G.vertices[i].data);	//输出i号顶点并计数
		count++;
		p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			k = p->adjvex;
			indegree[k]--;
			if (indegree[k] == 0)
				Push(S, k);
			p = p->nextarc;
		}
	}
	if (count < G.vexnum)
	{
		printf("图中存在回路，无法输出拓扑序列\n");
	}
}