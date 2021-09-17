#ifndef PQUEQUE_H
#define PQUEQUE_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class pqueque
{
public:
	//tipi
	typedef T value_type;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual value_type min() const = 0;
	virtual void deleteMin() = 0;
	virtual void insert(value_type) = 0;
	virtual ~pqueque(){};
};
#endif
