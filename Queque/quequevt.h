#ifndef QUEQUEVT_H
#define QUEQUEVT_H

#include <iostream>
#include "queque.h"
#define MAXDIM 100
using namespace std;

template <class T>
class quequevt : public queque<T>
{
public:
	//definisco i tipi
	typedef typename queque<T>::value_type value_type;
	//costruttore
	quequevt();
	//costruttore con parametro
	quequevt(int);
	//^^^operatori
	//metodo che inizializza una coda
	void create();
	//metodo che restituisce vero se la coda e' vuota
	bool empty() const;
	//legge e restituisce l'elemento al top
	value_type top() const;
	//metodo che rimuove un elemento della coda dal fondo
	void dequeque();
	//metodo che inserisce un elemento nella coda
	void enqueque(value_type);
	//metodo che restituisce la lunghezza della coda
	int size() const;
	//distruttore
	~quequevt();

private:
	value_type *elements; //array di elementi
	int head;			  //cursore che punta alla testa dell'array
	int lenght;			  //lunghezza della coda
	int MAXLENGHT;		  //massima capienza
};
template <class T>
quequevt<T>::quequevt()
{
	this->create();
	MAXLENGHT = MAXDIM;
	elements = new value_type[MAXLENGHT];
	head = 0;
}
template <class T>
quequevt<T>::quequevt(int N)
{
	this->create();
	MAXLENGHT = N;
	elements = new value_type[MAXLENGHT];
	head = 0;
}
template <class T>
void quequevt<T>::create()
{
	lenght = 0;
}
template <class T>
bool quequevt<T>::empty() const
{
	return (lenght == 0);
}
template <class T>
typename quequevt<T>::value_type quequevt<T>::top() const
{
	value_type item;
	if (!this->empty())
	{
		return (elements[head]);
	}
	return (item);
}
template <class T>
void quequevt<T>::dequeque()
{
	if (!this->empty())
	{
		head = ((head + 1) % MAXLENGHT);
		lenght--;
	}
}
template <class T>
void quequevt<T>::enqueque(value_type el)
{
	if (lenght < MAXLENGHT)
	{
		elements[((head + lenght) % MAXLENGHT)] = el;
		lenght++;
	}
}
template <class T>
int quequevt<T>::size() const
{
	return (lenght);
}
template <class T>
quequevt<T>::~quequevt()
{
	lenght = 0;
	delete[] elements;
	elements = nullptr;
}

#endif
