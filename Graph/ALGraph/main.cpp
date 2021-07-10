/*
 * @Description: 
 * @Author: Morphling
 * @Date: 2021-04-04 08:11:23
 * @Gitee: https://gitee.com/Morphlng
 * @LastEditors: Niezl
 * @LastEditTime: 2021-04-08 10:16:38
 */
#include "ALGraph.h"
using namespace std;

int main()
{
    ALGraph<char, int> g;
    g.Insert('A', 1, 'B');
    g.Insert('A', 1, 'C');
    g.Insert('A', 1, 'D');
    g.Insert('B', 1, 'E');
    g.Insert('B', 1, 'F');
    g.Insert('C', 1, 'E');
    g.Insert('D', 1, 'F');

    cout << g.Kruskal() << endl;

    return 0;
}