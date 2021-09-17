#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class set
{
public:
    //tipi
    typedef T value_type;
    //operatori
    virtual void create() = 0;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual bool member(value_type) const = 0;
    virtual void insert(value_type) = 0;
    virtual void remove(value_type) = 0;
    virtual ~set(){};
};

#endif