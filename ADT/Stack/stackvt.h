#ifndef STACKVT_H
#define STACKVT_H

#include <iostream>
#include "stack.h"
using namespace std;

template <class T>
class stackvt : public stack<T>
{
public:
	//definisco un alias per il tipo generico
	typedef typename stack<T>::valuetype valuetype;
	//costruttore di default
	stackvt();
	//costruttore con paramentro iniziale
	stackvt(int);
	void create();
	bool empty() const;
	valuetype top() const;
	valuetype pop();
	void push(valuetype);
	~stackvt();

private:
	valuetype *elements;
	int MAXLENGHT;
	int head; // index for the head of the stack
};

//implementazioni

template <class T>
stackvt<T>::stackvt()
{
	MAXLENGHT = 100;
	elements = new valuetype[MAXLENGHT];
	this->create();
}

template <class T>
stackvt<T>::stackvt(int dim)
{
	MAXLENGHT = dim;
	elements = new valuetype[MAXLENGHT];
	this->create();
}

template <class T>
void stackvt<T>::create()
{
	head = 0;
}

template <class T>
bool stackvt<T>::empty() const
{
	return (head == 0);
}

template <class T>
typename stackvt<T>::valuetype stackvt<T>::top() const
{
	valuetype value;
	if (!empty())
	{
		return (elements[head]);
	}
	return (value);
}

template <class T>
typename stackvt<T>::valuetype stackvt<T>::pop()
{
	valuetype value;
	if (!empty())
	{
		value = top();
		head--;
	}
	return (value);
}

template <class T>
void stackvt<T>::push(valuetype e)
{
	if (head < MAXLENGHT)
	{
		head++;
		elements[head] = e;
	}
}

template <class T>
stackvt<T>::~stackvt()
{
	MAXLENGHT = 0;
	head = 0;
	if (elements != nullptr)
	{
		delete[] elements;
		elements = nullptr;
	}
}

#endif
