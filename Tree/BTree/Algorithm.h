/*
 * @Description: 
 * @Author: Niezl
 * @Gitee: https://gitee.com/Morphlng
 * @Date: 2021-03-21 18:58:16
 * @LastEditors: Morphling
 * @LastEditTime: 2021-03-28 09:58:54
 */
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <type_traits>
#include "BTree.h"
using namespace std;

#pragma region 基本操作

// 先序遍历
template <typename T>
void Pre_Order_Traverse(TNode<T> *root)
{
    if (root)
        cout << root->data << " ";
    if (root->lchild)
        Pre_Order_Traverse(root->lchild);
    if (root->rchild)
        Pre_Order_Traverse(root->rchild);
}

// 中序遍历
template <typename T>
void In_Order_Traverse_Recur(TNode<T> *root)
{
    if (root->lchild)
        In_Order_Traverse(root->lchild);
    if (root)
        cout << root->data << " ";
    if (root->rchild)
        In_Order_Traverse(root->rchild);
}

// 中序非递归遍历（先序大同小异，略）
template <typename T>
void In_Order_Traverse(BTree<T> t)
{
    stack<TNode<T> *> s;
    TNode<T> *p = t.get_Root();

    while (p || !s.empty())
    {
        if (p) // 向左走到底
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
}

// 后序遍历
template <typename T>
void Post_Order_Traverse_Recur(TNode<T> *root)
{
    if (root->lchild)
        Post_Order_Traverse(root->lchild);
    if (root->rchild)
        Post_Order_Traverse(root->rchild);
    if (root)
        cout << root->data << " ";
}

// 求树的深度
template <typename T>
int Depth(TNode<T> *root)
{
    if (!root)
        return 0;

    int l = Depth(root->lchild);
    int r = Depth(root->rchild);
    return l > r ? l + 1 : r + 1;
}

// 层序遍历
template <typename T>
void Level_Traverse(BTree<T> t)
{
    if (!t.get_Root())
        return;

    queue<TNode<T> *> tmp_queue;
    tmp_queue.push(t.get_Root());

    while (!tmp_queue.empty())
    {
        TNode<T> *current = tmp_queue.front();
        tmp_queue.pop();
        if (current->lchild)
            tmp_queue.push(current->lchild);
        if (current->rchild)
            tmp_queue.push(current->rchild);
        cout << current->data << " ";
    }
    cout << endl;
}

#pragma endregion

#pragma region 算法

// 后序遍历，非递归算法
template <typename T>
void Post_Order_Traverse(BTree<T> t)
{
    if (!t.get_Root())
        return;

    stack<TNode<T> *> s;
    s.push(t.get_Root());

    TNode<T> *prev = NULL; // 设立一个前向指针来判断当前的迭代方向

    while (!s.empty())
    {
        TNode<T> *curr = s.top();

        // 自上而下迭代
        // !prev对应根结点；prev->lchild==curr对应走左孩子，prev->rchild==curr对应走右孩子
        if (!prev || prev->lchild == curr || prev->rchild == curr)
        {
            if (curr->lchild)
                s.push(curr->lchild);
            else if (curr->rchild)
                s.push(curr->rchild);
        }
        // 自下而上迭代
        else if (curr->lchild == prev)
        {
            if (curr->rchild)
                s.push(curr->rchild);
        }
        // 从右孩子返回到根结点，输出根结点
        else
        {
            cout << curr->data << " ";
            s.pop();
        }
        prev = curr;
    }
    cout << endl;
}

// 求树的高度，非递归
template <typename T>
int Height(BTree<T> t)
{
    TNode<T> *p = t.get_Root();
    queue<TNode<T> *> q;
    q.push(p);

    int height = 0;
    TNode<T> *last = t.get_Root(); // 记录当前层最右结点
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (p->lchild)
            q.push(p->lchild);
        if (p->rchild)
            q.push(p->rchild);
        if (p == last)
        {
            height++;
            last = q.back();
        }
    }
    return height;
}

