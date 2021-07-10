#pragma once
#ifndef _MGraph_H_
#define _MGraph_H_
#include <iostream>
#include <string>
#include <set>
#include <stack>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::queue;
using std::set;
using std::stack;
using std::string;
using std::unordered_map;
using std::vector;

template <typename IndexType, typename DataType>
class MGraph
{
private:
    unordered_map<IndexType, int> name2dex; // 节点名-下标（下标从1开始）
    unordered_map<int, IndexType> dex2name; // 下标-节点名（下标从1开始）
    vector<vector<DataType>> mat;           // 邻接矩阵
    struct nodedist                         // dist表示距离。该结构体用于求最短路径
    {
        int index;
        DataType dist;
        nodedist(int i, DataType d) : index(i), dist(d) {}
        bool operator<(const nodedist &other) const { return dist > other.dist; };
    };

public:
    MGraph() {}
    MGraph(const vector<IndexType> &, const vector<vector<DataType>> &);
    MGraph(const MGraph &);
    MGraph &operator=(const MGraph &);
    MGraph(MGraph &&);
    MGraph &operator=(MGraph &&);
    void show();

    // 增加一条边，true表无向图
    bool insert(IndexType, DataType, IndexType, bool = false);

    // 删除一条边，true表无向图
    bool del(IndexType, IndexType, bool = false);

    // 修改指定边权值
    bool update(IndexType, DataType, IndexType, bool = false);

    // 第一个邻接点的下标（从0开始），找不到时返回-1
    int FirstNeighbor(IndexType v);

    // 结点v相对于w的下一个邻接点的下标（从0开始），找不到时返回-1
    int NextNeighbor(IndexType v, IndexType w);

    // 顶点v到u之间是否存在路径（DFS）
    bool Exist_Path_DFS(IndexType v, IndexType u);

    // 顶点v到u之间是否存在路径（BFS）
    bool Exist_Path_BFS(IndexType v, IndexType u);

    void clear()
    {
        name2dex.clear();
        dex2name.clear();
        mat.clear();
    }

    // 调用广度优先遍历
    void BFS_Traverse();

    // 调用深度优先遍历
    void DFS_Traverse();

    // 从v号结点开始，广度优先遍历
    void BFS(IndexType, bool * = NULL);

    // 从v号节点开始，深度优先遍历
    void DFS_recur(IndexType, bool * = NULL);

    // 深度优先遍历（非递归）
    void DFS(IndexType, bool * = NULL);

    // 最小生成树，返回最小权值
    DataType Prim(IndexType s);

    // 最短路径，Floyd算法
    // 可适用于负权图，但不适用于“负权回路”，该类图不存在最短路径
    vector<vector<DataType>> Floyd();

    // 返回某点到某点间的最短路径长度，Dijkstra算法
    // 不适用于负权图
    DataType shortest_path(IndexType, IndexType);

    // 利用BFS，求某一节点到其他节点的最短路径
    // 仅适用于不带权图，或权值相等的图
    vector<DataType> shortest_path(IndexType);

    // 拓扑排序
    // 返回pair类型
    // 其中pair.first=true时则有拓扑排序
    // pair.second为拓扑排序结果
    pair<bool, vector<IndexType>> topological_sort();

    // 逆拓扑排序（利用DFS）
    pair<bool, vector<IndexType>> topological_rsort();
    bool topor_dfs(IndexType, vector<IndexType> &, bool *global, bool *curr_turn);

    // 拓扑排序，DFS
    vector<IndexType> topological_sort_dfs();
    void topo_dfs(IndexType, int &time, int *finishTime, bool *visited);

    ~MGraph() {}
};

#pragma region 基本操作
template <typename IndexType, typename DataType>
MGraph<IndexType, DataType>::MGraph(const vector<IndexType> &name, const vector<vector<DataType>> &m)
{
    if (name.size() != m.size())
        return;
    int num = name.size();
    if (num <= 0)
        return;
    mat = m;

    int i = 0;
    for (int i = 0; i < num; i++)
    {
        name2dex.insert(pair<IndexType, int>(name[i], i + 1));
        dex2name.insert(pair<int, IndexType>(i + 1, name[i]));
    }
}

