#include <iostream>
#include <string>
#include "pquequevt.h"
using namespace std;
int main()
{
	pquequevt<int> pq;
	pq.insert(10);
	pq.insert(5);
	pq.insert(2);
	pq.insert(3);
	pq.insert(4);
	pq.deleteMin();
	pq.print();
	pq.~pquequevt();
	// int n = 10;
	// double *v = new double[n];
	// for (int i = 0; i < n; i++)
	// {
	// 	v[i] = n - 1 - i;
	// }
	// print(v, n);
	// std::cout << "\n";
	// heapsort(v, n);
	// print(v, n);

	// delete[] v;
	// std::cout << "\n";
	cout << "\n";
	return 0;
}
