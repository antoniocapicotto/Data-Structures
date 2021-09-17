#include <iostream>
#include "pnstack.h"
#include "multiplestack.h"
//#include "stackvt.h"
using namespace std;
int main()
{
	multiplestack<int> ms(1);
	ms.~multiplestack();
	pnstack<int> stack;
	for (int i = 0; i < 10; i++)
	{
		stack.push(i);
	}
	stack.pop();
	stack.print();
	stack.~pnstack();
	std::cout << "\n";
	return 0;
}