template <typename IndexType, typename DataType>
MGraph<IndexType, DataType>::MGraph(const MGraph &g)
{
    name2dex = g.name2dex;
    dex2name = g.dex2name;
    mat = g.mat;
}

template <typename IndexType, typename DataType>
MGraph<IndexType, DataType> &MGraph<IndexType, DataType>::operator=(const MGraph &g)
{
    name2dex = g.name2dex;
    dex2name = g.dex2name;
    mat = g.mat;
    return *this;
}

template <typename IndexType, typename DataType>
MGraph<IndexType, DataType>::MGraph(MGraph &&g) // 右值引用，这会使传入参数析构
{
    name2dex = std::move(g.name2dex);
    dex2name = std::move(g.dex2name);
    mat = std::move(g.mat);
}

template <typename IndexType, typename DataType>
MGraph<IndexType, DataType> &MGraph<IndexType, DataType>::operator=(MGraph &&g)
{
    name2dex = std::move(g.name2dex);
    dex2name = std::move(g.dex2name);
    mat = std::move(g.mat);
    return *this;
}

template <typename IndexType, typename DataType>
bool MGraph<IndexType, DataType>::insert(IndexType s, DataType dist, IndexType e, bool t)
{
    int sdex = name2dex[s], edex = name2dex[e];
    if (!sdex || !edex) // 若有一点不存在，则先创建点
    {
        if (!sdex)
        {
            sdex = dex2name.size() + 1;
            name2dex[s] = sdex;
            dex2name[sdex] = s;
        }
        if (!edex)
        {
            edex = dex2name.size() + 1;
            name2dex[e] = edex;
            dex2name[edex] = e;
        }
        mat.resize(name2dex.size());
        for (int i = 0; i < mat.size(); i++)
        {
            mat[i].resize(mat.size(), 0x7F);
            mat[i][i] = 0;
        }
        mat[sdex - 1][edex - 1] = dist;
        if (t) // 无向图
            mat[edex - 1][sdex - 1] = dist;
    }
    else // 若两点都存在，直接加一条边
    {
        if (mat[sdex - 1][edex - 1] != 0x7F && mat[sdex - 1][edex - 1] != 0)
            return false;
        mat[sdex - 1][edex - 1] = dist;
        if (t)
            mat[edex - 1][sdex - 1] = dist;
    }
    return true;
}

template <typename IndexType, typename DataType>
bool MGraph<IndexType, DataType>::del(IndexType s, IndexType e, bool t)
{
    int sdex = name2dex[s], edex = name2dex[e];
    if (!sdex && !edex) // 删除不存在的节点
        return false;
    mat[sdex - 1][edex - 1] = 0;
    if (t)
        mat[edex - 1][sdex - 1] = 0;
    return true;
}

template <typename IndexType, typename DataType>
bool MGraph<IndexType, DataType>::update(IndexType s, DataType dist, IndexType e, bool t)
{
    int sdex = name2dex[s], edex = name2dex[e];
    if (!sdex && !edex)
        return false;
    mat[sdex - 1][edex - 1] = dist;
    if (t)
        mat[edex - 1][sdex - 1] = dist;
    return true;
}

template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::show()
{
    set<IndexType> sort_index;
    for (pair<IndexType, int> p : name2dex)
        sort_index.insert(p.first);

    cout << "  ";
    for (IndexType i : sort_index)
        cout << i << " ";
    cout << endl;

    for (IndexType i : sort_index)
    {
        cout << i << " ";
        for (IndexType j : sort_index)
        {
            if (mat[name2dex[i] - 1][name2dex[j] - 1] == 0x7F)
                cout << "∞"
                     << "  ";
            else
                cout << mat[name2dex[i] - 1][name2dex[j] - 1] << "  ";
        }
        cout << endl;
    }
}

template <typename IndexType, typename DataType>
int MGraph<IndexType, DataType>::FirstNeighbor(IndexType v)
{
    int index = name2dex[v] - 1;
    for (int i = 0; i < name2dex.size(); i++)
    {
        if (mat[index][i] != 0x7F && mat[index][i] != 0)
            return i;
    }
    return -1;
}

