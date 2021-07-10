#include "LinkQueue.h"

int main()
{
	LinkQueue<int> Q;
	Q.Push(1);
	Q.Push(2);
	Q.Push(3);
	cout << Q << endl;

	LinkQueue<int> Q2(Q);
	Q2.Pop();
	cout << Q2 << endl;
	Q2.Pop();
	cout << Q2 << endl;
	Q2.Pop();
	cout << Q2 << endl;
	Q2.Pop();
	cout << Q2 << endl;

	cout << Q << endl;
	return 0;
}