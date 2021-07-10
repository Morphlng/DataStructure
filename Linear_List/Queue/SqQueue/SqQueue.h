/*************************************************************************
	> File Name: SqQueue.h
	> Author: Niezl
	> Mail: niezl123@cuc.edu.cn
	> Created Time: Mon Mar 8 15:05:45 2021
 ************************************************************************/
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class SqQueue
{
    template <typename u>
    friend ostream &operator<<(ostream &, const SqQueue<u>);

public:
    SqQueue();
    SqQueue(int);
    SqQueue(const SqQueue &);
    ~SqQueue();
    bool Full();
    bool Empty();
    int length();

    void Push(T e);
    bool Pop();
    T Front();

protected:
    T *base;
    int front;
    int rear;
    int max_size;
};

template <typename T>
SqQueue<T>::SqQueue(int size)
{
    max_size = size;
    base = new T[size];
    front = rear = 0; // 不一定设初值为0
}

template <typename T>
SqQueue<T>::SqQueue()
{
    new (this) SqQueue(10);
}

template <typename T>
SqQueue<T>::SqQueue(const SqQueue &q)
{
    max_size = q.max_size;
    base = new T[max_size];
    for (int i = q.front; i != q.rear; i = (i + 1) % q.max_size)
    {
        base[i] = q.base[i];
    }
    front = q.front;
    rear = q.rear;
}

template <typename T>
SqQueue<T>::~SqQueue()
{
    front = rear = max_size = 0;
    delete base;
}

template <typename T>
bool SqQueue<T>::Full()
{
    // 采用牺牲一个单元的方法来判满
    return (rear + 1) % max_size == front;
}

template <typename T>
bool SqQueue<T>::Empty()
{
    return front == rear;
}

template <typename T>
int SqQueue<T>::length()
{
    return (rear + max_size - front) % max_size;
}

template <typename T>
void SqQueue<T>::Push(T e)
{
    if (Full())
    {
        T *tmp = base;
        base = new T[max_size + 10];
        for (int i = front; i != rear; i = (i + 1) % max_size)
            base[i] = tmp[i];

        max_size += 10;
        delete tmp;
    }
    base[rear] = e;
    rear = (rear + 1) % max_size;
}

template <typename T>
bool SqQueue<T>::Pop()
{
    if (Empty())
        return false;

    front = (front + 1) % max_size;
    return true;
}

template <typename T>
T SqQueue<T>::Front()
{
    if (Empty())
        return T();
    return base[front];
}

template <typename u>
ostream &operator<<(ostream &out, const SqQueue<u> Q)
{
    for (int i = Q.front; i != Q.rear; i = (i + 1) % Q.max_size)
        out << Q.base[i] << " ";

    return out;
}
