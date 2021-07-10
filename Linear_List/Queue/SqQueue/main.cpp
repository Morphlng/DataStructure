#include "SqQueue.h"

int main()
{
    SqQueue<int> Q1;
    Q1.Push(1);
    Q1.Push(2);
    Q1.Push(3);
    Q1.Push(4);
    Q1.Push(5);
    Q1.Push(6);
    Q1.Push(7);
    Q1.Push(8);
    Q1.Push(9);
    Q1.Push(10);
    Q1.Push(11);
    Q1.Push(12);

    cout << Q1 << endl;

    return 0;
}