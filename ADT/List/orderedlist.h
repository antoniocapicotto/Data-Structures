#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

//creo la classe lista ordinata con relazione d'ordine degli elementi <=
template <class T>
class orderedlist : public linkedlist<T>
{
public:
    orderedlist();
    void insert(T);
    void remove(T);
    bool search(T) const;
    void merge(const orderedlist<T> &);
    void print();
    ~orderedlist();

private:
    linkedlist<T> list; //class linked list
};

template <class T>
void orderedlist<T>::insert(T el)
{

    bool flag = false;
    for (auto pos = list.begin(); !list.end(pos) && !flag; pos = list.next(pos))
    {
        if (el <= list.read(pos))
        {
            list.insert(el, pos);
            flag = true;
        }
    }
    if (!flag)
    {
        list.push_back(el);
    }
}

template <class T>
orderedlist<T>::orderedlist()
{
    list.create();
}

template <class T>
orderedlist<T>::~orderedlist()
{
    list.~linkedlist();
}

template <class T>
void orderedlist<T>::print()
{
    cout << list;
}

template <class T>
void orderedlist<T>::remove(T el)
{
    list.remove(el);
}

template <class T>
bool orderedlist<T>::search(T el) const
{
    bool found = false;
    for (auto pos = list.begin(); !list.end(pos) && !found; pos = list.next(pos))
    {
        if (el == list.read(pos))
        {
            found = true;
        }
    }
    return (found);
}

template <class T>
void orderedlist<T>::merge(const orderedlist<T> &ol)
{
    for (auto pos = ol.list.begin(); !ol.list.end(pos); pos = ol.list.next(pos))
    {
        if (!this->search(ol.list.read(pos)))
        {
            this->insert(ol.list.read(pos));
        }
    }
}

#endif