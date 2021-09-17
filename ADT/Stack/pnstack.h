#ifndef PNSTACK_H
#define PNSTACK_H

#include <iostream>
#include "stack.h"
using namespace std;

//dichiaro la classe pnstack
template <class T>
class pnstack;

//dichiaro la classe nodostack
template <class T>
class stacknode
{
	friend class pnstack<T>;

public:
	stacknode()
	{
		prev = nullptr;
	}
	stacknode(T el)
	{
		item = el;
		prev = nullptr;
	}

private:
	stacknode<T> *prev;
	T item;
};

template <class T>
class pnstack : public stack<T>
{
public:
	//definisco un alias per il tipo generico tipovalore e il tipo stacknodo
	typedef typename stack<T>::value_type value_type;
	typedef stacknode<T> *node;
	//costruttore
	pnstack();
	//distruttore
	~pnstack();
	//metodo che inizializza l'oggetto pila
	void create();
	//metodo che restituisce vero se la pila e' vuota
	bool empty() const;
	//metodo che restituisce il valore in cima alla pila
	value_type top() const;
	//metodo che restituisce e rimuove l'elemento in cima alla pila
	void pop();
	//metodo che inserisce un valore in testa alla pila
	void push(value_type);
	//inserisce un elemento in cima alla pila senza duplicarlo in base al flag del secondo parametro
	void push(value_type, bool);
	//funzione di servizio che stampa tutti gli elementi contenuti nella pila
	void print();
	//funzione di servizio che verifica se un elemento e' già presente nella pila
	bool contains(value_type) const;

private:
	stacknode<T> *head;
};

//implementazioni

template <class T>
pnstack<T>::pnstack()
{
	this->create();
}

template <class T>
pnstack<T>::~pnstack()
{
	while (!this->empty())
	{
		this->pop();
	}
	delete head;
	head = nullptr;
}

template <class T>
void pnstack<T>::create()
{
	head = nullptr;
}

template <class T>
bool pnstack<T>::empty() const
{
	return (head == nullptr);
}

template <class T>
typename pnstack<T>::value_type pnstack<T>::top() const
{
	value_type item;
	if (!this->empty())
	{
		return (head->item);
	}
	return (item);
}

template <class T>
void pnstack<T>::pop()
{
	if (!this->empty())
	{
		node temp = head;
		head = head->prev;
		delete temp;
		temp = nullptr;
	}
}

template <class T>
void pnstack<T>::push(value_type el)
{
	stacknode<T> *newHead = new stacknode<T>(el);
	newHead->prev = head;
	head = newHead;
}

template <class T>
void pnstack<T>::print()
{
	if (!this->empty())
	{
		node i = head;
		while (i != nullptr)
		{
			cout << " " << i->item << " ";
			i = i->prev;
		}
	}
}

template <class T>
bool pnstack<T>::contains(value_type el) const
{
	bool found = false;
	if (!this->empty())
	{
		node i = head;
		while ((i != nullptr) && !found)
		{
			if (i->item == el)
			{
				found = true;
			}
			i = i->prev;
		}
	}
	return (found);
}

template <class T>
void pnstack<T>::push(value_type el, bool flag)
{
	//inserisco un elemento ammettendo ripetizioni di quest'ultimo
	if (!flag)
	{
		push(el);
	}
	//inserisco un elemento senza ripetizioni
	else
	{
		if (!contains(el))
		{
			push(el);
		}
	}
}

#endif
