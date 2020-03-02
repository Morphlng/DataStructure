#pragma once		//图的数组表示法
#include<stdio.h>
#include<limits.h>
#define INFINITY INT_MAX	//最大值∞
#define MAX_VNUM 20	//最大顶点个数
typedef enum {DG,DN,UDG,UDN} GraphKind;	//{有向图，有向网，无向图，无向网}
typedef int VRType; //VRType是顶点关系类型，对无权图用1或0表示是否相邻；对带权图，则为权值类型
typedef char InfoType;	//该弧相关信息的指针(弧相关信息一般指权值)
typedef char VertexType;	//结点名字
bool visited[MAX_VNUM]; //标记顶点是否被访问过

typedef struct ArcCell {	//邻接矩阵中的每个结点定义
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VNUM][MAX_VNUM];

typedef struct {
	VertexType vexs[MAX_VNUM]; //一维数组表示顶点向量
	AdjMatrix arcs;	//二维数组表示邻接矩阵
	int vexnum, arcnum;	//图的当前顶点数和弧数
	GraphKind kind;	//图的种类标志
}MGraph;

#include"SqStack.h"
#include"SqQueue.h"

int LocateVex(MGraph G, VertexType v)	//求顶点v在图G中的位置（即下标）
{
	int j = -1, k;
	for (k = 0; k < G.vexnum; k++)
	{
		if (G.vexs[k] == v)
		{
			j = k;
			break;
		}
	}
	return j;
}

void CreateUDN(MGraph &G)	//采用数组表示法构造无向网G
{
	int IncInfo, i, j, k;
	G.kind = UDG;
	printf("请输入所构造无向网的顶点数，弧数以及是否含有弧的其他信息:（IncInfo为0则各弧不含其他信息）\n");
	scanf_s("%d %d %d",&G.vexnum, &G.arcnum, &IncInfo); //IncInfo为0则各弧不含其他信息
	printf("请输入结点信息（名字）:\n");
	getchar();

	for (i = 0; i < G.vexnum; i++)	//构造顶点向量
	{
		printf("vexnum[%d]:",i);
		scanf_s("%c",&G.vexs[i]);	//输入顶点名字，如v1、v2
		printf("\n");
		getchar();
	}

	for (i = 0; i < G.vexnum; i++)	//初始化邻接矩阵
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { INFINITY,NULL };	 //{adj,info}
		}
	}

	for (k = 0; k < G.arcnum; k++)	//构造邻接矩阵
	{
		VertexType v1, v2;
		VRType w;
		printf("请输入第一个依附的顶点:\n");
		scanf_s("%c", &v1);  //输入一条边依附的顶点和权值
		getchar();
		printf("请输入第二个依附的顶点:\n");
		scanf_s("%c", &v2);
		getchar();
		printf("请输入权值:\n");
		scanf_s("%d", &w);
		getchar();
		i = LocateVex(G, v1);	//确定v1和v2在G中的位置
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;	//弧<v1,v2>的权值
		if (IncInfo)	//若弧含有相关信息，则输入
			gets_s(G.arcs[i][j].info,sizeof(G.arcs[i][j].info));
		G.arcs[j][i] = G.arcs[i][j];	//置<v1,v2>的对称弧<v2,v1>
		printf("\n");
	}
}

int FirstAdjVex(MGraph G, int v)	//查找与数组下标为v的顶点之间有边的顶点，返回数组下标
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.arcs[v][i].adj)
			return i;
	}
	return -1;
}

int NextAdjVex(MGraph G, int v, int w)	//查找下标为v的顶点 相对 下标为w的顶点 的下一个顶点
{
	for (int i = w + 1; i < G.vexnum; i++)
	{
		if (G.arcs[v][i].adj)
			return i;
	}
	return -1;
}

bool visit(MGraph G, int v)	//访问G图中下标为v的顶点
{
	if (G.vexs[v])
	{
		printf("%c", G.vexs[v]);
		return true;
	}
	return false;
}

void DFS_recur(MGraph G, int v)	//从第v个顶点出发递归地深度优先遍历图G
{
	int w;
	visited[v] = true;
	visit(G, v);	//访问第v个顶点
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		if (!visited[w])	//对v的尚未访问的邻接顶点w递归调用DFS
			DFS_recur(G, w);
	}
}

void DFSTraverse_recur(MGraph G)	//对图G作深度优先遍历的递归算法
{
	int v;
	for (v = 0; v < G.vexnum; v++)	//访问标志数组初始化
	{
		visited[v] = false;
	}
	for (v = 0; v < G.vexnum; v++)	//对尚未访问的顶点调用DFS
	{
		if (!visited[v])
			DFS_recur(G, v);
	} 
}

void DFSTraverse(MGraph G,int v0)	//对图G作深度优先遍历的非递归算法，如果图中存在环则有元素重复入栈
{
	int v, w;
	SqStack S;
	InitStack(S);
	Push(S, v0);	//从v出发，深度优先搜索图G
	while (!StackEmpty(S))
	{
		v = Pop(S);
		if (!visited[v])
		{
			visit(G, v);
			visited[v] = true;
		}
		w = FirstAdjVex(G, v);
		while (w != -1)
		{
			if (!visited[w])
				Push(S, w);
			w = NextAdjVex(G, v, w);
		}
	}
}

void BFSTraverse(MGraph G)
{
	int v, u, w;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	SqQueue Q;
	InitQueue(Q);	//置空的辅助队列Q
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])	//v尚未访问
		{
			visited[v] = true;
			visit(G,v);
			EnQueue(Q, v);	//v入队列
			while (!QueueEmpty(Q))
			{
				u = DeQueue(Q);	//队头元素出队
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
				{
					if (!visited[w])	//w为u的尚未访问的邻接顶点
					{
						visited[w] = true;
						visit(G,w);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}

struct AssistArray{	//记录从顶点集U到V-U的代价最小的边的辅助数组定义，用于求最小生成树
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VNUM];

int minimum(AssistArray *closedge)	//返回权值最小的边对应的结点下标
{
	int i, min;
	VertexType minvex;
	for (i = 0; i < MAX_VNUM; i++)
	{
		if (closedge[i].lowcost != 0)
		{
			min = closedge[i].lowcost;
			minvex = closedge[i].adjvex;
		}
	}
	for (i = 0; i < MAX_VNUM; i++)
	{
		if ((closedge[i].lowcost < min) && (closedge[i].lowcost != 0))
		{
			min = closedge[i].lowcost;
			minvex = closedge[i].adjvex;
		}
	}
	for (i = 0; i < MAX_VNUM; i++)
	{
		if (closedge[i].lowcost==min)
			break;
	}
	return i;
}

void MiniSpanTree_PRIM(MGraph G, VertexType u)	//普利姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
{
	int i, j, k = LocateVex(G, u);	//求顶点u的位置
	for (j = 0; j < G.vexnum; j++)	//辅助数组初始化
	{
		if (j != k)
			closedge[j] = { u,G.arcs[k][j].adj };	//{adjvex,lowcost}
	}	
	closedge[k].lowcost = 0;	//初始，U={u}
	for (i = 1; i < G.vexnum; i++)	//选择其余G.vexnum-1个顶点
	{
		k = minimum(closedge);	//求出T的下一个顶点，第k顶点
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;	//将k顶点并入U集
		for (j = 0; j < G.vexnum; j++)  //新顶点并入U后重新选择最小边
		{
			if (G.arcs[k][j].adj < closedge[j].lowcost)
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj };
		}
	}
}