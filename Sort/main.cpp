#include "Sort.h"
#include "Algorithm.h"
#include <iostream>
using namespace std;

int main()
{
    int A[8] = {49, 38, 65, 97, 76, 13, 27, 100};
    BubbleSort(A, 8);

    for (int i = 0; i < 8; i++)
        cout << A[i] << " ";
    cout << endl;
    return 0;
}