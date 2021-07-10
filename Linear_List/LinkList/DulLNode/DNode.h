/*************************************************************************
	> File Name: DNode.h
	> Author:
	> Mail:
	> Created Time: Wed Feb 24 15:23:33 2021
 ************************************************************************/
#pragma once
#ifndef _DNode_H
#define _DNode_H
#include <iostream>
using namespace std;

typedef unsigned int uint;

template <typename T>
struct DNode // 节点定义
{
	T data;			 // 数据域
	uint length = 0; // 头节点中用于记录链表长度
	DNode* prior;	 // 前一节点
	DNode* next;		 // 下一节点

	// 无参构造函数
	DNode(DNode<T>* next = NULL, DNode<T>* prior = NULL)
	{
		this->data = T();
		this->next = next;
		this->prior = prior;
	}

	// 含参构造函数
	DNode(const T& e, DNode<T>* next = NULL, DNode<T>* prior = NULL)
	{
		this->data = e;
		this->next = next;
		this->prior = prior;
	}
};

template <typename T>
class DLinkList // 双向循环链表，带头结点
{
	template <typename u>
	friend ostream& operator<<(ostream&, const DLinkList<u>&); // 输出运算符重载

public:
	DLinkList();
	DLinkList(const T& e);
	DLinkList(const DLinkList<T>& L);
	DLinkList& operator=(const DLinkList<T>& L);
	~DLinkList();

	DNode<T>* getHead();
	void setLength(uint length);

	// 尾插法建立单链DLinkList表
	void Build_Rear();

	// 只保留头节点
	void ClearList();

	uint length();
	// 头插法
	bool HeadInsert(T e);
	bool HeadInsert(DNode<T>*);
	// 尾插法
	bool RearInsert(T e);
	bool RearInsert(DNode<T>*);

	// 在p节点后插入s节点
	bool InsertNextNode(DNode<T>* p, DNode<T>* s);
	// 在p节点前插入s节点
	bool InsertPriorNode(DNode<T>* p, DNode<T>* s);
	// 按位序插入
	bool InsertNode(uint i, T e);

	// 删除p节点
	bool DeleteNode(DNode<T>* p);
	// 删除第i个节点，返回给e
	bool DeleteNode(uint i, T& e);

	// 更新第i个节点的值
	bool Update(uint i, T e);

	// 返回第i个位置上的元素（i>=1）
	bool GetElem(uint i, T& e);
	// 返回第i个元素的指针（i>=1）
	DNode<T>* Locate(uint i);
	// 返回第i个元素的指针（i>=1）
	DNode<T>* operator[](uint i);
	// 查找data为e的节点指针
	DNode<T>* Search(T e);

protected:
	DNode<T>* first;
};

template <typename T>
DLinkList<T>::DLinkList()
{
	first = new DNode<T>;
	first->data = T();
	first->prior = first;
	first->next = first;
}

template <typename T>
DLinkList<T>::DLinkList(const T& e)
{
	first = new DNode<T>;
	first->data = T();
	HeadInsert(e);
}

template <typename T>
DLinkList<T>::DLinkList(const DLinkList<T>& L)
{
	*this = L;
}

template <typename T>
DLinkList<T>& DLinkList<T>::operator=(const DLinkList<T>& L)
{
	first = new DNode<T>;
	first->data = L.first->data;
	first->length = L.first->length;
	first->next = first;
	first->prior = first;

	DNode<T>* p = L.first, * q = first;

	while (p->next != L.first)
	{
		p = p->next;
		DNode<T>* tmp = new DNode<T>;
		tmp->data = p->data;
		tmp->prior = q;
		q->next = tmp;
		q = q->next;
	}
	q->next = first;
	first->prior = q;
	return *this;
}

template <typename T>
DLinkList<T>::~DLinkList()
{
	ClearList();
	if (first != NULL)
		delete first;
	first = NULL;
}

template<typename T>
DNode<T>* DLinkList<T>::getHead()
{
	return first;
}

template<typename T>
void DLinkList<T>::setLength(uint length)
{
	first->length = length;
}

