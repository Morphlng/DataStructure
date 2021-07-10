#include <iostream>
#include <type_traits>

using std::cout;
using std::enable_if_t;
using std::is_arithmetic;

// 求一个数组中第k小元素
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
T QuickSelect(T a[], int s, int t, int k)
{
    int i = s, j = t;
    T tmp;
    if (s < t)
    {
        tmp = a[s];
        while (i != j) //从区间两端交替向中间扫描，直至i=j为止
        {
            while (j > i && a[j] >= tmp)
                j--;
            a[i] = a[j]; //将a[j]前移到a[i]的位置
            while (i < j && a[i] <= tmp)
                i++;
            a[j] = a[i]; //将a[i]后移到a[j]的位置
        }
        a[i] = tmp;
        if (k - 1 == i) // 恰好是第k小
            return a[i];
        else if (k - 1 < i)
            return QuickSelect(a, s, i - 1, k); //在左区间中递归查找
        else
            return QuickSelect(a, i + 1, t, k); //在右区间中递归查找
    }
    else if (s == t && s == k - 1) //区间内只有一个元素且为a[k-1]
        return a[k - 1];

    return -1; // 找不到第k小
}