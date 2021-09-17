#include <iostream>
#include <string>
#include "pnbintree.h"
#include "bintreevt.h"
using namespace std;

int main()
{
	pnbintree<int> t, b;

	t.ins_root();
	t.write(t.get_root(), 10);
	t.ins_sx(t.get_root(), 20);

	b.ins_root();
	b.write(b.get_root(), 30);
	b.ins_sx(b.get_root(), 40);

	t.mutation(t.sx(t.get_root()), b.sx(b.get_root()), b);

	cout << "\ndepth: " << t.depth() << endl;

	t.preorder(t.get_root());

	t.~pnbintree();
	b.~pnbintree();

	cout << "\n";
	return 0;
}
