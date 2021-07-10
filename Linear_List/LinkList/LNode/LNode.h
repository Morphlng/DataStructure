/*************************************************************************
	> File Name: LNode.h
	> Author: Niezl
	> Mail: niezl123@cuc.edu.cn
	> Created Time: Wed Feb 24 15:16:10 2021
 ************************************************************************/
#pragma once
#ifndef _LNode_H
#define _LNode_H
#include <iostream>
#include <unordered_map>
using namespace std;

typedef unsigned int uint;

template <typename T>
struct LNode // 节点定义
{
	T data;			 // 数据域
	uint length = 0; // 头节点中用于记录链表长度
	LNode *next;	 // 下一节点

	// 无参构造函数
	LNode(LNode<T> *ptr = NULL)
	{
		this->next = ptr;
	}

	// 含参构造函数
	LNode(const T &e, LNode<T> *ptr = NULL)
	{
		this->data = e;
		this->next = ptr;
	}
};

template <typename T>
class LinkList // 单链表，带头节点
{
	template <typename u>
	friend ostream &operator<<(ostream &, const LinkList<u> &); // 输出运算符重载

public:
	LinkList();
	LinkList(const T &e);
	LinkList(const LinkList<T> &L);
	LinkList<T> &operator=(const LinkList<T> &);
	~LinkList();

	void setLength(uint);
	LNode<T> *getHead();

	// 尾插法建立单链表
	void Build_Rear();

	// 只保留头节点
	void ClearList();

	uint length();
	// 头插法
	bool HeadInsert(T e);
	bool HeadInsert(LNode<T> *);

	// 返回链尾指针
	LNode<T> *GetRear();
	// 尾插法
	bool RearInsert(T e);
	bool RearInsert(LNode<T> *);

	// 在给定节点p之前插入元素
	bool InsertPriorNdoe(LNode<T> *p, T e);
	// 在给定节点p之后插入元素
	bool InsertNextNdoe(LNode<T> *p, T e);
	// 在第i个位置（i>=1）插入x
	bool Insert(uint i, T e);

	// 删除第i个位置的元素（i>=1），赋值给x
	bool Delete(uint i, T &e);
	// 删除指定节点
	bool DeleteNode(LNode<T> *p);

	// 修改第i个位置上的元素（i>=1）
	bool Update(uint i, T e);
	// 返回第i个位置上的元素（i>=1）
	bool GetElem(uint i, T &e);
	// 返回第i个元素的指针（i>=1）
	LNode<T> *Locate(uint i);
	// 返回倒数第i个元素的指针
	LNode<T> *Backwards_K(int i);
	// 返回第i个元素
	T operator[](int i);
	// 查找data为e的节点指针
	LNode<T> *Search(T e);
	// 逆序
	void Reverse();
	// 同样是逆序，可能更好理解
	void Flip();
	// 排序
	void Sort(bool descend = false);
	// 去重
	void Set(bool abs = false);

protected:
	LNode<T> *first; // 头指针，若T为数字型，则头节点存储长度信息
};

template <typename T>
LinkList<T>::LinkList()
{
	first = new LNode<T>;
	first->data = T();
	first->length = 0;
}

template <typename T>
LinkList<T>::LinkList(const T &e)
{
	this->first = new LNode<T>;
	first->data = T();
	first->length = 0;
	HeadInsert(e);
}

template <typename T>
LinkList<T>::LinkList(const LinkList<T> &L)
{
	*this = L;
}

template <typename T>
LinkList<T> &LinkList<T>::operator=(const LinkList<T> &L)
{
	first = new LNode<T>;
	first->data = L.first->data;
	first->length = L.first->length;
	first->next = L.first->next;

	LNode<T> *p = L.first, *q = first;
	while (p->next != NULL)
	{
		p = p->next;
		LNode<T> *tmp = new LNode<T>;
		tmp->data = p->data;
		q->next = tmp;
		q = q->next;
	}
	q->next = NULL;
	return *this;
}

template <typename T>
LinkList<T>::~LinkList()
{
	ClearList();
	if (first != NULL)
		delete first;
	first = NULL;
}

template <typename T>
void LinkList<T>::setLength(uint length)
{
	first->length = length;
}

template <typename T>
LNode<T> *LinkList<T>::getHead()
{
	return first;
}

