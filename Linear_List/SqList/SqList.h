/*************************************************************************
    > File Name: SqList.h
    > Author: Niezl
    > Mail: niezl123@cuc.edu.cn
    > Created Time: Wed Feb 24 09:25:16 2021
 ************************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;

typedef unsigned int uint;

template <typename T>
class SqList
{
    template <typename u>
    friend ostream& operator<<(ostream&, const SqList<u>&); // 输出运算符重载

public:
    SqList();
    SqList(uint size);
    SqList(const SqList&);
    SqList& operator=(const SqList&);
    void InitList(uint size);
    void setLength(uint length);
    void ClearList();
    ~SqList();

    // 初始赋值
    void Build();

    // 获取顺序表最大长度
    int size();

    // 获得顺序表当前长度
    int length();

    bool Empty();

    // 定位
    int LocateElem(T e);

    // 得到i位元素（负数则从后往前）
    bool GetElem(int i, T& e);

    // 得到下标i处元素
    T operator[](int i);

    // 指定位置插入（注意这里i是位序，即从1开始）
    bool Insert(uint i, T e);

    // 指定位置删除，将删除值赋给e
    bool Delete(uint i, T& e);

    // 修改指定位置的值
    bool Update(uint i, T e);

    // 排序
    void Sort(bool descend = false);

    // 去重
    void Set();

private:
    T* elem;
    uint _size;
    uint _length;
};

template <typename T>
ostream& operator<<(ostream& out, const SqList<T>& L)
{
    for (uint i = 0; i < L._length; i++)
    {
        out << L.elem[i] << " ";
    }
    return out;
}

template <typename T>
SqList<T>::SqList()
{
    InitList(10);
}

template <typename T>
SqList<T>::SqList(uint size)
{
    InitList(size);
}

template <typename T>
SqList<T>::SqList(const SqList& L)
{
    *this = L;
}

template <typename T>
SqList<T>& SqList<T>::operator=(const SqList& L)
{
    _length = L._length;
    _size = L._size;
    elem = new T[L._size];
    for (int i = 0; i < _length; i++)
    {
        elem[i] = L.elem[i];
    }

    return *this;
}

template <typename T>
void SqList<T>::InitList(uint size)
{
    if (size < 1)
        size = 10;
    _size = size;
    _length = 0;
    elem = new T[_size];
    for (uint i = 0; i < _size; i++)
        elem[i] = T();
}

template <typename T>
void SqList<T>::setLength(uint length)
{
    _length = length;
}

template <typename T>
void SqList<T>::Build()
{
    ClearList();
    int i = 0;
    while (true)
    {
        T e;
        cout << "请输入第" << ++i << "个数据：" << endl;
        cin >> e;
        Insert(i, e);

        char choose;
        cout << "是否还要继续加入？Y/N" << endl;
        cin >> choose;
        if (choose != 'Y' && choose != 'y')
            break;
    }
}

template <typename T>
void SqList<T>::ClearList()
{
    _length = 0;
}

template <typename T>
SqList<T>::~SqList()
{
    ClearList();
    delete[] elem;
    elem = NULL;
}

template <typename T>
bool SqList<T>::Empty()
{
    return 0 == _length;
}

template <typename T>
int SqList<T>::size()
{
    return _size;
}

template <typename T>
int SqList<T>::length()
{
    return _length;
}

template <typename T>
int SqList<T>::LocateElem(T e)
{
    for (uint i = 0; i < _length; i++)
    {
        if (elem[i] == e)
            return i;
    }
    return -1;
}

template <typename T>
bool SqList<T>::GetElem(int i, T& e)
{
    if (i < 0)
    {
        if (-i > _length)
            return false;
        e = elem[_length + i];
    }
    else
    {
        if (_length <= i)
            return false;
        e = elem[i];
    }
    return true;
}

template <typename T>
T SqList<T>::operator[](int i)
{
    T e;
    if (GetElem(i, e))
        return e;
    return T();
}

template <typename T>
bool SqList<T>::Insert(uint i, T e)
{
    if (i < 1 || i > _length + 1) // 由于是位序，所以从1开始
        return false;

    if (_length >= _size)
    {
        T* p = elem;
        elem = new T[_size + 10];
        for (uint i = 0; i < _length; i++)
        {
            elem[i] = p[i];
        }
        _size += 10;
        delete[] p;
    }

    T* q = &(elem[i - 1]); // 指向插入位置
    if (_length > 0)
    {
        for (T* p = &(elem[_length - 1]); p >= q; --p) // 插入位置以后元素后移
        {
            *(p + 1) = *p;
        }
    }
    *q = e;
    ++_length;
    return true;
}

template <typename T>
bool SqList<T>::Delete(uint i, T& e)
{
    if (i < 1 || i > _length)
        return false;

    T* q = &(elem[i - 1]); // 指向删除位置
    e = *q;
    for (++q; q <= &(elem[_length - 1]); ++q) // 删除位置以后元素前移
    {
        *(q - 1) = *q;
    }
    --_length;
    return true;
}

template <typename T>
bool SqList<T>::Update(uint i, T e)
{
    if (i < 1 || i > _length)
        return false;
    T* p = &(elem[i - 1]);
    *p = e;
    return true;
}

template <typename T>
void SqList<T>::Sort(bool descend)
{
    int i, j;
    T temp;

    for (i = 0; i < _length; i++)
    {
        bool flag = false;
        for (j = 0; j < _length - i - 1; j++)
        {
            if (descend)
            {
                if (elem[j] < elem[j + 1])
                {
                    temp = elem[j];
                    elem[j] = elem[j + 1];
                    elem[j + 1] = temp;
                    flag = true;
                }
            }
            else
            {
                if (elem[j] > elem[j + 1])
                {
                    temp = elem[j];
                    elem[j] = elem[j + 1];
                    elem[j + 1] = temp;
                    flag = true;
                }
            }

        }
        if (!flag)
            break;
    }

}

template <typename T>
void SqList<T>::Set()
{
    if (_length <= 1)
        return;

    T* tmp = new T[_length];
    tmp[0] = elem[0];
    int count = 1;

    for (int i = 1; i < _length; i++)
    {
        bool duplicate = false;
        for (int j = 0; j < count; j++)
        {
            if (tmp[j] == elem[i])
            {
                duplicate = true;
                break;
            }
        }
        if (!duplicate)
        {
            tmp[count++] = elem[i];
        }
    }

    for (int i = 0; i < count; i++)
    {
        elem[i] = tmp[i];
    }

    _length = count;
    delete[] tmp;
}