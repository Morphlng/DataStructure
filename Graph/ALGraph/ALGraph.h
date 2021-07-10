/*
 * @Description: 
 * @Author: Morphling
 * @Date: 2021-04-02 20:25:58
 * @Gitee: https://gitee.com/Morphlng
 * @LastEditors: Niezl
 * @LastEditTime: 2021-04-08 10:29:32
 */
#pragma once
#ifndef _ALGraph_H_
#define _ALGraph_H_

#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <unordered_map>
#include <queue>

using std::cout;
using std::endl;
using std::pair;
using std::queue;
using std::set;
using std::stack;
using std::string;
using std::unordered_map;
using std::vector;

// 链表结点
template <typename DataType>
struct ArcNode
{
public:
    ArcNode(int vex, DataType val = DataType(), ArcNode<DataType> *next = NULL) : adjvex(vex), value(val), nextarc(next) {}

    int adjvex;                 // 指向的顶点
    DataType value;             // 边权值
    ArcNode<DataType> *nextarc; // 下一个邻接点
};

// 表头结点
template <typename IndexType, typename DataType>
struct VNode
{
public:
    VNode(IndexType n = IndexType(), ArcNode<DataType> *arc = NULL) : name(n), firstarc(arc) {}

    IndexType name;              // 顶点名
    ArcNode<DataType> *firstarc; // 第一条邻接边
};

template <typename IndexType, typename DataType>
class ALGraph
{
public:
    ALGraph(bool direct = false) { directed = direct; }
    void AddNode(IndexType);
    void Insert(IndexType, DataType, IndexType);
    void DFS(IndexType, bool * = NULL);

    // 输出从结点Vi到Vj的所有简单路径
    void FindRoute(IndexType i, IndexType j, vector<IndexType> path = {}, bool * = NULL);

    void print();
    ~ALGraph();

private:
    vector<VNode<IndexType, DataType>> vertices; // 表头结点集
    bool directed;                               // 默认为无向图，true为有向图
    unordered_map<IndexType, int> dex2name;
    unordered_map<int, IndexType> name2dex;
};

template <typename IndexType, typename DataType>
ALGraph<IndexType, DataType>::~ALGraph()
{
    for (VNode<IndexType, DataType> node : vertices)
    {
        if (node.firstarc)
        {
            ArcNode<DataType> *p = node.firstarc;
            while (p)
            {
                ArcNode<DataType> *tmp = p->nextarc;
                delete p;
                p = tmp;
            }
            node.firstarc = NULL;
        }
    }
    vertices.clear();
}

template <typename IndexType, typename DataType>
void ALGraph<IndexType, DataType>::AddNode(IndexType index)
{
    if (name2dex[index])
        return;

    vertices.push_back(VNode<IndexType, DataType>(index));
    name2dex[index] = dex2name.size() + 1;
    dex2name[dex2name.size() + 1] = index;
}

// 添加一条s-d的边，路径权值为val
template <typename IndexType, typename DataType>
void ALGraph<IndexType, DataType>::Insert(IndexType s, DataType val, IndexType d)
{
    int sdex = name2dex[s], ddex = name2dex[d];

    if (!sdex)
    {
        AddNode(s);
        sdex = name2dex[s];
    }
    if (!ddex)
    {
        AddNode(d);
        ddex = name2dex[d];
    }

    ArcNode<DataType> *tmp = vertices[sdex - 1].firstarc;
    if (!tmp)
    {
        tmp = new ArcNode<DataType>(ddex, val);
        vertices[sdex - 1].firstarc = tmp;
    }
    else
    {
        while (tmp->nextarc)
            tmp = tmp->nextarc;
        tmp->nextarc = new ArcNode<DataType>(ddex, val);
    }

    if (!directed)
    {
        tmp = vertices[ddex - 1].firstarc;
        if (!tmp)
        {
            tmp = new ArcNode<DataType>(sdex, val);
            vertices[ddex - 1].firstarc = tmp;
        }
        else
        {
            while (tmp->nextarc)
                tmp = tmp->nextarc;
            ArcNode<DataType> *q = new ArcNode<DataType>(sdex, val);
            tmp->nextarc = q;
        }
    }
}

template <typename IndexType, typename DataType>
void ALGraph<IndexType, DataType>::DFS(IndexType s, bool *visited)
{
    bool flag = false;
    if (!visited)
    {
        visited = new bool[name2dex.size()]{false};
        flag = true;
    }

    int sdex = name2dex[s];
    cout << s << " ";
    visited[sdex - 1] = true;

    ArcNode<DataType> *p = vertices[sdex - 1].firstarc;
    while (p)
    {
        if (!visited[p->adjvex - 1])
            DFS(dex2name[p->adjvex], visited);
        p = p->nextarc;
    }

    if (flag)
        delete[] visited;
}

template <typename IndexType, typename DataType>
void ALGraph<IndexType, DataType>::FindRoute(IndexType i, IndexType j, vector<IndexType> path, bool *visited)
{
    bool flag = false;
    if (!visited)
    {
        path.clear();
        visited = new bool[name2dex.size()];
        flag = true;
    }

    int idex = name2dex[i];
    path.push_back(i);
    visited[idex - 1] = true;

    if (idex == name2dex[j])
    {
        for (IndexType name : path)
            cout << name << " ";
        cout << endl;
    }

    ArcNode<DataType> *p = vertices[idex - 1].firstarc;
    while (p)
    {
        if (!visited[p->adjvex - 1])
            FindRoute(dex2name[p->adjvex], j, path, visited);
        p = p->nextarc;
    }

    visited[idex - 1] = false;

    if (flag)
        delete[] visited;
}

template <typename IndexType, typename DataType>
void ALGraph<IndexType, DataType>::print()
{
    for (VNode<IndexType, DataType> node : vertices)
    {
        if (node.firstarc)
        {
            ArcNode<DataType> *p = node.firstarc;
            while (p)
            {
                cout << node.name << "->" << dex2name[p->adjvex] << ", val=" << p->value << endl;
                p = p->nextarc;
            }
        }
    }
}
#endif