#ifndef LISTVECTOR_H
#define LISTVECTOR_H

#include <iostream>
#include "linearlist.h"
using namespace std;

template <class T>
class listvector : public linearlist<T, int>
{
public:
	//definisco un alias per il tipovalore generico
	typedef typename linearlist<T, int>::value_type value_type;
	//definisco l'indice dell'array come un intero per scorrere il vettore
	typedef typename linearlist<T, int>::position position;
	//costruttore di defualt
	listvector();
	//costruttore con parametro
	listvector(int);
	// costruttore per copia
	listvector(const listvector<T> &);
	//distruttore
	~listvector();
	/* =================================== OPERATORI =========================================== */
	//metodo che inizializza la lenght della lista
	void create();
	//metodo che indica quando la lista e' vuota
	bool empty() const;
	//metodo che restituisce il valore data una posizione p della lista
	value_type read(position) const;
	//metodo che scrive/modifica il valore v, in posizione p nella lista
	void write(value_type, position);
	//metodo che restituisce la prima posizione della lista
	position begin() const;
	//metodo che restituisce la prossima posizione  di p nella lista, restituisce p se si e' arrivati alla fine della lista
	position next(position) const;
	//metodo che restituisce la posizione che precede p nella lista, resituisce p se si arriva all'inizio della lista
	position previous(position) const;
	//metodo che restituisce un boolean che indica se si e' arrivati alla fine della lista
	bool end(position) const;
	//metodo che restituisce la posizione p dell'ultimo elemento della lista ovvero il fine lista
	position last() const;
	//metodo che inserisce un elemento v in posizione p nella lista
	void insert(value_type, position);
	//metodo che cancella un elemento data una posizione p
	void erase(position);
	//^funzioni utili
	void insertion_sort();
	/** sovraccarico di operatori **/
	//operatore di assegnamento
	listvector<T> &operator=(const listvector<T> &);
	//operatore di uguaglianza
	bool operator==(const listvector<T> &) const;

private:
	//metodo private che permette di modificare la massima dimensione dell'array
	void changeDimension(value_type *&, int, int);
	value_type *elements; //array di elementi
	int lenght;			  //lunghezza
	int array_dimension;  //capienza massima
};
//metodo public
template <class T>
listvector<T>::listvector()
{
	array_dimension = 10;
	elements = new value_type[array_dimension];
	this->create();
}
//metodo public
template <class T>
listvector<T>::listvector(int N)
{
	array_dimension = N;
	elements = new value_type[array_dimension];
	this->create(); //inizializza la lista
}
//metodo public
template <class T>
void listvector<T>::create()
{
	lenght = 0;
}
//metodo public
template <class T>
listvector<T>::listvector(const listvector<T> &list)
{
	this->array_dimension = list.array_dimension;
	this->lenght = list.lenght;
	this->elements = new value_type[array_dimension];
	for (int i = 0; i < list.array_dimension; i++)
	{
		this->elements[i] = list.elements[i];
	}
}
//metodo public
template <class T>
listvector<T>::~listvector()
{
	delete[] elements;
	elements = nullptr;
	lenght = 0;
	array_dimension = 0;
}
//metodo public
template <class T>
bool listvector<T>::empty() const
{
	return (lenght == 0);
}
//metodo public
template <class T>
typename listvector<T>::value_type listvector<T>::read(position pos) const
{
	value_type item;
	if ((pos > 0) && (pos < lenght + 1))
	{
		return (elements[pos - 1]);
	}
	return (item);
}
//metodo public
template <class T>
void listvector<T>::write(value_type el, position pos)
{
	if ((pos > 0) && (pos < lenght + 1))
	{
		elements[pos - 1] = el;
	}
}
//metodo public
template <class T>
typename listvector<T>::position listvector<T>::begin() const
{
	return (1); //posizione iniziale
}
//metodo public
template <class T>
typename listvector<T>::position listvector<T>::next(position pos) const
{
	if ((pos > 0) && (pos < lenght + 1))
	{
		return (pos + 1);
	}
	else
	{
		return (pos);
	}
}
//metodo public
template <class T>
typename listvector<T>::position listvector<T>::previous(position pos) const
{
	if ((pos > 1) && (pos < lenght + 1))
	{
		return (pos - 1);
	}
	else
	{
		return (pos);
	}
}
//metodo public
template <class T>
bool listvector<T>::end(position pos) const
{
	bool flag = false;
	if ((pos > 0) && (pos <= lenght + 1))
	{
		flag = (pos == lenght + 1);
	}
	return (flag);
}
//metodo public
template <class T>
typename listvector<T>::position listvector<T>::last() const
{
	position pos = begin();
	//cerco l'ultima posizione in cui vi e' un elemento
	while (!end(next(pos)))
	{
		pos = next(pos);
	}
	return (pos);
}
//metodo public
template <class T>
void listvector<T>::insert(value_type el, position pos)
{
	//verifico di se la lenght della lista ha raggiunto la capacita' massima
	if (lenght == array_dimension)
	{
		changeDimension(elements, array_dimension, array_dimension * 2);
		array_dimension = array_dimension * 2;
	}
	//verifico se la posizione in cui voglio inserire v, e' una posizione valida
	if ((pos > 0) && (pos <= lenght + 1))
	{
		for (int i = lenght; i >= pos; i--)
		{
			elements[i] = elements[i - 1];
		}
		elements[pos - 1] = el;
		lenght++;
	}
}
//metodo public
template <class T>
void listvector<T>::erase(position pos)
{
	if (lenght < array_dimension / 2)
	{
		changeDimension(elements, array_dimension, array_dimension / 2);
		array_dimension = array_dimension / 2;
	}
	if ((pos > 0) && (pos < lenght + 1))
	{
		if (!empty())
		{
			for (int i = pos - 1; i < (lenght - 1); i++)
			{
				elements[i] = elements[i + 1];
			}
			lenght--;
		}
	}
}

//metodo public
template <class T>
listvector<T> &listvector<T>::operator=(const listvector<T> &list)
{
	if (!(*this == list))
	{ //!attenzione agli autoassegnamenti
		this->array_dimension = list.array_dimension;
		this->lenght = list.lenght;
		delete[] this->elements;
		elements = new value_type[array_dimension];
		for (int i = 0; i < list.array_dimension; i++)
		{
			this->elements[i] = list.elements[i];
		}
	}
	return *(this);
}
//metodo public
template <class T>
bool listvector<T>::operator==(const listvector<T> &list) const
{
	if (this->size() != list.size())
	{
		return (false);
	}
	else
	{
		position pos1 = begin();
		position pos2 = list.begin();
		while (!end(pos1))
		{
			if (!(read(pos1) == read(pos2)))
			{
				return (false);
			}
			pos1 = next(pos1);
			pos2 = next(pos2);
		}
	}
	return (true);
}

//metodo private
template <class T>
void listvector<T>::changeDimension(value_type *&e, int oldSize, int newSize)
{
	value_type *temp = new value_type[newSize];
	int number = 0;
	if (oldSize < newSize)
	{
		number = oldSize;
	}
	else
	{
		number = newSize;
	}
	for (int i = 0; i < number; i++)
	{
		temp[i] = e[i];
	}
	delete[] e;
	e = temp;
}

template <class T>
void listvector<T>::insertion_sort()
{
	T temp;
	position i, j;
	for (i = 1; i < lenght; i++)
	{
		temp = elements[i];
		j = i - 1;
		while ((j >= 0) && (elements[j] > temp))
		{
			elements[j + 1] = elements[j];
			j--;
		}
		elements[j + 1] = temp;
	}
}

#endif
