#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "linearlist.h"
using namespace std;

//dichiaro la classe linkedlist
template <class T>
class linkedlist;

//dichiaro la classe nodolista
template <class T>
class listnode
{
	friend class linkedlist<T>;

public:
	listnode()
	{
		next = nullptr;
		prev = nullptr;
	}
	listnode(T el)
	{
		item = el;
		next = nullptr;
		prev = nullptr;
	}

private:
	T item;
	listnode<T> *next;
	listnode<T> *prev;
};

template <class T>
class linkedlist : public linearlist<T, listnode<T> *>
{
public:
	//definisco un alias per il tipo generico per il tipo tipovalore e per il tipo posizione
	typedef typename linearlist<T, listnode<T> *>::value_type value_type;
	typedef listnode<T> *position;
	/** operatori **/
	//&costruttore di default
	linkedlist();
	//costruttore di copia
	linkedlist(const linkedlist<T> &);
	//metodo che inizializza una nuova lista
	void create();
	//metodo che restituisce un boolean , verifica se la lista e' vuota
	bool empty() const;
	//metodo che legge il valore di un elemento data una posizione p
	value_type read(position) const;
	//metodo che scrive un elemento v in posizione p della lista
	void write(value_type, position);
	//metodo che restituisce il primo lista
	position begin() const;
	//metodo che restituisce l'ultimo elemento della lista
	position last() const;
	//metodo che restituisce un boolean, verifica se si e' arrivati al fine lista
	bool end(position) const;
	//metodo che restituisce la posizione che occupa il successivo elemento di pos nella lista
	position next(position) const;
	//metodo che restituisce la posizione che occupa il precedente elemento di pos nella lista
	position previous(position) const;
	//metodo che inserisce un item in posizione pos nella lista
	void insert(value_type, position);
	//metodo che cancella un item dalla lista di posizione p
	void erase(position);
	//^funzioni utili
	/*metodo che quando la lista è di elementi di tipo intero, sposta, nel modo più efficiente possibile,
	il massimo in ultima posizione, e il minimo in prima posizione*/
	void move_min_max();
	//metodo che elimina da una lista L1 tutti gli elementi presenti nella lista L2.
	void difference(const linkedlist<T> &);
	//&distruttore
	~linkedlist();
	/**sovraccarico di operatori**/
	//&operatore di assegnamento
	linkedlist<T> &operator=(const linkedlist<T> &);
	//&operatore di uguaglianza
	bool operator==(const linkedlist<T> &) const;
	//&operatore di disuguaglianza
	bool operator!=(const linkedlist<T> &) const;

private:
	listnode<T> *phead; //puntatore alla testa
	int lenght;			//lunghezza della lista
};

//costruttore
template <class T>
linkedlist<T>::linkedlist()
{
	this->create();
	phead = new listnode<T>;
	phead->next = phead;
	phead->prev = phead;
}

//costruttore di copia
//metodo public
template <class T>
void linkedlist<T>::create()
{
	lenght = 0;
}

//metodo public
template <class T>
bool linkedlist<T>::empty() const
{
	return (lenght == 0);
}

//metodo public
template <class T>
typename linkedlist<T>::value_type linkedlist<T>::read(position pos) const
{
	value_type item; //empty value
	if (!end(pos) && !empty())
	{
		return (pos->item);
	}
	return (item);
}

//metodo public
template <class T>
void linkedlist<T>::write(value_type el, position pos)
{
	if (!end(pos))
	{
		pos->item = el;
	}
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::begin() const
{
	return (phead->next);
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::last() const
{
	return (phead->prev);
}

//metodo public
template <class T>
bool linkedlist<T>::end(position pos) const
{
	return (pos == phead);
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::next(position pos) const
{
	return (pos->next);
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::previous(position pos) const
{
	if (!end(pos))
	{
		return (pos->prev);
	}
	else
	{
		return (pos);
	}
}

//metodo public
template <class T>
void linkedlist<T>::insert(value_type el, position pos)
{
	//creo un nuovo nodo
	position newnode = new listnode<T>(el);
	//innesto il nuovo nodo nella posizion p
	newnode->next = pos;
	newnode->prev = pos->prev;
	//sposto i puntatori per sistemare la lista
	pos->prev->next = newnode;
	pos->prev = newnode;
	//incremento la lunghezza
	lenght++;
}

//metodo public
template <class T>
void linkedlist<T>::erase(position pos)
{
	if (!empty() && !end(pos))
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		//elimino il nodo
		delete pos;
		pos = nullptr;
		//decremento la lunghezza
		lenght--;
	}
}

//metodo public
template <class T>
linkedlist<T>::~linkedlist()
{
	//cancello tutti gli elementi nella lista
	while (!this->empty())
	{
		this->erase(begin());
	}
	//se la testa e' diversa da un puntatore nullo la dealloco
	delete phead;
	phead = nullptr;
}

//metodo public
template <class T>
linkedlist<T> &linkedlist<T>::operator=(const linkedlist<T> &list)
{
	if (!(*this == list))
	{
		//^elimino il vecchio stato
		while (!this->empty())
		{
			this->erase(begin());
		}
		delete phead;
		phead = nullptr;
		lenght = 0;
		//^creo  il nuovo stato
		this->create();
		phead = new listnode<T>;
		phead->next = phead;
		phead->prev = phead;
		if (!list.empty())
		{
			position pos2 = list.begin();
			while (!list.end(pos2))
			{
				this->push_back(list.read(pos2));
				pos2 = pos2->next;
			}
		}
	}
	return *(this);
}

//metodo public
template <class T>
bool linkedlist<T>::operator==(const linkedlist<T> &list) const
{
	if (this->size() != list.size())
	{
		return (false);
	}
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
	return (true);
}

template <class T>
bool linkedlist<T>::operator!=(const linkedlist<T> &list) const
{
	return (!(*this == list));
}

template <class T>
linkedlist<T>::linkedlist(const linkedlist<T> &list)
{
	//inizializzo lo stato
	this->create();
	phead = new listnode<T>;
	phead->next = phead;
	phead->prev = phead;
	//copio gli elementi del secondo oggetto nel primo
	if (!list.empty())
	{
		position pos2 = list.begin();
		while (!list.end(pos2))
		{
			this->push_back(list.read(pos2));
			pos2 = pos2->next;
		}
	}
}

template <>
void linkedlist<int>::move_min_max()
{
	if (!empty())
	{
		//cerco la posizione del minimo
		position minpos = begin();
		for (auto pos = begin(); !end(pos); pos = next(pos))
		{
			if (read(pos) < read(minpos))
			{
				minpos = pos;
			}
		}
		this->exchange(begin(), minpos);
		//cerco la posizione del massimo
		position maxpos = begin();
		for (auto pos = begin(); !end(pos); pos = next(pos))
		{
			if (read(pos) > read(maxpos))
			{
				maxpos = pos;
			}
		}
		this->exchange(last(), maxpos);
	}
}

template <class T>
void linkedlist<T>::difference(const linkedlist<T> &list)
{
	linkedlist<T> list_difference;
	if (!empty())
	{
		//rimuovo gli elementi in comune con la lista B
		for (auto i = begin(); !end(i); i = next(i))
		{
			if (!list.member(read(i)))
			{
				list_difference.push_back(read(i));
			}
		}
	}
	//assegno alla lista implicita A , la nuova lista differenza
	*this = list_difference;
}

#endif