template <typename IndexType, typename DataType>
int MGraph<IndexType, DataType>::NextNeighbor(IndexType v, IndexType w)
{
    int index = name2dex[v] - 1;
    for (int i = name2dex[w]; i < name2dex.size(); i++)
    {
        if (mat[index][i] != 0x7F && mat[index][i] != 0)
            return i;
    }
    return -1;
}
#pragma endregion

#pragma region 遍历算法
template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::BFS(IndexType v, bool *visited)
{
    // 如果单独调用该函数，则需要建立visited数组
    bool flag = false;
    if (!visited)
    {
        visited = new bool[name2dex.size()]{false};
    }

    queue<IndexType> q;
    q.push(v);
    cout << v << " ";
    visited[name2dex[v] - 1] = true;
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, dex2name[w + 1]))
        {
            if (!visited[w])
            {
                cout << dex2name[w + 1] << " ";
                visited[w] = true;
                q.push(dex2name[w + 1]);
            }
        }
    }

    if (flag)
        delete[] visited;
}

template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::BFS_Traverse()
{
    bool visited[name2dex.size()]{false};
    for (int i = 0; i < name2dex.size(); i++)
        if (!visited[i])
            BFS(dex2name[i + 1], visited);
}

template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::DFS_recur(IndexType v, bool *visited)
{
    bool flag = false;
    if (!visited)
    {
        flag = true;
        visited = new bool[mat.size()]{false};
    }

    cout << v << " ";
    visited[name2dex[v] - 1] = true;
    for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, dex2name[w + 1]))
    {
        if (!visited[w])
            DFS_recur(dex2name[w + 1], visited);
    }

    if (flag)
        delete[] visited;
}

template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::DFS(IndexType v, bool *visited)
{
    bool flag = false;
    if (!visited)
    {
        flag = true;
        visited = new bool[mat.size()]{false};
    }

    stack<IndexType> s;
    s.push(v);
    while (!s.empty())
    {
        v = s.top();
        s.pop();
        if (!visited[name2dex[v] - 1])
        {
            cout << v << " ";
            visited[name2dex[v] - 1] = true;
        }

        int w = FirstNeighbor(v);
        while (w != -1)
        {
            if (!visited[w])
                s.push(dex2name[w + 1]);
            w = NextNeighbor(v, dex2name[w + 1]);
        }
    }

    if (flag)
        delete[] visited;
}

template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::DFS_Traverse()
{
    bool visited[name2dex.size()]{false};
    for (int i = 0; i < name2dex.size(); i++)
        if (!visited[i])
            DFS(dex2name[i + 1], visited);
}
#pragma endregion

template <typename IndexType, typename DataType>
bool MGraph<IndexType, DataType>::Exist_Path_DFS(IndexType v, IndexType u)
{
    bool visited[name2dex.size()]{false};

    stack<IndexType> s;
    s.push(v);
    while (!s.empty())
    {
        v = s.top();
        visited[name2dex[v] - 1] = true;
        s.pop();
        if (v == u)
            return true;
        else
        {
            int w = FirstNeighbor(v);
            while (w != -1)
            {
                if (!visited[w])
                    s.push(dex2name[w + 1]);
                w = NextNeighbor(v, dex2name[w + 1]);
            }
        }
    }
    return false;
}

template <typename IndexType, typename DataType>
bool MGraph<IndexType, DataType>::Exist_Path_BFS(IndexType v, IndexType u)
{
    bool visited[name2dex.size()]{false};

    queue<IndexType> q;
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        if (v == u)
            return true;
        visited[name2dex[v] - 1] = true;
        q.pop();
        for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, dex2name[w + 1]))
        {
            if (!visited[w])
                q.push(dex2name[w + 1]);
        }
    }
    return false;
}

