#include "LNode.h"

template <typename T>
void DeleteX(LinkList<T> &L, T e)
{
    LNode<T> *p = L.getHead(), *q = p->next, *tmp;
    int count = 0;
    while (q != NULL)
    {
        if (q->data == e)
        {
            tmp = q;
            q = q->next;
            delete tmp;
        }
        else
        {
            p->next = q;
            p = q;
            q = q->next;
            count++;
        }
    }
    p->next = NULL;
    L.setLength(count);
}

template <typename T>
T DeleteMin(LinkList<T> &L)
{
    LNode<T> *pre = L.getHead(), *p = pre->next; // 寻找时的工作指针

    LNode<T> *minpre = pre, *minp = p; // 记录最小节点与其前驱
    T min = p->data;

    while (p != NULL)
    {
        if (p->data < min)
        {
            min = p->data;
            minpre = pre;
            minp = p;
        }
        pre = p;
        p = p->next;
    }

    if (minp != NULL)
    {
        minpre->next = minp->next;
        delete minp;
    }

    L.setLength(L.length() - 1);

    return min;
}

template <typename T>
bool DeleteS2T(LinkList<T> &L, T s, T t)
{
    if (s > t)
        return false;

    LNode<T> *p = L.getHead(), *q = p->next;
    int count = 0;

    while (q)
    {
        if (q->data >= s && q->data <= t)
        {
            LNode<T> *tmp = q;
            q = q->next;
            p->next = q;
            delete tmp;
        }
        else
        {
            p = q;
            q = q->next;
            count++;
        }
    }

    L.setLength(count);

    return true;
}

// 注意这种方式是不合理的，析构时会因为公共区域被反复释放而报错
template <typename T>
[[deprecated(
    "你不应当使用该函数，其会导致内存重复释放")]] LNode<T> *
Common_Node(const LinkList<T> &L1, const LinkList<T> &L2)
{
    int L1length = L1.length(), L2length = L2.length();
    int k = L1length - L2length;

    LNode<T> *p = L1.getHead()->next, *q = L2.getHead()->next;
    if (k > 0) // L1更长，则先让L1移动k个节点
    {
        while (k--)
        {
            p = p->next;
        }
    }
    else if (k < 0)
    {
        k = -k;
        while (k--)
        {
            q = q->next;
        }
    }

    while (p != NULL || q != NULL)
    {
        if (p == q)
            return p;
        p = p->next;
        q = q->next;
    }

    return nullptr;
}

template <typename T>
void Min_Delete(LinkList<T> &L)
{
    while (L.length())
    {
        LNode<T> *p = L.getHead()->next, *minp = p;
        T min = p->data;

        while (p != NULL)
        {
            if (p->data < min)
            {
                minp = p;
                min = p->data;
            }
            p = p->next;
        }
        cout << min << " ";
        L.DeleteNode(minp);
    }
    cout << endl;
}

// 将两个升序单链表，合并为一个降序单链表
template <typename T>
void Merge_List(LinkList<T> &L1, LinkList<T> &L2)
{
    LNode<T> *head1 = L1.getHead();
    LNode<T> *p = head1->next, *q = L2.getHead()->next;
    head1->next = NULL;
    LNode<T> *tmp;

    while (p != NULL && q != NULL)
    {
        if (p->data < q->data)
        {
            tmp = p->next;
            p->next = head1->next;
            head1->next = p;
            p = tmp;
        }
        else
        {
            tmp = q->next;
            q->next = head1->next;
            head1->next = q;
            q = tmp;
        }
    }

    while (p != NULL)
    {
        tmp = p->next;
        p->next = head1->next;
        head1->next = p;
        p = tmp;
    }

    while (q != NULL)
    {
        tmp = q->next;
        q->next = head1->next;
        head1->next = q;
        q = tmp;
    }

    L1.setLength(L1.length() + L2.length());
    L2.setLength(0);
    L2.getHead()->next = NULL;
}

// 查找两个有序链表中的交集，存入L1
template <typename T>
void Intersection(LinkList<T> &L1, LinkList<T> L2)
{
    LNode<T> *head1 = L1.getHead(), *p = head1->next, *q = L2.getHead()->next;
    LNode<T> *tmp;
    head1->next = NULL;
    int count = 0;

    while (p != NULL && q != NULL)
    {
        if (p->data == q->data)
        {
            tmp = p->next;
            p->next = head1->next;
            head1->next = p;
            p = tmp;
            q = q->next;
            count++;
        }
        else if (p->data < q->data)
        {
            tmp = p;
            p = p->next;
            delete tmp;
        }
        else
        {
            q = q->next;
        }
    }
    L1.setLength(count);
}

// 检查L2是否为L1的子序列
template <typename T>
bool subset(LinkList<T> L1, LinkList<T> L2)
{
    LNode<T> *p = L1.getHead()->next, *q = L2.getHead()->next;
    LNode<T> *tmpp = p;

    bool flag = false;
    while (p != NULL && q != NULL)
    {
        if (p->data == q->data)
        {
            p = p->next;
            q = q->next;
        }
        else
        {
            tmpp = tmpp->next;
            p = tmpp;
            q = L2.getHead()->next;
        }
    }
    if (q == NULL)
        return true;

    return false;
}

// 判断单链表中是否存在环路，有则返回环入口
// 这种函数仅为算法，你若调用说明单链表有错误
template <typename T>
LNode<T> *isLoop(LinkList<T> &L)
{
    LNode<T> *p = L.getHead()->next, *q = L.getHead()->next; // 快慢两个指针
    while (p->next != NULL && q != NULL)
    {
        p = p->next->next;
        q = q->next;

        if (p == q) // 有环，但这不一定是入口
            break;
    }
    if (p == NULL || q == NULL)
        return NULL;

    p = L.getHead()->next;
    /* 解释
	* 设开始结点距环起始点距离为a，快慢指针相遇点距环起始点为x，环长为r，快指针在绕换n圈。
	* 则由速度关系可知，慢指针相遇时走过a+x，快指针速度是其两倍，故为2(a+x)。同时，快指针还走过a+n*r+x，则有等式2(a+x)=a+n*r+x，a=n*r-x。
	* 即开始结点距离环起始点a=n*r-x，那么p指向开始结点，q指向相遇点，两者共同步进，相交时刚好走过a，p指向环起始点。
	*/

    while (p != q)
    {
        p = p->next;
        q = q->next;
    }
    return p;
}

template <typename T>
void Resort(LinkList<T> &L)
{
    LNode<T> *p, *q, *r, *s;
    p = q = L.getHead();
    while (q->next != NULL)
    {
        p = p->next;
        q = q->next;
        if (q->next != NULL)
            q = q->next;
    }
    q = p->next;
    // 此时p 指向中间结点，q为后半段首节点

    // 下面逆置后半段
    p->next = NULL;
    while (q != NULL)
    {
        // 头插法（p当作头结点）
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }

    s = L.getHead()->next; // s指向前半段的第一个数据
    q = p->next;           // q指向后半段的第一个数据
    p->next = NULL;
    while (q != NULL)
    {
        r = q->next; // 记录后半段下一个节点
        q->next = s->next;
        s->next = q;
        s = q->next; // s指向前半段的下一个插入点
        q = r;
    }
}