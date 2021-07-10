/*
 * @Description: 
 * @Author: Morphling
 * @Date: 2021-03-28 15:00:49
 * @Gitee: https://gitee.com/Morphlng
 * @LastEditors: Niezl
 * @LastEditTime: 2021-03-29 13:38:01
 */

#include "BSTree.h"

int main()
{
  /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */

  int balance[] = {10, 20, 30, 40, 50, 25};
  BSTree<int> t(balance, 6, true);

  // int str[] = {19, 13, 50, 11, 26, 66, 21, 30, 60, 70};
  // BSTree<int> t(str, 10);

  t.print();

  t.BST_Balance_Delete(35);

  t.print();

  return 0;
}