template <typename T>
void DLinkList<T>::Build_Rear()
{
	ClearList();

	int i = 0;
	cout << "正在使用尾插法初始化双向循环链表......" << endl;
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
void DLinkList<T>::ClearList()
{
	DNode<T>* tmp = first->next;
	while (tmp != first && tmp != NULL)
	{
		tmp = tmp->next;
		DeleteNode(tmp->prior);
	}
	first->data = T();
	first->next = first;
	first->prior = first;
	first->length = 0;
}

template <typename T>
uint DLinkList<T>::length()
{
	return first->length;
}

template <typename T>
bool DLinkList<T>::HeadInsert(T e)
{
	DNode<T>* p = new DNode<T>;
	if (p == NULL)
		return false;

	p->data = e;

	if (first->next == first)
	{
		first->next = p;
		first->prior = p;
		p->next = first;
		p->prior = first;
	}
	else
	{
		p->next = first->next;
		first->next->prior = p;
		p->prior = first;
		first->next = p;
	}

	++first->length;

	return true;
}

template <typename T>
bool DLinkList<T>::HeadInsert(DNode<T>* s)
{
	if (s == NULL)
		return false;

	if (first->next == first)
	{
		first->next = s;
		first->prior = s;
		s->next = first;
		s->prior = first;
	}
	else
	{
		s->next = first->next;
		first->next->prior = s;
		s->prior = first;
		first->next = s;
	}

	++first->length;

	return true;
}

template <typename T>
bool DLinkList<T>::RearInsert(T e)
{
	DNode<T>* p = new DNode<T>;
	if (!p)
		return false;

	p->data = e;

	if (first->prior == first)
	{
		first->prior = p;
		first->next = p;
		p->next = first;
		p->prior = first;
	}
	else
	{
		p->next = first;
		p->prior = first->prior;
		first->prior->next = p;
		first->prior = p;
	}

	++first->length;

	return true;
}

template <typename T>
bool DLinkList<T>::RearInsert(DNode<T>* s)
{
	if (s == NULL)
		return false;

	if (first->prior == first)
	{
		first->prior = s;
		first->next = s;
		s->next = first;
		s->prior = first;
	}
	else
	{
		s->next = first;
		s->prior = first->prior;
		first->prior->next = s;
		first->prior = s;
	}

	++first->length;

	return true;
}

template <typename T>
bool DLinkList<T>::InsertNextNode(DNode<T>* p, DNode<T>* s)
{
	if (p == NULL || s == NULL)
		return false;

	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	++first->length;

	return true;
}

template <typename T>
bool DLinkList<T>::InsertPriorNode(DNode<T>* p, DNode<T>* s)
{
	if (p == NULL || s == NULL)
		return false;

	return InsertNextNode(p->prior, s);
}

template <typename T>
bool DLinkList<T>::InsertNode(uint i, T e)
{
	if (i<1 || i>first->length + 1)
		return false;

	DNode<T>* tmp = first;
	while (--i)
	{
		tmp = tmp->next;
	}

	DNode<T>* s = new DNode<T>(e);

	return InsertNextNode(tmp, s);
}

template <typename T>
bool DLinkList<T>::DeleteNode(DNode<T>* p)
{
	if (p == NULL)
		return false;

	p->prior->next = p->next;
	p->next->prior = p->prior;
	delete p;
	p = NULL;
	--first->length;

	return true;
}

template <typename T>
bool DLinkList<T>::DeleteNode(uint i, T& e)
{
	if (i<1 || i>first->length)
		return false;

	DNode<T>* tmp = first;
	while (i--)
		tmp = tmp->next;

	e = tmp->data;

	return DeleteNode(tmp);
}

template <typename T>
DNode<T>* DLinkList<T>::Locate(uint i)
{
	if (i<1 || i>first->length)
		return NULL;

	DNode<T>* p = first;
	while (i--)
	{
		p = p->next;
	}
	return p;
}

template <typename T>
bool DLinkList<T>::Update(uint i, T e)
{
	if (i<1 || i>first->length)
		return false;

	DNode<T>* p = Locate(i);
	p->data = e;
	return true;
}

template <typename T>
bool DLinkList<T>::GetElem(uint i, T& e)
{
	if (i<1 || i>first->length)
		return false;

	DNode<T>* p = Locate(i);
	e = p->data;
	return true;
}

template <typename T>
DNode<T>* DLinkList<T>::operator[](uint i)
{
	return Locate(i);
}

template <typename T>
DNode<T>* DLinkList<T>::Search(T e)
{
	DNode<T>* p = first->next;
	while (p != first && first != NULL)
	{
		if (p->data == e)
			return p;
		p = p->next;
	}
	return NULL;
}

template <typename u>
ostream& operator<<(ostream& out, const DLinkList<u>& L)
{
	DNode<u>* p = L.first;
	while (p->next != L.first)
	{
		p = p->next;
		out << p->data << " ";
	}
	return out;
}

#endif
