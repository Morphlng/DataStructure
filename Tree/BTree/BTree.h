/*
 * @Description: 二叉树模板
 * @Author: Morphling
 * @Date: 2021-03-18 14:56:22
 * @Gitee: https://gitee.com/Morphlng
 * @LastEditors: Niezl
 * @LastEditTime: 2021-03-26 08:33:07
 */
#pragma once
#include <iostream>
#include <stack>
using namespace std;

// 节点定义
template <typename T>
struct TNode
{
public:
    TNode(T e = T(), TNode<T> *lc = NULL, TNode<T> *rc = NULL)
    {
        data = e;
        lchild = lc;
        rchild = rc;
    }

    T data;
    TNode *lchild;
    TNode *rchild;
};

// 二叉树
template <typename T>
class BTree
{
public:
    BTree(T * = NULL, T * = NULL, int = 0);
    BTree(const BTree &);
    ~BTree();

    void set_Root(TNode<T> *);
    TNode<T> *get_Root();
    // 利用先序和中序序列，唯一确定二叉树
    TNode<T> *CreateBTree(T *, T *, int);

    // 调用构造函数
    void Rebuild(T *, T *, int);

private:
    TNode<T> *root;
    void Release(TNode<T> *root);         // 用于析构函数
    TNode<T> *Copy(const TNode<T> *node); // 用于拷贝构造
};

template <typename T>
BTree<T>::BTree(T *first, T *mid, int n)
{
    root = CreateBTree(first, mid, n);
}

template <typename T>
BTree<T>::BTree(const BTree<T> &t)
{
    root = Copy(t.root);
}

template <typename T>
TNode<T> *BTree<T>::Copy(const TNode<T> *node)
{
    TNode<T> *root = NULL;
    if (node != NULL)
    {
        root = new TNode<T>(node->data);
        root->lchild = Copy(node->lchild);
        root->rchild = Copy(node->rchild);
    }
    return root;
}

template <typename T>
BTree<T>::~BTree()
{
    Release(root);
}

template <typename T>
void BTree<T>::Release(TNode<T> *root)
{
    if (root != NULL)
    {
        Release(root->lchild);
        Release(root->rchild);
        delete root;
    }
}

template <typename T>
TNode<T> *BTree<T>::CreateBTree(T *first, T *mid, int n)
{
    if (n <= 0)
        return NULL;

    int k;
    TNode<T> *tmp = new TNode<T>(first[0]);
    for (k = 0; k < n; k++)
        if (mid[k] == first[0])
            break;

    tmp->lchild = CreateBTree(first + 1, mid, k);
    tmp->rchild = CreateBTree(first + k + 1, mid + k + 1, n - k - 1);
    return tmp;
}

template <typename T>
void BTree<T>::Rebuild(T *first, T *mid, int n)
{
    Release(root);
    root = CreateBTree(first, mid, n);
}

template <typename T>
void BTree<T>::set_Root(TNode<T> *p)
{
    root = p;
}

template <typename T>
TNode<T> *BTree<T>::get_Root()
{
    return root;
}