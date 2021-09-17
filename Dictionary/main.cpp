#include <iostream>
#include <string>
#include "hashtable.h"
using namespace std;
int main()
{
	hashtable<string, int> h(10);

	mypair<string, int> the_pair;
	the_pair.first = "firstkey";
	the_pair.second = 10;
	std::cout << "\nvuoto: " << h.empty();
	std::cout << "\nnum elementi: " << h.size();
	h.insert(the_pair);
	std::cout << "\nvalore primachiave: " << h.retrieves(the_pair.first);
	std::cout << "\nappartiene: " << h.member(the_pair.first);
	std::cout << "\n\n";
	h.printkeys();
	mypair<string, int> the_copy = *(h.find(the_pair.first));
	the_copy.first = "secondkey";
	std::cout << "\nsearch copy key: " << h.search(the_copy.first);
	std::cout << "\nappartiene copia della primachiave: "
			  << h.member(the_copy.first);
	h.insert(the_copy);
	std::cout << "\nmembro coppia: " << h.member(the_copy.first);
	h.modify(the_copy.first, 20);
	std::cout << "\nvalore primachiave copia: " << h.retrieves(the_copy.first);
	std::cout << "\n";
	h.printkeys();

	h.~hashtable();
	std::cout << "\n";
	return 0;
}
