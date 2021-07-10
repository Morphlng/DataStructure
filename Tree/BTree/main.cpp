/*
 * @Description: 
 * @Author: Niezl
 * @Gitee: https://gitee.com/Morphlng
 * @Date: 2021-03-21 16:10:50
 * @LastEditors: Morphling
 * @LastEditTime: 2021-03-28 09:59:21
 */

#include "BTree.h"
#include "Algorithm.h"
/*
        1
     2      3
       4  5
*/

int main()
{
    BTree<char> t1;

    // int first[] = {1, 2, 4, 3, 5};
    // int mid[] = {2, 4, 1, 5, 3};

    // char first[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    // char mid[] = {'B', 'C', 'A', 'E', 'D', 'G', 'H', 'F', 'I'};

    char first[] = {'+', '*', 'a', 'b', '-', '-', 'c', 'd'};
    char mid[] = {'a', '*', 'b', '+', '-', 'c', '-', 'd'};

    t1.Rebuild(first, mid, 8);

    Tree2Expression(t1.get_Root());

    return 0;
}