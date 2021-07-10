#include "LNode.h"
#include "Algorithm.h"

int main()
{
    LinkList<int> L1;

    L1.RearInsert(1);
    L1.RearInsert(2);
    L1.RearInsert(3);
    L1.RearInsert(2);
    L1.RearInsert(-1);

    cout << L1 << endl;

    L1.Set();

    cout << L1 << endl;

    return 0;
}
