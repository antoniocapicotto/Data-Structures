#include <iostream>
#include "pnbst.h"
using namespace std;
int main()
{
    //bst chiave-valore
    pnbst<int, int> bst;
    bst.ins_root(10,10);
    bst.insert(20, 20);
    bst.insert(15, 15);
    bst.insert(5, 5);
    bst.insert(4, 4);
    bst.insert(2, 2);
    bst.insert(22, 22);
    // cout << "\nleggi chiave: " << bst.read_key(bst.predecessor(bst.search(20)));
    //cout << "test maximum from root: " << bst.read_key(bst.maximum(bst.search(5)));
    // bst.erase_sub_tree(bst.get_root());
    bst.modify(15, 99);
    cout << "\nleggi label: " << bst.read_label(bst.search(15)) << endl;
    bst.erase(20);
    bst.erase(10);
    // cout << "\nnode radice: " << bst.read_key(bst.get_root());
    // cout << "\nnode sinistro radice: " << bst.read_key(bst.get_sx(bst.get_root()));
    // cout << "\nnode destro radice: " << bst.read_key(bst.get_dx(bst.get_root()));
    // cout << "\nnode destro destro radice: " << bst.read_key(bst.get_dx(bst.get_dx(bst.get_root())));

    // cout << "\ntest search: " << bst.read_key(bst.search(10));
    // cout << "\nread label: " << bst.read_label(bst.max());
    cout << "\n";
    bst.inorder(bst.get_root());
    bst.~pnbst();
    cout << "\n";
    return 0;
}