// 判断完全二叉树
template <typename T>
bool CompleteBTree(BTree<T> t)
{
    queue<TNode<T> *> q;
    TNode<T> *p = t.get_Root();
    if (!p)
        return true;
    q.push(p);

    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (p)
        {
            // 将包括空结点在内的所有结点入队
            q.push(p->lchild);
            q.push(p->rchild);
        }
        else
        {
            // 如果空结点后还有非空结点，说明不是完全二叉树
            while (!q.empty())
            {
                p = q.front();
                q.pop();
                if (p)
                    return false;
            }
        }
    }
    return true;
}

// 返回双分支结点个数
template <typename T>
void dul_Node(TNode<T> *root, int &num)
{
    if (!root)
        return;

    if (root->lchild && root->rchild)
        num++;

    if (root->lchild)
        dul_Node(root->lchild, num);

    if (root->rchild)
        dul_Node(root->rchild, num);
}

template <typename T>
void Swap_LR(TNode<T> *root)
{
    if (!root)
        return;

    if (root->lchild)
        Swap_LR(root->lchild);

    if (root->rchild)
        Swap_LR(root->rchild);

    TNode<T> *tmp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = tmp;
}

// 删除值为x的结点为根的子树
template <typename T>
void Delete_XNode(TNode<T> *root)
{
    if (root)
    {
        Delete_XNode(root->lchild);
        Delete_XNode(root->rchild);
        delete root;
    }
}

template <typename T>
void Delete_X(BTree<T> &t, T x)
{
    TNode<T> *p = t.get_Root();
    if (!p)
        return;

    // 根结点为所找，则直接删除整棵树
    if (p->data == x)
    {
        Delete_XNode(p);
        t.set_Root(nullptr);
        return;
    }

    queue<TNode<T> *> q;
    q.push(p);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (p->lchild)
            if (p->lchild->data == x)
            {
                Delete_XNode(p->lchild);
                p->lchild = NULL;
            }
            else
                q.push(p->lchild);

        if (p->rchild)
            if (p->rchild->data == x)
            {
                Delete_XNode(p->rchild);
                p->rchild = NULL;
            }
            else
                q.push(p->rchild);
    }
}

// 输出值为x的结点的全部祖先
template <typename T>
void X_Ancestor(BTree<T> t, T x)
{
    TNode<T> *p = t.get_Root();
    if (!p || p->data == x)
        return;

    stack<TNode<T> *> s;
    s.push(p);

    // 非递归的后序遍历
    TNode<T> *prev = NULL;
    while (!s.empty())
    {
        TNode<T> *curr = s.top();

        if (!prev || prev->lchild == curr || prev->rchild == curr)
        {
            if (curr->lchild)
                s.push(curr->lchild);
            else if (curr->rchild)
                s.push(curr->rchild);
        }
        else if (curr->lchild == prev)
        {
            if (curr->rchild)
                s.push(curr->rchild);
        }
        else // 从右孩子返回到根结点
        {
            if (curr->data == x)
                break;
            else
                s.pop();
        }
        prev = curr;
    }

    while (!s.empty())
    {
        cout << s.top()->data << " ";
        s.pop();
    }
    cout << endl;
}

// 返回两个节点最近的公共祖先
template <typename T>
TNode<T> *CommonAncestor(TNode<T> *root, T p, T q)
{
    if (!root || root->data == p || root->data == q)
        return root;

    // 在左右子树中分别寻找
    TNode<T> *left = CommonAncestor(root->lchild, p, q);
    TNode<T> *right = CommonAncestor(root->rchild, p, q);

    if (!left && !right)
        return NULL;
    else if (left && !right)
        return left;
    else if (right && !left)
        return right;

    return root;
}

// 求二叉树的宽度
template <typename T>
int Width(BTree<T> t)
{
    TNode<T> *p = t.get_Root();
    queue<TNode<T> *> q;
    if (!p)
        return 0;

    q.push(p);
    TNode<T> *last = p;
    int width = 1;

    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (p->lchild)
            q.push(p->lchild);

        if (p->rchild)
            q.push(p->rchild);

        if (p == last)
        {
            // q.size相当于下一层的宽度
            width = width > q.size() ? width : q.size();
            last = q.back();
        }
    }

    return width;
}

