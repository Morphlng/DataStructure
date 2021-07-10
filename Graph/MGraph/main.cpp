/*
 * @Description: 
 * @Author: Morphling
 * @Date: 2021-03-26 14:35:40
 * @Gitee: https://gitee.com/Morphlng
 * @LastEditors: Morphling
 * @LastEditTime: 2021-04-11 11:56:55
 */
#include "MGraph.h"

int main()
{
    MGraph<string, int> G;
    // G.insert("V0", 6, "V1", true);
    // G.insert("V0", 5, "V2", true);
    // G.insert("V0", 1, "V3", true);
    // G.insert("V2", 4, "V3", true);
    // G.insert("V1", 5, "V3", true);
    // G.insert("V1", 3, "V4", true);
    // G.insert("V3", 6, "V4", true);
    // G.insert("V3", 4, "V5", true);
    // G.insert("V4", 6, "V5", true);
    // G.insert("V2", 2, "V5", true);

    G.insert("V0", 1, "V1", false);
    G.insert("V2", 1, "V3", false);
    G.insert("V1", 1, "V3", false);
    G.insert("V3", 1, "V4", false);
    G.insert("V2", 1, "V4", false);

    G.show();

    auto result = G.topological_sort_dfs();

    return 0;
}