template <typename T>
void LinkList<T>::ClearList()
{
	LNode<T> *tmp = GetRear();
	while (tmp != first)
	{
		DeleteNode(tmp);
		tmp = GetRear();
	}
	first->data = T();
	first->length = 0;
	first->next = NULL;
}

template <typename T>
uint LinkList<T>::length()
{
	return first->length;
}

template <typename T>
bool LinkList<T>::HeadInsert(T e)
{
	LNode<T> *tmp = new LNode<T>(e);
	if (tmp == NULL)
		return false;

	if (this->first->next != NULL)
	{
		tmp->next = this->first->next;
		this->first->next = tmp;
	}
	else
	{
		this->first->next = tmp;
		tmp->next = NULL;
	}

	++first->length;

	return true;
}

template <typename T>
bool LinkList<T>::HeadInsert(LNode<T> *p)
{
	// 头插法不允许一次性插入多个节点
	if (p == NULL || p->next != NULL)
		return false;

	if (this->first->next != NULL)
	{
		p->next = this->first->next;
		this->first->next = p;
	}
	else
	{
		this->first->next = p;
		p->next = NULL;
	}

	++first->length;

	return true;
}

template <typename T>
LNode<T> *LinkList<T>::GetRear()
{
	LNode<T> *p = first;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

template <typename T>
bool LinkList<T>::RearInsert(T e)
{
	LNode<T> *tmp = new LNode<T>(e);
	if (tmp == NULL)
		return false;

	LNode<T> *p = GetRear();
	p->next = tmp;

	++first->length;

	return true;
}

template <typename T>
bool LinkList<T>::RearInsert(LNode<T> *p)
{
	if (p == NULL)
		return false;

	LNode<T> *tmp = GetRear();
	tmp->next = p;

	int increase = 1; // p->next若不为NULL，则加入不止一个节点
	tmp = p;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		increase++;
	}

	first->length += increase;
	return true;
}

template <typename T>
void LinkList<T>::Build_Rear()
{
	ClearList();

	int i = 0;
	cout << "正在使用尾插法初始化单链表......" << endl;
	while (true)
	{
		T tmp;
		cout << "请输入第" << ++i << "个节点的数据：";
		cin >> tmp;
		RearInsert(tmp);

		char c;
		cout << "是否需要继续添加节点？(Y/N)" << endl;
		cin >> c;
		if (c != 'Y' && c != 'y')
			break;
		cout << endl;
	}
}

template <typename T>
bool LinkList<T>::InsertPriorNdoe(LNode<T> *p, T e)
{
	if (p == NULL)
		return false;

	LNode<T> *tmp = new LNode<T>;
	tmp->data = p->data;
	tmp->next = p->next;
	p->next = tmp;
	p->data = e;

	++first->length;
	return true;
}

template <typename T>
bool LinkList<T>::InsertNextNdoe(LNode<T> *p, T e)
{
	if (p == NULL)
		return false;

	LNode<T> *tmp = new LNode<T>;
	tmp->data = e;
	tmp->next = p->next;
	p->next = tmp;

	++first->length;
	return true;
}

template <typename T>
bool LinkList<T>::Insert(uint i, T e)
{
	if (i < 1 || i > this->length() + 1)
		return false;

	if (i == this->length() + 1)
		RearInsert(e);
	else if (i == 1)
		HeadInsert(e);
	else
	{
		LNode<T> *p = Locate(i - 1);
		if (p != NULL)
			return InsertNextNdoe(p, e);
	}
	return true;
}

template <typename T>
bool LinkList<T>::Delete(uint i, T &e)
{
	if (i < 1 || i > this->length())
		return false;

	LNode<T> *p = this->first, *tmp;
	if (i == 1)
	{
		tmp = p->next;
		e = tmp->data;
		p->next = tmp->next;
		delete tmp;
	}
	else
	{
		p = Locate(i - 1);
		tmp = p->next;
		p->next = tmp->next;
		e = tmp->data;
		delete tmp;
	}

	--first->length;

	return true;
}

