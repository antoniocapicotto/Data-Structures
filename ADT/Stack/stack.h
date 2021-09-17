#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class stack
{
public:
	//tipi
	typedef T value_type;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual value_type top() const = 0;
	virtual void pop() = 0;
	virtual void push(value_type) = 0;
	virtual ~stack(){};
};
#endif
