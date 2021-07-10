#include "SqList.h"
#include <type_traits>
#include <unordered_map>

template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
bool DeleteMin(SqList<T> &L, T &e)
{
    int Llength = L.length();
    if (Llength == 0)
        return false;

    T min = L[0];
    int index = 0;
    int i;
    for (i = 1; i < Llength; i++)
    {
        if (L[i] < min)
        {
            min = L[i];
            index = i;
        }
    }

    e = min;
    L.Update(index + 1, L[Llength - 1]);
    return true;
}

template <typename T>
void Reverse(SqList<T> &L)
{
    int i = 0;
    T tmp;

    int Llength = L.length();
    for (i = 0; i < Llength / 2; i++)
    {
        tmp = L[i];
        // 注意Update参数为位序，而[]从0开始
        L.Update(i + 1, L[Llength - i - 1]);
        L.Update(Llength - i, tmp);
    }
}

template <typename T>
void RemoveX(SqList<T> &L, T x)
{
    int count = 0;
    int Llength = L.length();
    for (int i = 0; i < Llength; i++)
    {
        if (L[i] != x)
        {
            L.Update(++count, L[i]);
        }
    }
    L.setLength(count);
}

// 删除有序表L中，数值介于[s,t]之间的节点
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
bool RemoveS2T_Sort(SqList<T> &L, T s, T t)
{
    L.Sort(); // 确保L是有序表（这里是升序）
    int Llength = L.length();
    if (Llength == 0 || s >= t)
        return false;

    int s_index = -1, t_index = -1;
    for (int i = 0; i < Llength; i++)
    {
        if (t_index != -1) // 找到t_index可以提前退出
            break;

        if (s_index == -1 && L[i] >= s)
            s_index = i;
        if (t_index == -1 && L[i] >= t)
            t_index = i;
    }

    if (s_index == -1) // 全部小于s
        return true;
    else
    {
        if (t_index == -1) // 全部小于t
            t_index = Llength;
        while (t_index < Llength)
        {
            if (L[t_index] != t)
                L.Update(s_index++ + 1, L[t_index]); // 只有更新后s_index才应该移动
            t_index++;
        }
        L.setLength(s_index);
    }

    return true;
}

// 删除顺序表L中，数值介于[s,t]之间的节点
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
bool RemoveS2T(SqList<T> &L, T s, T t)
{
    // 可以从后往前遍历，并调用Delete函数，但是效率太低
    // 这里我们依旧采取移动的方式进行
    int Llength = L.length();
    if (Llength == 0 || s >= t)
        return false;

    int count = 0;
    for (int i = 0; i < Llength; i++)
    {
        if (L[i] < s || L[i] > t)
        {
            L.Update(++count, L[i]);
        }
    }
    L.setLength(count);

    return true;
}

// 将一个有序表去重
template <typename T>
void Set(SqList<T> &L)
{
    L.Sort();
    int i, Llength = L.length();

    if (Llength <= 1)
        return;

    int count = 1; // 至少有一个元素，所以count从1开始
    for (i = 0; i < Llength; i++)
    {
        if (L[count - 1] != L[i])
        {
            L.Update(++count, L[i]);
        }
    }
    L.setLength(count);
}

// 将两个有序表合并
template <typename T>
SqList<T> Merge(SqList<T> L1, SqList<T> L2)
{
    SqList<T> R;
    int i = 0, j = 0;
    int L1length = L1.length(), L2length = L2.length();
    int count = 0;

    while (i < L1length && j < L2length)
    {
        if (L1[i] < L2[j])
        {
            R.Insert(++count, L1[i]);
            i++;
        }
        else
        {
            R.Insert(++count, L2[j]);
            j++;
        }
    }

    while (i < L1length)
    {
        R.Insert(++count, L1[i++]);
    }

    while (j < L2length)
    {
        R.Insert(++count, L2[j++]);
    }

    R.setLength(count);

    return R;
}

