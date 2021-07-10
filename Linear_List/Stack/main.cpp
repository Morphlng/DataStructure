#include "SqStack.h"

int main()
{
    SqStack<int> s;

    s.Push(1);
    s.Push(2);
    s.Push(3);
    cout << s << endl;

    return 0;
}