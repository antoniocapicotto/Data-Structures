#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
using namespace std;

template <class K, class E, class N>
class bst
{
public:
    //tipi
    typedef K key;
    typedef E label;
    typedef N node;
    //operatori
    virtual void create() = 0;
    virtual bool empty() const = 0;
    virtual void insert(key, label) = 0;
    virtual void erase(key) = 0;
    virtual node search(key) const = 0;
    virtual node minimum() const = 0;
    virtual node maximum() const = 0;
    virtual node predecessor(node) const = 0;
    virtual node successor(node) const = 0;
    virtual ~bst(){};
};

#endif