// 将数组/顺序表中第m到n项逆序
template <typename T>
bool Flip(SqList<T> &L, int m, int n)
{
    /*
        第8题调用方法：
        Flip(L,1,m);
        Flip(L,n,Llength);
        Flip(L,1,Llength);
    */
    int Llength = L.length();
    if (m >= n || m < 1 || n > Llength)
        return false;

    T temp;
    for (int i = 0; m + i < n - i; i++)
    {
        temp = L[m + i - 1];
        L.Update(m + i, L[n - i - 1]);
        L.Update(n - i, temp);
    }

    return true;
}

// 在有序表中查找X，若找不到则插入，并保持有序
template <typename T>
bool FindX(SqList<T> &L, T x)
{
    // 折半查找，若没有找到则插入位置为[min](或mid+1||max+1)
    int min = 0, max = L.length() - 1;
    int mid = (max + min) / 2;
    while (min <= max)
    {
        if (L[mid] == x)
            break;
        else if (L[mid] < x)
            min = mid + 1;
        else
            max = mid - 1;
        mid = (max + min) / 2;
    }

    if (L[mid] != x)
    {
        L.Insert(min + 1, x);
        return false;
    }
    else
    {
        if (mid != L.length() - 1)
        {
            T temp = L[mid];
            L.Update(mid + 1, L[mid + 1]);
            L.Update(mid + 2, temp);
        }
    }

    return true;
}

// 将一个数组中的元素循环左移p个位置
template <typename T>
void LShift(SqList<T> &L, int p)
{
    int Llength = L.length();
    p %= Llength; // 因为p = Llength时相当于没变
    if (p == 0)
        return;

    // 调用Flip即可
    Flip(L, 1, p);
    Flip(L, p + 1, Llength);
    Flip(L, 1, Llength);
}

template <typename T>
T Median(SqList<T> L1, SqList<T> L2, int n)
{
    if (L1.length() != n || L2.length() != n) // 要求两个顺序表等长
        return 0;

    int s1 = 0, h1 = n - 1, m1, s2 = 0, h2 = n - 1, m2;
    while (s1 != h1 || s2 != h2) // 最后只剩下一个元素
    {
        m1 = (s1 + h1) / 2;
        m2 = (s2 + h2) / 2;
        if (L1[m1] == L2[m2])
            return L1[m1];

        // L1的中位数小于L2，则舍弃L1的低位和L2的高位
        if (L1[m1] < L2[m2])
        {
            // 奇数（例如11，(0+10)%2==0）
            if ((s1 + h1) % 2 == 0)
            {
                s1 = m1;
                h2 = m2;
            }
            else
            {
                s1 = m1 + 1;
                h2 = m2;
            }
        }
        else
        {
            // L1的中位数大于L2，则舍弃L1的高位和L2的低位
            // 奇数（例如11，(0+10)%2==0）
            if ((s1 + h1) % 2 == 0)
            {
                h1 = m1;
                s2 = m2;
            }
            else
            {
                h1 = m1;
                s2 = m2 + 1;
            }
        }
    }
    return L1[s1] < L2[s2] ? L1[s1] : L2[s2];
}

template <typename T>
T Majority(SqList<T> L)
{
    int Llength = L.length();

    unordered_map<T, int> count;
    for (int i = 0; i < Llength; i++)
        count[L[i]]++;

    int max = 0;
    int major = 0;

    for (auto it : count)
    {
        if (it.second > max)
        {
            max = it.second;
            major = it.first;
        }
    }

    return max > Llength / 2 ? major : -1;
}

template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
T findMissMin(SqList<T>L)
{
    int Llength = L.length();

    T* tmp = new T[Llength]();

    for (int i = 0; i < Llength; i++)
    {
        if (L[i] > 0 && L[i] < Llength)
            tmp[L[i] - 1]++;
    }

    for (int i = 0; i < Llength; i++)
        if (tmp[i] == 0)
            return i + 1;

    return -1;
}