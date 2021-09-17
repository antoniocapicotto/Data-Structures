#include <iostream>
#include "setvt.h"
#include "pnset.h"
using namespace std;
int main()
{
    pnset<int> d, e, f;
    for (int i = 0; i < 10; i++)
    {
        d.insert(i);
    }
    d.print();
    cout << "\n";
    for (int i = 10; i < 20; i++)
    {
        e.insert(i);
    }
    e.print();
    cout << "\n";
    f = d.union_(e);
    f.print();
    cout << "\n";
    f = d.intersection_(e);
    f.print();
    cout << "\n";
    f = d.difference_(e);
    f.print();
    d = e;
    cout << "\n d == e: " << (d == e);
    d.~pnset();
    e.~pnset();
    f.~pnset();
    cout << "\n";
    return 0;
}