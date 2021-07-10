#include "SqList.h"
#include "Algorithm.h"

int main()
{
    SqList<int> L1;

    L1.Insert(1, 0);
    L1.Insert(2, 5);
    L1.Insert(3, 5);
    L1.Insert(4, 3);
    L1.Insert(5, 5);
    L1.Insert(6, 7);
    L1.Insert(7, 5);
    L1.Insert(8, 5);

    L1.Sort();

    cout << "L1:" << L1 << endl;
    
    return 0;
}