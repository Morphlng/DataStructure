#include "DString.h"

DString concat(const DString &s1, const DString &s2)
{
    DString result(s1.length + s2.length);
    int i, j;
    for (i = 1; i <= s1.length; i++)
        result.ch[i] = s1.ch[i];

    for (j = 1; j <= s2.length; j++)
        result.ch[i++] = s2.ch[j];

    return result;
}

// 朴素模式匹配算法
int Index(const DString &s1, const DString &s2)
{
    int k = 1; // 记录匹配开始位置
    int i = k, j = 1;
    while (i <= s1.length && j <= s2.length)
    {
        if (s1.ch[i] == s2.ch[j])
            i++, j++;
        else
            i = ++k, j = 1; // 可以省略k，让i=i-(j-1)+1=i-j+2
    }
    if (j > s2.length)
        return k;
    else
        return -1;
}

// kmp算法中求nextval数组
// 考研考手算next, nextval
int *cal_nextval(const DString &s2)
{
    int *nextval = new int[s2.length + 1];
    // 对于第j个字符
    // next[j] = S的最长相等前后缀长度 + 1
    // 特别的，next[1] = 0；next[2] = 1
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < s2.length)
    {
        if (j == 0 || s2.ch[i] == s2.ch[j])
        {
            i++, j++;
            nextval[i] = j;
        }
        else
            j = nextval[j];
    }

    // 进一步优化，得到nextval数组
    for (i = 2; i <= s2.length; i++)
    {
        if (s2.ch[i] == s2.ch[nextval[i]])
            nextval[i] = nextval[nextval[i]];
    }

    return nextval;
}

// kmp算法
int Index_kmp(const DString &s1, const DString &s2)
{
    int *nextval = cal_nextval(s2);

    int i = 1, j = 1;
    while (i <= s1.length && j <= s2.length)
    {
        if (j == 0 || s1.ch[i] == s2.ch[j])
            j++, i++;
        else
            j = nextval[j];
    }

    if (j > s2.length)
        return i - s2.length;
    else
        return -1;
}

int main()
{
    DString A("adefababaac"), B("ababaa");

    cout << Index_kmp(A, B) << endl;
    cout << Index(A, B) << endl;
    cout << A.IndexOf(B) << endl;

    return 0;
}