#include <iostream>
using namespace std;

struct Elem
{
    int no;     // 记录n
    double val; // 记录第n次递归时的值
};

double P(int n, double x)
{
    Elem *stack = new Elem[n];
    double result;
    int i, top = -1, p0 = 1, p1 = 2 * x; // 记录初值

    for (i = n; i >= 2; i--)
    {
        stack[++top].no = i;
    }
    while (top != -1)
    {
        stack[top].val = 2 * x * p1 - 2 * (stack[top].no - 1) * p0;
        p0 = p1;
        p1 = stack[top].val;
        top--;
    }

    if (n == 0)
        return p0;
    else
        return p1;
}

int main()
{
    cout << P(1, 2) << endl;
    return 0;
}