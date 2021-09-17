#ifndef QUEQUE_H
#define QUEQUE_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class queque
{
public:
	//tipi
	typedef T value_type;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual value_type top() const = 0;
	virtual void dequeque() = 0;
	virtual void enqueque(value_type) = 0;
	virtual int size() const = 0;
	virtual ~queque() {}
};

#endif
