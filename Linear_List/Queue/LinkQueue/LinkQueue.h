/*************************************************************************
	> File Name: LinkQueue.h
	> Author:
	> Mail:
	> Created Time: Thu Mar 11 11:39:19 2021
 ************************************************************************/
#pragma once
#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H
#include<iostream>
using namespace std;

template<typename T>
struct Node {
public:
	Node(Node<T>* ptr = NULL)
	{
		data = T();
		next = ptr;
	}

	Node(const T& e, Node<T>* ptr = NULL)
	{
		this->data = e;
		this->next = ptr;
	}

	T data;
	Node* next;
};

template<typename T>
class LinkQueue {
	template<typename u>
	friend ostream& operator<<(ostream&, const LinkQueue<u>&);
public:
	LinkQueue();
	LinkQueue(const LinkQueue&);
	bool isEmpty();
	void Push(T);
	T Front();
	T Pop();
	int Length();

private:
	Node<T>* front, * rear;	// front为头指针，rear指向队尾元素
	int length;
};

template<typename T>
LinkQueue<T>::LinkQueue()
{
	front = rear = new Node<T>;
	length = 0;
}

template<typename T>
LinkQueue<T>::LinkQueue(const LinkQueue& Q)
{
	front = rear = new Node<T>;
	Node<T>* qptr = Q.front->next, * ptr = front;
	while (qptr != NULL)
	{
		Node<T>* tmp = new Node<T>(qptr->data);
		ptr->next = tmp;
		ptr = tmp;
		qptr = qptr->next;
	}
	rear = ptr;
	length = Q.length;
}

template<typename T>
bool LinkQueue<T>::isEmpty()
{
	return length == 0;
}

template<typename T>
void LinkQueue<T>::Push(T e)
{
	Node<T>* tmp = new Node<T>(e);
	rear->next = tmp;
	rear = tmp;
	length++;
}

template<typename T>
T LinkQueue<T>::Front()
{
	return front->next->data;
}

template<typename T>
T LinkQueue<T>::Pop()
{
	if (front == rear)
		return T();

	Node<T>* ptr = front->next;
	T tmp = ptr->data;
	front->next = ptr->next;
	delete ptr;
	length--;

	if (length == 0)
		rear = front;

	return tmp;
}

template<typename T>
int LinkQueue<T>::Length()
{
	return length;
}

template<typename T>
ostream& operator<<(ostream& out, const LinkQueue<T>& Q)
{
	Node<T>* ptr = Q.front->next;
	while (ptr != NULL)
	{
		out << ptr->data << " ";
		ptr = ptr->next;
	}
	return out;
}

#endif