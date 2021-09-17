#ifndef MULTIPLESTACK_H
#define MULTIPLESTACK_H

#include <iostream>
#include "pnstack.h"
#include "./../list/linkedlist.h"
using namespace std;

template <class T>
class multiplestack : public pnstack<T>
{
public:
    typedef T value_type;
    multiplestack(unsigned int);
    void push(value_type, unsigned int);
    void pop(unsigned int);
    void print();
    ~multiplestack();

private:
    pnstack<T> *stackvector;
    int m;
};

template <class T>
multiplestack<T>::multiplestack(unsigned int n)
{
    m = n;
    stackvector = new pnstack<T>[m];
    for (int i = 0; i < m; i++)
    {
        stackvector[i].create();
    }
}

template <class T>
multiplestack<T>::~multiplestack()
{
    if (stackvector != nullptr)
    {
        delete[] stackvector;
        stackvector = nullptr;
    }
    m = 0;
}

template <class T>
void multiplestack<T>::push(value_type el, unsigned int i)
{
    if (i < m)
    {
        stackvector[i].push(el);
    }
}

template <class T>
void multiplestack<T>::print()
{
    for (int i = 0; i < m; i++)
    {
        stackvector[i].print();
        cout << "\n";
    }
}

template <class T>
void multiplestack<T>::pop(unsigned int i)
{
    if (i < m)
    {
        return (stackvector[i].pop());
    }
}

#endif