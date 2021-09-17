#ifndef PNQUEQUE_H
#define PNQUEQUE_H

#include <iostream>
#include "queque.h"
using namespace std;

//forward declaration della classe
template <class T>
class pnqueque;

//nodo della coda
template <class T>
class quequenode
{
	friend class pnqueque<T>;

public:
	quequenode()
	{
		next = nullptr;
	}
	quequenode(T el)
	{
		item = el;
		next = nullptr;
	}

private:
	T item;
	quequenode<T> *next;
};
template <class T>
class pnqueque : public queque<T>
{
public:
	//definisco i tipi
	typedef quequenode<T> *node;
	typedef typename queque<T>::value_type value_type;
	//costruttore
	pnqueque();
	//costruttore di copia
	pnqueque(const pnqueque<T> &);
	//^^^operatori
	//metodo che inizializza la coda
	void create();
	//metodo che restituisce vero se la coda e' vuota
	bool empty() const;
	//metodo che restituisce il valore in testa alla coda (FIFO)
	value_type top() const;
	//metodo che rimuove un elemento dalla coda
	void dequeque();
	//metodo che inserisce un valore nella coda
	void enqueque(value_type);
	//metodo che restituisce la grandezza della coda
	int size() const;
	//&metodo che data una coda di interi restituisce una coda di soli elementi positivi
	pnqueque<int> positive_queque();
	//metodo che stampa tutti gli elementi della coda
	void print() const;
	//distruttore
	~pnqueque();

private:
	node head;
	node tail;
	int lenght;
};
template <class T>
pnqueque<T>::pnqueque()
{
	this->create();
	head = tail = nullptr;
}
template <class T>
void pnqueque<T>::create()
{
	lenght = 0;
}
template <class T>
bool pnqueque<T>::empty() const
{
	return (lenght == 0);
}
template <class T>
typename pnqueque<T>::value_type pnqueque<T>::top() const
{
	value_type item;
	if (!this->empty())
	{
		return (head->item);
	}
	return (item);
}
template <class T>
void pnqueque<T>::dequeque()
{
	if (!this->empty())
	{
		node temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
		lenght--;
	}
}

template <class T>
void pnqueque<T>::enqueque(value_type el)
{
	//creo il nodo da inserire con il valore el
	node temp = new quequenode<T>(el);
	if (this->empty())
	{
		head = tail = temp;
	}
	else
	{
		tail->next = temp;
	}
	temp->next = nullptr;
	tail = temp;
	lenght++;
}
template <class T>
int pnqueque<T>::size() const
{
	return (lenght);
}
template <class T>
pnqueque<T>::~pnqueque()
{
	while (!this->empty())
	{
		this->dequeque();
	}
	head = tail = nullptr;
	lenght = 0;
}
template <>
pnqueque<int> pnqueque<int>::positive_queque()
{
	pnqueque<int> queque;			 //cosa risultato
	pnqueque<int> quequecopy(*this); //copia coda iniziale
	while (!quequecopy.empty())
	{
		int temp = quequecopy.top();
		if (temp >= 0)
		{
			queque.enqueque(temp);
		}
		quequecopy.dequeque();
	}
	return (queque);
}
template <class T>
pnqueque<T>::pnqueque(const pnqueque<T> &queque)
{
	//inizializzo l'oggetto
	this->create();
	head = tail = nullptr;
	//copio i valore della seconda coda nella prima
	node i = queque.head;
	while (i != nullptr)
	{
		this->enqueque(i->item);
		i = i->next;
	}
}
template <class T>
void pnqueque<T>::print() const
{
	if (!this->empty())
	{
		node i = head;
		while (i != nullptr)
		{
			cout << " " << i->item << " ";
			i = i->next;
		}
	}
}
#endif