template <typename IndexType, typename DataType>
DataType MGraph<IndexType, DataType>::Prim(IndexType s)
{
    int n = name2dex.size();
    DataType result = DataType();

    DataType lowcost[n];                    // 如果一个结点已经加入点集，则lowcost为-1
    memset(lowcost, 0x7F, sizeof(lowcost)); // 0x7F为无穷大

    int i, j, sdex = name2dex[s];
    for (j = 0; j < n; j++)
        if (mat[sdex - 1][j] != 0 && mat[sdex - 1][j] < lowcost[j])
            lowcost[j] = mat[sdex - 1][j];

    lowcost[sdex - 1] = -1;

    for (i = 0; i < n; i++)
    {
        DataType min = 0x7F;
        int mindex = -1;
        for (j = 0; j < n; j++)
        {
            if (lowcost[j] != -1 && lowcost[j] < min)
            {
                min = lowcost[j];
                mindex = j;
            }
        }
        if (mindex == -1)
            break;

        lowcost[mindex] = -1;
        result += min;

        for (j = 0; j < n; j++)
        {
            if (mat[mindex][j] != 0 && mat[mindex][j] < lowcost[j])
                lowcost[j] = mat[mindex][j];
        }
    }
    return result;
}

template <typename IndexType, typename DataType>
DataType MGraph<IndexType, DataType>::shortest_path(IndexType s, IndexType e)
{
    int sdex = name2dex[s], edex = name2dex[e];
    cout << "Calculate Path...  start:" << s << "(" << sdex << ") end:" << e << "(" << edex << ")\n";
    if (!sdex || !edex)
        return 0;
    if (sdex == edex)
        return mat[sdex - 1][edex - 1];
    vector<bool> vertex_set(mat.size(), false); // 标明一个点是否已经走过
    vector<DataType> dis(mat.size(), 0);        // 记录到各点的距离
    priority_queue<nodedist> que;               // 优先队列，可以pop出每次最优的点
    que.push(nodedist(sdex - 1, 0));
    while (!que.empty())
    {
        int index = que.top().index;
        DataType dist = que.top().dist;
        que.pop();
        // cout << "current point:" << dex2name[index + 1] << " ";
        if (vertex_set[index])
            continue; //has confirmed
        if (index == edex - 1)
            return dist;
        vertex_set[index] = true;
        dis[index] = dist;
        for (int i = 0; i < mat.size(); i++)
        {
            if (mat[index][i])
                que.push(nodedist(i, dist + mat[index][i]));
        }
    }
    return dis[edex - 1];
}

template <typename IndexType, typename DataType>
vector<DataType> MGraph<IndexType, DataType>::shortest_path(IndexType s)
{
    int num = name2dex.size();
    vector<DataType> distance; // distance[u]表示从s到u的最短路径
    vector<int> path;          // path表示最短路径从哪个顶点来
    distance.resize(num);
    path.resize(num);
    bool visited[num]{false};

    for (int i = 0; i < num; i++)
    {
        distance[i] = 0x7F;
        path[i] = -1;
    }

    distance[name2dex[s] - 1] = 0;
    visited[name2dex[s] - 1] = true;
    queue<IndexType> q;
    q.push(s);
    while (!q.empty())
    {
        IndexType curr = q.front();
        q.pop();
        for (int w = FirstNeighbor(curr); w >= 0; w = NextNeighbor(curr, dex2name[w + 1]))
        {
            if (!visited[w])
            {
                distance[w] = distance[name2dex[curr] - 1] + 1;
                path[w] = name2dex[curr] - 1;
                visited[w] = true;
                q.push(dex2name[w + 1]);
            }
        }
    }

    return distance;
}

template <typename IndexType, typename DataType>
vector<vector<DataType>> MGraph<IndexType, DataType>::Floyd()
{
    // T：O(|V|^3) S:O(|V|^2)
    int num = name2dex.size();

    vector<vector<DataType>> A; // 最短路径矩阵
    vector<vector<int>> path;   // 中转顶点（仅当需要路径序列时才有意义）
    A.resize(num), path.resize(num);
    for (int i = 0; i < num; i++)
        A[i].resize(num), path[i].resize(num);

    // 初始化A和path
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
            A[i][j] = mat[i][j], path[i][j] = -1;

    for (int k = 0; k < num; k++)
        for (int i = 0; i < num; i++)
            for (int j = 0; j < num; j++)
                if (A[i][j] > A[i][k] + A[k][j])
                    A[i][j] = A[i][k] + A[k][j], path[i][j] = k;

    return A;
}