/*
    1
  2    3
4  5  6  7

      0  1  2 3    4  5 6
Pre:  1 [2 [4 5]] [3 [6 7]]
In:   4 2 5 1 6 3 7
Post: 4 5 2 6 7 3 1
*/

stack<int> post_stack;
// 将一个满二叉树的前序序列转为后序序列
// 当然你需要输出栈的内容才是最后结果
template <typename T>
void Pre2Post(T *pre, int low, int high)
{
    int length = high - low;
    if (length > 0)
    {
        post_stack.push(pre[low]);

        low += (length / 2) + 1;

        // 先对先序序列中的右子树找根
        Pre2Post(pre, low, high);

        low -= length / 2;
        high -= length / 2;

        // 再对先序序列中的左子树找根
        Pre2Post(pre, low, high);
    }
    else
    {
        // 叶子结点
        post_stack.push(pre[low]);
    }
}

// 将叶子结点从左至右串成链表
template <typename T>
TNode<T> *LeafLink(BTree<T> t)
{
    TNode<T> *pre = NULL, *head = new TNode<T>;
    TNode<T> *p = t.get_Root();
    if (!p)
        return NULL;

    stack<TNode<T> *> s;
    while (p || !s.empty())
    {
        if (p)
        {
            if (!p->lchild && !p->rchild)
            {
                TNode<T> *tmp = new TNode<T>(p->data);
                if (!head->rchild)
                    head->rchild = tmp;
                else
                    pre->rchild = tmp;
                pre = tmp;
            }
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }

    return head;
}

// 判断两颗二叉树是否相似
template <typename T>
bool Sim_Tree(TNode<T> *t1, TNode<T> *t2)
{
    if (!t1 && !t2)
        return true;
    else if (!t1 || !t2)
        return false;

    return Sim_Tree(t1->lchild, t2->lchild) && Sim_Tree(t1->rchild, t2->rchild);
}

// 求二叉树的带权路径长度（WPL）
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
int WPL(BTree<T> t)
{
    TNode<T> *p = t.get_Root();
    if (!p)
        return 0;

    int wpl = 0;
    int level = 0;
    TNode<T> *last = p;
    queue<TNode<T> *> q;
    q.push(p);

    while (!q.empty())
    {
        p = q.front();
        q.pop();

        if (!p->lchild && !p->rchild)
            wpl += p->data * level;

        if (p->lchild)
            q.push(p->lchild);
        if (p->rchild)
            q.push(p->rchild);

        if (last == p)
        {
            level++;
            last = q.back();
        }
    }

    return wpl;
}

// a操作符优先级是否高于b操作符
// true表示大于等于，false表示小于
bool isPrior(char a, char b)
{
    switch (a)
    {
    case '+':
    case '-':
        if (b == '+' || b == '-')
            return true;
        else
            return false;

    case '*':
    case '/':
        if (b == '*' || b == '/' || b == '+' || b == '-')
            return true;
        else
            return false;

    default:
        break;
    }
}

// char first[] = {'+', '*', 'a', 'b', '-', '-', 'c', 'd'};
// char mid[] = {'a', '*', 'b', '+', '-', 'c', '-', 'd'};

// 将二叉树转为中缀表达式
void Tree2Expression(TNode<char> *root)
{
    if (!root)
        return;

    bool prior;
    if (root->lchild)
    {
        prior = isPrior(root->data, root->lchild->data);
        if (prior)
            cout << "(";
        Tree2Expression(root->lchild);
        if (prior)
            cout << ")";
    }

    cout << root->data;

    if (root->rchild)
    {
        prior = isPrior(root->data, root->rchild->data);
        if (prior)
            cout << "(";
        Tree2Expression(root->rchild);
        if (prior)
            cout << ")";
    }
}

#pragma endregion