template <typename T>
bool LinkList<T>::DeleteNode(LNode<T> *p)
{
	if (p == NULL)
		return false;

	if (p->next == NULL)
	{
		T temp;
		return Delete(first->length, temp);
	}

	LNode<T> *tmp = p->next;
	p->data = tmp->data;
	p->next = tmp->next;
	delete tmp;

	--first->length;

	return true;
}

template <typename T>
bool LinkList<T>::Update(uint i, T e)
{
	if (i < 1 || i > this->length())
		return false;

	LNode<T> *p = first;
	while (i > 0)
	{
		p = p->next;
		i--;
	}
	p->data = e;

	return true;
}

template <typename T>
bool LinkList<T>::GetElem(uint i, T &e)
{
	if (i < 1 || i > this->length())
		return false;

	LNode<T> *p = first;
	while (i > 0)
	{
		p = p->next;
		i--;
	}
	e = p->data;

	return true;
}

template <typename T>
LNode<T> *LinkList<T>::Locate(uint i)
{
	if (i < 1 || i > this->length())
		return NULL;

	LNode<T> *p = first;
	while (i > 0)
	{
		p = p->next;
		i--;
	}

	return p;
}

template <typename T>
LNode<T> *LinkList<T>::Backwards_K(int k)
{
	if (k > 0 || -k > first->length)
		return NULL;

	k = -k;
	LNode<T> *p = first->next, *q = first->next;
	while (k--)
	{
		p = p->next; // 前面已经判断过k的合法性了，不用判断p==NULL
	}

	while (p != NULL)
	{
		q = q->next;
		p = p->next;
	}

	return q;
}

template <typename T>
T LinkList<T>::operator[](int i)
{
	LNode<T> *tmp;
	if (i >= 0)
	{
		tmp = Locate(i + 1);
		if (tmp)
			return tmp->data;
	}
	else
	{
		tmp = Backwards_K(i);
		if (tmp)
			return tmp->data;
	}
	return T();
}

template <typename T>
LNode<T> *LinkList<T>::Search(T e)
{
	LNode<T> *p = first->next;
	while (p != NULL)
	{
		if (p->data == e)
			return p;
		p = p->next;
	}
	return NULL;
}

template <typename T>
void LinkList<T>::Reverse()
{
	if (first->length <= 1)
		return;

	LNode<T> *s = first;
	LNode<T> *p = s->next;
	LNode<T> *t = p->next;

	while (t != NULL)
	{
		p->next = s;
		s = p;
		p = t;
		t = t->next;
	}

	p->next = s;
	first->next->next = NULL; // 删除原本的头节点
	first->next = p;		  // 将头节点指向原本的链尾节点
}

template <typename T>
void LinkList<T>::Flip()
{
	if (first->length <= 1)
		return;

	// p指向开始元素之后的元素（第二个）
	LNode<T> *p = first->next->next, *q;
	// 将原链表一分为二（first与第一个元素 和 p）
	first->next->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		q->next = first->next; // 将元素按头插法加入
		first->next = q;
	}
}

template <typename T>
void LinkList<T>::Sort(bool descend)
{
	LNode<T> *p, *q, *insert;
	p = first->next, q = p->next;
	p->next = NULL;
	p = q; // 从第二个节点开始插入

	while (p) // 直接插入排序
	{
		q = p->next;
		insert = first;
		if (!descend)
			while (insert->next != NULL && insert->next->data < p->data)
				insert = insert->next;
		else
			while (insert->next != NULL && insert->next->data > p->data)
				insert = insert->next;

		p->next = insert->next;
		insert->next = p;
		p = q;
	}
}

template <typename T>
void LinkList<T>::Set(bool abs)
{
	unordered_map<T, int> tmp;
	LNode<T> *p = first->next;
	LNode<T> *pre = first;
	T val;

	while (p != NULL)
	{
		if (abs)
			val = p->data >= 0 ? p->data : -p->data;
		else
			val = p->data;

		tmp[val]++;
		if (tmp[val] > 1)
		{
			pre->next = p->next;
			delete p;
			first->length--;
			p = pre->next;
		}
		else
		{
			p = p->next;
			pre = pre->next;
		}
	}
}

template <typename T>
ostream &operator<<(ostream &out, const LinkList<T> &L)
{
	LNode<T> *p = L.first->next;
	while (p != NULL)
	{
		out << p->data << " ";
		p = p->next;
	}
	return out;
}

#endif
