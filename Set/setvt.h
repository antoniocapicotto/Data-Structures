#ifndef SETVT_H
#define SETVT_H

#include <iostream>
#include "set.h"
using namespace std;

template <class T>
class setvt : public set<T>
{
public:
    //definisco i tipi
    typedef typename set<T>::value_type value_type;
    //costruttore con parametro
    setvt(int);
    //costruttore di copia
    setvt(const setvt<T> &);
    //metodo che inizializza l'insieme
    void create();
    //metodo che restituisce vero se l'insieme e' vuoto
    bool empty() const;
    //metodo che restituisce la lunghezza dell'insieme
    int size() const;
    //metodo che restituisce vero se l'elemento e' contenuto nell'insieme
    bool member(value_type) const;
    //metodo che inserisce un elemento nell'insieme
    void insert(value_type);
    //metodo che rimuove un elemento dall'insieme
    void remove(value_type);
    //metodo che restituisce la minima capienza massima tra due insiemi
    int min(int, int);
    //metodo che restituisce la massima capienza massima tra due insiemi
    int max(int, int);
    //metodo che stampa tutti gli elementi dell'insieme
    void print() const;
    //^^^operatori insiemistici^^^
    //unione tra un insieme A e un insieme B: ( C = A UNIONE B )
    setvt<T> union_(const setvt<T> &);
    //intersezione tra un insieme A ed un insieme B: (C = A INTERSEZIONE B)
    setvt<T> intersection_(const setvt<T> &);
    //insieme differenza tra un insieme A ed un insieme B: (C =  A - B)
    setvt<T> difference_(const setvt<T> &);
    //&sovraccarico operatori
    //assegnamento
    setvt<T> &operator=(const setvt<T> &);
    //distruttore della classe insieme
    ~setvt();

private:
    value_type *elements; //vettore contenente elementi di tipo tipoelem
    int dim;              //grandezza dell'insieme
    int MAXDIM;           //massima capienza
};

template <class T>
setvt<T>::setvt(int N)
{
    this->create();
    MAXDIM = N;
    elements = new value_type[MAXDIM];
}

template <class T>
setvt<T>::~setvt()
{
    delete[] elements;
    elements = nullptr;
    dim = 0;
}

template <class T>
void setvt<T>::create()
{
    dim = 0;
}

template <class T>
bool setvt<T>::empty() const
{
    return (dim == 0);
}

template <class T>
int setvt<T>::size() const
{
    return (dim);
}

template <class T>
int setvt<T>::min(int maxdim1, int maxdim2)
{
    if (maxdim1 == maxdim2)
    {
        return (maxdim1);
    }
    if (maxdim1 < maxdim2)
    {
        return (maxdim1);
    }
    else
    {
        return (maxdim2);
    }
}

template <class T>
int setvt<T>::max(int maxdim1, int maxdim2)
{
    if (maxdim1 == maxdim2)
    {
        return (maxdim1);
    }
    if (maxdim1 > maxdim2)
    {
        return (maxdim1);
    }
    else
    {
        return (maxdim2);
    }
}

template <class T>
bool setvt<T>::member(value_type el) const
{
    bool found = false;
    if (!this->empty())
    {
        //verifico se v appartiene
        for (int i = 0; (i < dim) && !found; i++)
        {
            if (elements[i] == el)
            {
                found = true;
            }
        }
    }
    return (found);
}

template <class T>
void setvt<T>::insert(value_type el)
{
    if (!member(el))
    {
        if (dim < MAXDIM)
        {
            elements[dim] = el;
            dim++;
        }
    }
}

template <class T>
void setvt<T>::remove(value_type el)
{
    if (member(el))
    {
        //elimino l'elemento nell'array
        int i = 0;
        while ((i < dim) && (elements[i] != el))
        {
            i++;
        }
        for (int j = i; j < (dim - 1); j++)
        {
            elements[j] = elements[j + 1];
        }
        dim--;
    }
}

template <class T>
void setvt<T>::print() const
{
    cout << "\n[";
    if (!this->empty())
    {
        for (int i = 0; i < dim; i++)
        {
            cout << " " << elements[i] << " ";
        }
    }
    cout << "]\n";
}

template <class T>
setvt<T> &setvt<T>::operator=(const setvt<T> &set)
{
    //elimino il vecchio stato
    delete[] elements;
    elements = nullptr;
    dim = 0;
    //copio il nuovo stato in quello attuale
    dim = set.dim;
    MAXDIM = set.MAXDIM;
    elements = new value_type[MAXDIM];
    for (int i = 0; i < set.MAXDIM; i++)
    {
        elements[i] = set.elements[i];
    }
    return *(this);
}

template <class T>
setvt<T> setvt<T>::union_(const setvt<T> &b)
{
    setvt<T> set((max(MAXDIM, b.MAXDIM)));
    for (int i = 0; i < dim; i++)
    {
        set.insert(elements[i]);
    }
    for (int i = 0; i < b.dim; i++)
    {
        set.insert(b.elements[i]);
    }
    return (set);
}

template <class T>
setvt<T> setvt<T>::intersection_(const setvt<T> &b)
{
    setvt<T> set(min(MAXDIM, b.MAXDIM));
    for (int i = 0; i < dim; i++)
    {
        if (b.member(elements[i]))
        {
            set.insert(elements[i]);
        }
    }
    for (int i = 0; i < b.dim; i++)
    {
        if (member(b.elements[i]))
        {
            set.insert(b.elements[i]);
        }
    }
    return (set);
}

template <class T>
setvt<T> setvt<T>::difference_(const setvt<T> &b)
{
    setvt<T> set(MAXDIM);
    for (int i = 0; i < dim; i++)
    {
        if (!b.member(elements[i]))
        {
            set.insert(elements[i]);
        }
    }
    return (set);
}

template <class T>
setvt<T>::setvt(const setvt<T> &set)
{
    dim = set.dim;
    MAXDIM = set.MAXDIM;
    elements = new value_type[MAXDIM];
    for (int i = 0; i < set.MAXDIM; i++)
    {
        elements[i] = set.elements[i];
    }
}

#endif