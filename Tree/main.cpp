#include <iostream>
#include "treelink.h"
#include "treelist.h"
using namespace std;
int main()
{
	//albero lista
	treelist<char> T;
	T.insRoot();
	T.write(T.getRoot(), 'a');
	T.insFirstChild(T.getRoot(), 'b');
	T.insNextSibiling(T.firstChild(T.getRoot()), 'c');
	T.insNextSibiling(T.firstChild(T.getRoot()), 'd');
	T.insFirstChild(T.getRoot(), 'e');
	T.print();
	T.~treelist();

	//albero collegato
	// treelink<char> t;
	// t.insRoot();
	// t.write(t.getRoot(), 'a');
	// t.insFirstChild(t.getRoot(), 'b');
	// t.insFirstChild(t.firstChild(t.getRoot()), 'c');
	// t.insNextSibiling(t.firstChild(t.getRoot()), 'd');
	// t.insNextSibiling(t.firstChild(t.getRoot()), 'e');
	// cout << "\nbfs: ";
	// t.bfs(t.getRoot());
	// cout << "\n";
	// t.print(t.getRoot());
	// t.~treelink();

	cout << "\n";
	return 0;
}