template <typename IndexType, typename DataType>
pair<bool, vector<IndexType>> MGraph<IndexType, DataType>::topological_sort()
{
    pair<bool, vector<IndexType>> ans(false, vector<IndexType>());
    queue<int> my_que;
    vector<int> indegrees(mat.size(), 0);
    int num = mat.size();

    // 统计入度
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat.size(); j++)
            if (mat[j][i])
                indegrees[i]++;

    for (int i = 0; i < indegrees.size(); i++)
        if (!indegrees[i])
        {
            my_que.push(i);
            ans.second.push_back(dex2name[i + 1]);
        }

    // 每次找入度为0的节点，加入结果
    while (!my_que.empty())
    {
        int index = my_que.front();
        my_que.pop();
        for (int i = 0; i < mat.size(); i++)
            if (mat[index][i])
                if (--indegrees[i] == 0)
                {
                    my_que.push(i);
                    ans.second.push_back(dex2name[i + 1]);
                }

        num--;
    }
    // 仅当所有节点都加入结果（没有环路），才有拓扑排序
    ans.first = (num == 0);
    if (!ans.first)
        ans.second.clear();

    return ans;
}

template <typename IndexType, typename DataType>
pair<bool, vector<IndexType>> MGraph<IndexType, DataType>::topological_rsort()
{
    vector<IndexType> list;
    bool visited[name2dex.size()]{false};

    bool flag = true;
    for (int i = 0; i < name2dex.size(); i++)
    {
        // 记录一轮递归中访问的结点
        // 如果没有回路不会出现相同结点被两次访问
        bool recur_visited[name2dex.size()]{false};

        if (!visited[i])
            flag = topor_dfs(dex2name[i + 1], list, visited, recur_visited);
        if (!flag)
            return pair<bool, vector<IndexType>>(false, vector<IndexType>());
    }

    return pair<bool, vector<IndexType>>(flag, list);
}

template <typename IndexType, typename DataType>
bool MGraph<IndexType, DataType>::topor_dfs(IndexType curr, vector<IndexType> &list, bool *visited, bool *recur_visted)
{
    // 该函数不应被单独调用
    if (!visited || !recur_visted)
        return false;

    visited[name2dex[curr] - 1] = true;
    recur_visted[name2dex[curr] - 1] = true;

    bool flag = true;
    for (int w = FirstNeighbor(curr); w >= 0; w = NextNeighbor(curr, dex2name[w + 1]))
    {
        if (recur_visted[w])
            return false;

        if (!visited[w])
            flag = topor_dfs(dex2name[w + 1], list, visited, recur_visted);

        if (!flag)
            return false;
    }
    list.push_back(curr);

    return true;
}

template <typename IndexType, typename DataType>
vector<IndexType> MGraph<IndexType, DataType>::topological_sort_dfs()
{
    vector<IndexType> list;
    bool visited[name2dex.size()]{false};
    int finishTime[name2dex.size()]{0};

    int time = 0; // 计数器，拓扑排序即计数器从大到小
    for (int i = 0; i < name2dex.size(); i++)
    {
        if (!visited[i])
            topo_dfs(dex2name[i + 1], time, finishTime, visited);
    }

    for (int i = 0; i < name2dex.size(); i++)
    {
        DataType min = -1;
        int index = 0;
        for (int j = 0; j < name2dex.size(); j++)
        {
            if (finishTime[j] > min)
            {
                min = finishTime[j];
                index = j;
            }
        }
        list.push_back(dex2name[index + 1]);
        finishTime[index] = -1;
    }

    return list;
}

template <typename IndexType, typename DataType>
void MGraph<IndexType, DataType>::topo_dfs(IndexType curr, int &time, int *finishTime, bool *visited)
{
    // 该函数不应被单独调用
    if (!visited || !finishTime)
        return;

    visited[name2dex[curr] - 1] = true;

    for (int w = FirstNeighbor(curr); w >= 0; w = NextNeighbor(curr, dex2name[w + 1]))
    {
        if (!visited[w])
            topo_dfs(dex2name[w + 1], time, finishTime, visited);
    }
    time++;
    finishTime[name2dex[curr] - 1] = time;
}
#endif