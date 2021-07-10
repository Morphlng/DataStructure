#include <iostream>
#include <type_traits>

using std::cout;
using std::enable_if_t;
using std::endl;
using std::is_arithmetic;

// 用来将数组逆序（升序-降序）
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void Reverse(T A[], int n)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        T tmp = A[low];
        A[low++] = A[high];
        A[high--] = tmp;
    }
}

// 插入排序的特点是每一趟排序过后，元素不一定在其最终位置
// 但是会保持前部有序（直接插入、折半插入）
#pragma region 插入排序

// 插入排序，数组大小为n
// 空间复杂度O(1)，时间复杂度O(n^2)，稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void InsertSort(T A[], int n, bool descend = false)
{
    int i, j;
    T tmp;

    for (i = 1; i < n; i++)
    {
        if (A[i] < A[i - 1])
        {
            tmp = A[i];
            // 将比当前元素大的后移
            for (j = i - 1; j >= 0 && A[j] > tmp; j--)
                A[j + 1] = A[j];

            // 插入当前元素
            A[j + 1] = tmp;
        }
    }
    // 降序
    if (descend)
        Reverse(A, n);
}

// 折半插入排序，数组大小为n
// 该优化只是将查找的时间复杂度降低为O(nlogn)，对整体没变化
// 空间复杂度O(1)，时间复杂度O(n^2)，稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void BiInsertSort(T A[], int n, bool descend = false)
{
    int i, j, low, high, mid;
    T tmp;

    for (i = 1; i < n; i++)
    {
        tmp = A[i];
        low = 0, high = i - 1;
        // 折半查找插入位置
        while (low <= high)
        {
            mid = (low + high) >> 1;
            if (A[mid] > tmp)
                high = mid - 1;
            else
                low = mid + 1;
        }
        // 将大于当前关键字的元素后移
        for (j = i - 1; j >= low; j--)
            A[j + 1] = A[j];
        A[low] = tmp;
    }

    // 降序
    if (descend)
        Reverse(A, n);
}

// 希尔排序，数组大小为n
// 空间复杂度O(1)，最坏情况下(d=1)时间复杂度O(n^2)，不稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void ShellSort(T A[], int n, bool descend = false)
{
    int d, i, j;
    T tmp;
    for (d = n >> 1; d >= 1; d >>= 1) // 步长，每次取1/2
    {
        for (i = d; i < n; i++) // 处理每个子表
        {
            if (A[i] < A[i - d])
            {
                tmp = A[i];
                for (j = i - d; j >= 0 && A[j] > tmp; j -= d)
                    A[j + d] = A[j];
                A[j + d] = tmp;
            }
        }
    }

    // 降序
    if (descend)
        Reverse(A, n);
}

#pragma endregion

// 交换排序每一趟结束后，都会“使”一个元素在其最终位置
// 可以据此判断一个序列是否为交换排序的中间过程
#pragma region 交换排序
// 冒泡排序，数组大小为n
// 空间复杂度O(1)，时间复杂度O(n^2)，稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void BubbleSort(T A[], int n, bool descend = false)
{
    int i, j;
    T tmp;
    for (i = 0; i < n; i++)
    {
        bool flag = false; // 如果一次比较没有发生交换，可以提前终止
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag)
            break;
    }

    // 降序
    if (descend)
        Reverse(A, n);
}

// 双向起泡法
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void DulBubbleSort(T A[], int n, bool descend = false)
{
    int low = 0, high = n - 1;
    T tmp;
    bool flag = true;
    while (low < high && flag)
    {
        flag = false;
        for (int i = low; i < high; i++)
        {
            if (A[i] > A[i + 1])
            {
                tmp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = tmp;
                flag = true;
            }
        }
        high--; // 确定了一个最大值
        for (int j = high; j > low; j--)
        {
            if (A[j] < A[j - 1])
            {
                tmp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = tmp;
                flag = true;
            }
        }
        low++; // 确定了一个最小值
    }

    // 降序
    if (descend)
        Reverse(A, n);
}

// 快速排序，一次划分
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
int Partition(T A[], int low, int high)
{
    T pivot = A[low];
    while (low < high)
    {
        while (low < high && A[high] >= pivot)
            high--;
        A[low] = A[high];
        while (low < high && A[low] <= pivot)
            low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low; // 返回时low=high=锚点位置
}

// 快速排序
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void QSort(T A[], int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(A, low, high); // 划分
        QSort(A, low, pivot - 1);            // 处理左子表
        QSort(A, pivot + 1, high);           // 处理右子表
    }
}

