/*************************************************************************
	> File Name: SqStack.h
	> Author: Niezl
	> Mail: niezl123@cuc.edu.cn
	> Created Time: Mon Mar 8 08:15:18 2021
 ************************************************************************/
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class SqStack
{
    template <typename u>
    friend ostream &operator<<(ostream &, const SqStack<u> &);

public:
    SqStack();
    SqStack(int size);
    SqStack(const SqStack &);
    ~SqStack();

    bool Empty();
    bool Full();
    void Clear();
    void Push(T);
    bool Pop();
    T Top();

protected:
    T *base;
    T *top; // top指向栈顶的下一位置
    int size;
};

template <typename T>
SqStack<T>::SqStack(int _size)
{
    size = _size;
    base = new T[size];
    top = base;
}

template <typename T>
SqStack<T>::SqStack()
{
    new (this) SqStack(10);
}

template <typename T>
SqStack<T>::SqStack(const SqStack &S)
{
    size = S.size;
    base = new T[size];
    top = S.top;

    for (int i = 0; S.base + i != S.top; i++)
    {
        *(base + i) = *(S.base + i);
    }
}

template <typename T>
SqStack<T>::~SqStack()
{
    top = NULL;
    delete base;
    base = NULL;
    size = 0;
}
template <typename T>
bool SqStack<T>::Empty()
{
    return top - base == 0;
}

template <typename T>
bool SqStack<T>::Full()
{
    return top - base >= size;
}

template <typename T>
void SqStack<T>::Clear()
{
    top = base;
}

template <typename T>
void SqStack<T>::Push(T e)
{
    if (Full()) // 栈满
    {
        T *tmp = base;
        base = new T[size + 10];

        for (int i = 0; tmp + i != top; i++)
        {
            *(base + i) = *(tmp + i);
        }
        top = base + size;
        size += 10;
        delete tmp;
    }
    *top++ = e;
}

template <typename T>
bool SqStack<T>::Pop()
{
    if (Empty()) // 栈空
    {
        return false;
    }
    *--top;
    return true;
}

template <typename T>
T SqStack<T>::Top()
{
    if (Empty()) // 栈空
    {
        return T();
    }
    return *(top - 1);
}

template <typename T>
ostream &operator<<(ostream &out, const SqStack<T> &S)
{
    for (int i = 0; S.base + i != S.top; i++)
    {
        out << S.base[i] << " ";
    }
    return out;
}