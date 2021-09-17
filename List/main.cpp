#include <iostream>
#include "linkedlist.h"
#include "listvector.h"
#include "orderedlist.h"
int main()
{
	listvector<int> l1,l2;
	for (int i = 0; i < 10; i++)
	{
		l1.push_back(i);
	}
	l2 = l1;
	cout << (l1 == l2);

	l1.~listvector();
	l2.~listvector();
	cout << "\n";
	return 0;
}