// 快速排序调用，数组大小为n
// 空间复杂度O(logn)，时间复杂度为O(nlogn)，不稳定
// 空间复杂度即为递归层数，为树的高度，最好情况logn（每次划分均匀），最坏情况n（原本有序，不论正序逆序）
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void QuickSort(T A[], int n, bool descend = false)
{
    QSort(A, 0, n - 1);

    // 降序
    if (descend)
        Reverse(A, n);
}

#pragma endregion

// 同交换排序，每一趟结束后都会“使”一个元素在其最终位置
#pragma region 选择排序
// 选择排序
// 空间复杂度O(1)，时间复杂度O(n^2)，不稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void SelectSort(T A[], int n, bool descend = false)
{
    int i, j, mindex;
    for (i = 0; i < n; i++)
    {
        mindex = i;
        for (j = i; j < n; j++)
            if (A[j] < A[mindex])
                mindex = j;

        if (mindex != i)
        {
            T tmp = A[i];
            A[i] = A[mindex];
            A[mindex] = tmp;
        }
    }

    // 降序
    if (descend)
        Reverse(A, n);
}

// 一次大根堆调整
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void MaxHeapAdjust(T A[], int k, int len)
{
    T tmp = A[k];
    for (int i = 2 * (k + 1) - 1; i < len; i = 2 * (i + 1) - 1)
    {
        if (i < len - 1 && A[i] < A[i + 1]) // 如果存在右孩子且右孩子更大，则指向右孩子
            i++;
        if (tmp >= A[i]) // 如果根比左右孩子都大，则不用调整
            break;
        else // 否则将根与较大的孩子交换
        {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = tmp;
}

// 创建大根堆
// 建堆的时间复杂度为O(n)
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void BuildMaxHeap(T A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapAdjust(A, i, n);
}

// 一次小根堆调整
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void MinHeapAdjust(T A[], int k, int len)
{
    T tmp = A[k];
    for (int i = 2 * (k + 1) - 1; i < len; i = 2 * (i + 1) - 1)
    {
        if (i < len - 1 && A[i] > A[i + 1]) // 如果存在右孩子且右孩子更小，则指向右孩子
            i++;
        if (tmp <= A[i]) // 如果根比左右孩子都小，则不用调整
            break;
        else // 否则将根与较大的孩子交换
        {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = tmp;
}

// 创建小根堆
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void BuildMinHeap(T A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        MinHeapAdjust(A, i, n);
}

// 堆排序
// 空间复杂度O(1)，时间复杂度O(nlogn)，不稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void HeapSort(T A[], int n, bool descend = false)
{
    if (descend)
        BuildMinHeap(A, n); // 先将原始序列转为小根堆
    else
        BuildMaxHeap(A, n); // 先将原始序列转为大根堆

    // 每次取最大(小)的（第一个）元素与末尾元素交换，然后再次HeapAdjust
    for (int i = n - 1; i >= 0; i--)
    {
        T tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        if (descend)
            MinHeapAdjust(A, 0, i); // 注意因为我这里下标从0开始，所以相当于已经将表长-1
        else
            MaxHeapAdjust(A, 0, i);
    }
}
#pragma endregion

#pragma region 归并排序
// 归并
// low-mid为一个子序列，mid+1-high为另一个子序列（high保证不越界）
// 将两个子序列合并后放置于A数组，B数组用来做中转
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void Merge(T A[], T B[], int low, int mid, int high)
{
    int i, j, k;
    // 把A数组里的值复制到B数组
    for (k = low; k <= high; k++)
        B[k] = A[k];

    // 排序，<=保证了稳定性
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
        A[k] = (B[i] <= B[j]) ? B[i++] : B[j++];

    // 如果左子序列尚未完毕
    while (i <= mid)
        A[k++] = B[i++];

    // 如果右子序列尚未完毕
    while (j <= high)
        A[k++] = B[j++];
}

// 归并排序递归过程
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void MSort(T A[], T B[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) >> 1;
        MSort(A, B, low, mid);
        MSort(A, B, mid + 1, high);
        Merge(A, B, low, mid, high);
    }
}

// 归并排序
// 归并排序在形态上是一棵倒立的二叉树，每一趟排序O(n)，共logn趟
// 空间复杂度O(n)，时间复杂度O(nlogn)，稳定
template <typename T, typename = enable_if_t<is_arithmetic<T>::value>>
void MergeSort(T A[], int n, bool descend = false)
{
    T B[n]{0};
    MSort(A, B, 0, n - 1);

    // 降序
    if (descend)
        Reverse(A, n);
}
#pragma endregion
