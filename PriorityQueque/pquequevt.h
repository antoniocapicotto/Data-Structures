#ifndef PQUEQUEVT_H
#define PQUEQUEVT_H

#include <iostream>
#include "assert.h"
#include "pqueque.h"
using namespace std;

template <class T>
class pquequevt : public pqueque<T>
{
public:
	//definisco i tipi
	typedef typename pqueque<T>::value_type value_type;
	//^^^operatori
	//costruttore
	pquequevt();
	//costruttore con parametro
	pquequevt(int);
	//distruttore
	~pquequevt();
	//metodo che inizializza la coda
	void create();
	//metodo che restituisce vero se la prioricoda e' vuota
	bool empty() const;
	//metodo che restituisce l'elemento con priorita' minima
	value_type min() const;
	//metodo che elimina dalla prioricoda l'elemento con priorita' minima
	void deleteMin();
	//metodo che inserisce un elemento nella prioricoda
	void insert(value_type);
	//&funzioni di servizio
	//metodo di servizio che stampa tutti gli elementi della prioricoda
	void print() const;

private:
	//massima grandezza dell'array
	int MAXLENGHT;
	//array di tipo tipoelem
	value_type *heap;
	//riferimento all'ultimo elemento inserito
	int last;
	//&metodi per aggiornare lo stato della coda
	//metodo che aggiorna lo stato della coda quando viene inserito un elemento
	void fixUp();
	//metodo che aggiorna lo stato della coda quando viene rimosso un elemento
	void fixDown(int, int);
};

//~implementazione dei metodi
//costruttore di default
template <class T>
pquequevt<T>::pquequevt()
{
	this->create();
	MAXLENGHT = 100;
	heap = new value_type[MAXLENGHT];
}
//costruttore con paramentro N che indica la massima grandezza
template <class T>
pquequevt<T>::pquequevt(int N)
{
	this->create();
	MAXLENGHT = N;
	heap = new value_type[MAXLENGHT];
}
//metodo creacoda()
template <class T>
void pquequevt<T>::create()
{
	last = 0;
}
template <class T>
bool pquequevt<T>::empty() const
{
	return (last == 0);
}
//distruttore
template <class T>
pquequevt<T>::~pquequevt()
{
	last = 0;
	delete[] heap;
	heap = nullptr;
}
//metodo insert
template <class T>
void pquequevt<T>::insert(value_type v)
{
	assert(last < MAXLENGHT);
	heap[++last - 1] = v;
	fixUp();
}
//metodo min()-> elemento minimo della coda
template <class T>
typename pquequevt<T>::value_type pquequevt<T>::min() const
{
	assert(last != 0);
	return (heap[0]);
}
//metodo per cancellare il minimo elemento con priorita'
template <class T>
void pquequevt<T>::deleteMin()
{
	assert(last != 0);
	heap[0] = heap[last - 1];
	last--;
	fixDown(1, last);
}
/* 
 * Per ripristinare i vincoli dello heap quando la priorita' di un nodo e'     *
 * cresciuta, ci spostiamo nello heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dello heap.                                           
*/
template <class T>
void pquequevt<T>::fixUp()
{
	int k = last;

	while ((k > 1) && (heap[k - 1] < heap[(k / 2) - 1]))
	{
		value_type tmp;

		tmp = heap[k - 1];
		heap[k - 1] = heap[(k / 2) - 1];
		heap[k / 2 - 1] = tmp;
		k = k / 2;
	}
}
/* 
 * Per ripristinare i vincoli dello heap quando la priorita' di un nodo si e'  *
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario, *
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci     *
 * quando il nodo al posto k non e' più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N e' pari e  *
 * k e' N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      
*/
template <class T>
void pquequevt<T>::fixDown(int k, int N)
{

	short int scambio = 1;

	while ((k <= N / 2) && (scambio))
	{
		int j = 2 * k;
		value_type tmp;
		if ((j < N) && (heap[j - 1] > heap[j]))
		{
			j++;
		}
		if (scambio = (heap[j - 1] < heap[k - 1]))
		{
			tmp = heap[k - 1];
			heap[k - 1] = heap[j - 1];
			heap[j - 1] = tmp;
			k = j;
		}
	}
}
template <class T>
void pquequevt<T>::print() const
{
	cout << "\n[ ";
	for (int i = 0; i < last; i++)
	{
		if (i % 2 == 0)
		{
			cout << heap[i];
		}
		else
		{
			cout << "\t" << heap[i] << " - ";
		}
	}
	std::cout << " ]\n";
}
//funzioni di servizio per tipo di dato array
template <class T>
void print(T *A, int n)
{
	std::cout << "\n[";
	for (int i = 0; i < n; i++)
	{
		std::cout << " " << A[i] << " ";
	}
	std::cout << "]\n";
}

template <class T>
void heapsort(T *e, int n)
{
	pquequevt<T> pq(n);
	for (int i = 0; i < n; i++)
	{
		pq.insert(e[i]);
	}
	for (int i = 0; i < n; i++)
	{
		e[i] = pq.min();
		pq.deleteMin();
	}
}

#endif
