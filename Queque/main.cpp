#include <iostream>
#include "pnqueque.h"
#include "quequevt.h"
using namespace std;

int main()
{
	pnqueque<int> q;
	// for (int i = 0; i < 10; i++)
	// {
	// 	q.enqueque(i);
	// }
	// q.dequeque();
	// q.dequeque();

	// q.print();
	q.~pnqueque();
	quequevt<int> qv;
	for (int i = 0; i < 10; i++)
	{
		qv.enqueque(i);
	}
	while (!qv.empty())
	{
		cout << qv.top() << " ";
		qv.dequeque();
	}
	qv.~quequevt();

	cout << "\n";
	return 0;
}
