/*
 * @Description: 
 * @Author: Morphling
 * @Date: 2021-03-28 14:52:56
 * @Gitee: https://gitee.com/Morphlng
 * @LastEditors: Niezl
 * @LastEditTime: 2021-03-29 12:48:07
 */
#pragma once
#include <iostream>
#include <type_traits>
#include <stack>
using namespace std;

// 节点定义
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
struct TNode
{
public:
    TNode(T e = T(), TNode<T> *lc = NULL, TNode<T> *rc = NULL)
    {
        data = e;
        lchild = lc;
        rchild = rc;
        height = 1;
    }

    T data;
    TNode *lchild;
    TNode *rchild;
    int height;
};

template <typename T>
class BSTree
{
public:
    BSTree(T * = NULL, int = 0, bool balance = false);
    BSTree(const BSTree &);
    ~BSTree();
    void set_Root(TNode<T> *);
    TNode<T> *get_Root();

    void Create_BST(T *, int n);
    void Create_Balance_BST(T *, int n);
    // 调用构造函数
    void Rebuild(T *, int);

    TNode<T> *BST_Search(const T &key);

    // 二叉排序树插入操作
    bool BST_Insert(const T &key);
    // 二叉排序树删除操作
    bool BST_Delete(const T &key);

    int height(TNode<T> *);
    // 封装的平衡二叉树插入操作
    bool BST_Balance_Insert(const T &key);
    // 封装的平衡二叉树删除操作
    bool BST_Balance_Delete(const T &key);

    // 以升序序列输出树的结点(中序遍历)
    void print();

private:
    TNode<T> *root;
    // 用于析构函数
    void Release(TNode<T> *root);
    // 用于拷贝构造
    TNode<T> *Copy(const TNode<T> *node);
    // 右旋
    TNode<T> *R_Rotate(TNode<T> *y);
    // 左旋
    TNode<T> *L_Rotate(TNode<T> *x);
    // 平衡二叉树插入操作(递归)
    TNode<T> *insert(TNode<T> *, const T &key);
    // 平衡二叉树删除操作(递归)
    TNode<T> *remove(TNode<T> *, const T &key);
};

template <typename T>
BSTree<T>::BSTree(T *nums, int n, bool balance)
{
    if (!balance)
        Create_BST(nums, n);
    else
        Create_Balance_BST(nums, n);
}

template <typename T>
BSTree<T>::BSTree(const BSTree<T> &t)
{
    root = Copy(t.root);
}

template <typename T>
TNode<T> *BSTree<T>::Copy(const TNode<T> *node)
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
BSTree<T>::~BSTree()
{
    Release(root);
}

template <typename T>
void BSTree<T>::Release(TNode<T> *root)
{
    if (root != NULL)
    {
        Release(root->lchild);
        Release(root->rchild);
        delete root;
    }
}

template <typename T>
TNode<T> *BSTree<T>::BST_Search(const T &key)
{
    TNode<T> *p = root;
    while (p && p->data != key)
    {
        if (key < p->data)
            p = p->lchild;
        else
            p = p->rchild;
    }
    return p; // 查找失败将返回NULL
}

template <typename T>
bool BSTree<T>::BST_Insert(const T &key)
{
    if (!root)
    {
        root = new TNode<T>(key);
        return true;
    }

    TNode<T> *p = root;
    while (p)
    {
        if (p->data == key)
            return false;

        if (p->data < key)
        {
            if (p->rchild)
                p = p->rchild;
            else
                break;
        }
        else
        {
            if (p->lchild)
                p = p->lchild;
            else
                break;
        }
    }
    if (p->data < key)
        p->rchild = new TNode<T>(key);
    else
        p->lchild = new TNode<T>(key);
    return true;
}

template <typename T>
void BSTree<T>::Create_BST(T *nums, int n)
{
    root = NULL;
    int i = 0;
    while (i < n)
    {
        BST_Insert(nums[i]);
        i++;
    }
}

template <typename T>
void BSTree<T>::Rebuild(T *nums, int n)
{
    Release(root);
    Create_BST(nums, n);
}

template <typename T>
void BSTree<T>::set_Root(TNode<T> *p)
{
    root = p;
}

template <typename T>
TNode<T> *BSTree<T>::get_Root()
{
    return root;
}

template <typename T>
bool BSTree<T>::BST_Delete(const T &key)
{
    TNode<T> *p = root, *pre = NULL;
    while (p)
    {
        if (p->data == key)
            break;

        pre = p;
        if (p->data < key)
            p = p->rchild;
        else
            p = p->lchild;
    }

    if (!p) // 没有找到key
        return false;

    if (!p->lchild && !p->rchild) // key在叶子结点，直接删除
    {
        if (p == pre->lchild)
            pre->lchild = NULL;
        else if (p == pre->rchild)
            pre->rchild = NULL;
        delete p;
    }
    else if (p->lchild && !p->rchild) // 只有一边孩子，则将孩子值赋给p
    {
        TNode<T> *tmp = p->lchild;
        *p = *tmp;
        delete tmp;
    }
    else if (!p->lchild && p->rchild)
    {
        TNode<T> *tmp = p->rchild;
        *p = *tmp;
        delete tmp;
    }
    else // 若左右子树都有，则以右子树最左结点（直接后继）替代（或者也可以用直接前驱）
    {
        TNode<T> *tmp = p->rchild;
        pre = p;
        while (tmp->lchild)
        {
            pre = tmp;
            tmp = tmp->lchild;
        }
        p->data = tmp->data;

        if (tmp->rchild)
        {
            TNode<T> *temp = tmp->rchild;
            *tmp = *temp;
            delete temp;
        }
        else
        {
            if (pre->lchild == tmp)
                pre->lchild = NULL;
            else if (pre->rchild == tmp)
                pre->rchild = NULL;
            delete tmp;
        }
    }

    return true;
}

template <typename T>
void BSTree<T>::print()
{
    TNode<T> *p = root;
    stack<TNode<T> *> s;
    while (p || !s.empty())
    {
        if (p)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            cout << p->data << " ";
            p = p->rchild;
        }
    }
    cout << endl;
}

#pragma region 平衡二叉树

template <typename T>
void BSTree<T>::Create_Balance_BST(T *nums, int n)
{
    root = NULL;
    int i = 0;
    while (i < n)
    {
        root = insert(root, nums[i]);
        i++;
    }
}

template <typename T>
TNode<T> *BSTree<T>::R_Rotate(TNode<T> *y)
{
    TNode<T> *x = y->lchild;
    y->lchild = x->rchild;
    x->rchild = y;

    y->height = max(height(y->lchild), height(y->rchild)) + 1;
    x->height = max(height(x->lchild), height(x->rchild)) + 1;

    return x; // x变为新的根，返回
}

template <typename T>
TNode<T> *BSTree<T>::L_Rotate(TNode<T> *x)
{
    TNode<T> *y = x->rchild;
    x->rchild = y->lchild;
    y->lchild = x;

    x->height = max(height(x->lchild), height(x->rchild)) + 1;
    y->height = max(height(y->lchild), height(y->rchild)) + 1;

    return y; // y变为新的根，返回
}
template <typename T>
int BSTree<T>::height(TNode<T> *node)
{
    if (!node)
        return 0;
    return node->height;
}

template <typename T>
bool BSTree<T>::BST_Balance_Insert(const T &key)
{
    TNode<T> *tmp = root;
    root = insert(root, key);
    if (tmp == root) // 没有插入就不会变
        return false;
    return true;
}

template <typename T>
TNode<T> *BSTree<T>::insert(TNode<T> *node, const T &key)
{
    if (!node)
    {
        TNode<T> *tmp = new TNode<T>(key);
        return tmp;
    }

    if (node->data < key)
        node->rchild = insert(node->rchild, key);
    else if (node->data > key)
        node->lchild = insert(node->lchild, key);
    else
        return node; // 不允许有相同值结点

    node->height = max(height(node->lchild), height(node->rchild)) + 1;

    int balance = height(node->lchild) - height(node->rchild);

    // LL
    if (balance > 1 && key < node->lchild->data)
        return R_Rotate(node);

    // RR
    if (balance < -1 && key > node->rchild->data)
        return L_Rotate(node);

    // LR
    if (balance > 1 && key > node->lchild->data)
    {
        node->lchild = L_Rotate(node->lchild);
        return R_Rotate(node);
    }

    // RL
    if (balance < -1 && key < node->rchild->data)
    {
        node->rchild = R_Rotate(node->rchild);
        return L_Rotate(node);
    }

    // 加入后也平衡直接返回
    return node;
}

template <typename T>
bool BSTree<T>::BST_Balance_Delete(const T &key)
{
    TNode<T> *tmp = root;
    root = remove(root, key);
    if (tmp == root) // 没有删除节点，就不会变
        return false;
    return true;
}

template <typename T>
TNode<T> *BSTree<T>::remove(TNode<T> *node, const T &key)
{
    // 1、先按照正常的BST删除节点
    if (!node)
        return node;

    if (node->data < key)
        node->rchild = remove(node->rchild, key);
    else if (node->data > key)
        node->lchild = remove(node->lchild, key);
    else
    {
        if (!node->lchild || !node->rchild)
        {
            TNode<T> *tmp = node->lchild ? node->lchild : node->rchild;
            if (!tmp) // 没有孩子
            {
                tmp = node;
                node = NULL;
            }
            else
                *node = *tmp;
            delete tmp;
        }
        else // 两个孩子都有，找右子树最左结点
        {
            TNode<T> *tmp = node->rchild;
            while (tmp->lchild)
                tmp = tmp->lchild;

            node->data = tmp->data;
            node->rchild = remove(node->rchild, tmp->data);
        }
    }

    // 下面开始平衡化
    if (!node)
        return node;

    // 更新高度
    node->height = max(height(node->lchild), height(node->rchild)) + 1;

    int balance = height(node->lchild) - height(node->rchild);

    // LL
    if (balance > 1 && (height(node->lchild->lchild) - height(node->lchild->rchild)) >= 0)
        return R_Rotate(node);

    // LR
    if (balance > 1 && (height(node->lchild->lchild) - height(node->lchild->rchild)) < 0)
    {
        node->lchild = L_Rotate(node->lchild);
        return R_Rotate(node);
    }

    // RR
    if (balance < -1 && (height(node->rchild->lchild) - height(node->rchild->rchild)) <= 0)
        return L_Rotate(node);

    // RL
    if (balance < -1 && (height(node->rchild->lchild) - height(node->rchild->rchild)) > 0)
    {
        node->rchild = R_Rotate(node->rchild);
        return L_Rotate(node);
    }

    return node;
}

#pragma endregion