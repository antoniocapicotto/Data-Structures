#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <iostream>
#include <string>
using namespace std;

template <class T, class P>
class linearlist
{
public:
	//definizione di del tipo generico typevalue e del tipo posizione
	typedef T value_type;
	typedef P position;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual value_type read(position) const = 0;
	virtual void write(value_type, position) = 0;  //write x in position p
	virtual position begin() const = 0;			   //return the first position pointing the beginning of the list
	virtual bool end(position) const = 0;		   //return true if p is the last position pointing the end of the list
	virtual position last() const = 0;			   //returns the position of the last element of the list
	virtual position next(position) const = 0;	   //return next position
	virtual position previous(position) const = 0; //return the previous position
	virtual void insert(value_type, position) = 0;
	virtual void erase(position) = 0;
	/*			****			funzioni di servizio			****		*/
	//metodo che permette di stampare tutti gli elementi di una lista
	friend ostream &operator<<(ostream &os, const linearlist<T, P> &l)
	{
		linearlist<T, P>::position p;
		p = l.begin();
		os << "[";
		while (!l.end(p))
		{
			if (p != l.begin())
			{
				os << ", " << l.read(p);
			}
			else
			{
				os << l.read(p);
			}
			p = l.next(p);
		}
		os << "]" << endl;
		return (os);
	}
	// metodo che restituisce la lunghezza della lista ovvero il numero di elementi
	int size() const;
	//metodo che inserisce un item v in testa alla lista
	void push_front(value_type);
	/*metodo che inserisce un elemento v in fondo alla lista, il valore viene quindi inserito nella posizione
	 successiva all'ultimo elemento */
	void push_back(value_type);
	//metodo che rimuove l'elemento in testa alla lista
	void pop_front();
	//metodo che rimuove l'elemento in fondo alla lista
	void pop_back();
	//metodo che pulisce la lista e restituisce una lista vuota priva di elementi
	void clear();
	//distruttore della classe astratta
	virtual ~linearlist(){};
	//metodo che inverte gli elementi di una lista
	void reverse();
	//metodo che restituisce vero se una lista e' palindroma
	bool palindroma() const;
	//metodo che rimuove un item dalla lista
	void remove(value_type);
	//metodo che calcola il numero di elementi compresi fra le posizioni p1 e p2
	int num_elements(position, position);
	//scambia l'elemento in posizione p1 con quello in posizione p2
	void exchange(position, position);
	//metodo che restituisce vero se l'elemento appartiene alla lista
	bool member(value_type) const;
};

//metodo public
template <class T, class P>
int linearlist<T, P>::size() const
{
	int count = 0;
	for (auto pos = begin(); !end(pos); pos = next(pos))
	{
		count++;
	}
	return (count);
}

//metodo public
template <class T, class P>
void linearlist<T, P>::push_front(value_type el)
{
	insert(el, begin());
}

//metodo public
template <class T, class P>
void linearlist<T, P>::push_back(value_type el)
{
	insert(el, next(last()));
}

//metodo public
template <class T, class P>
void linearlist<T, P>::pop_front()
{
	erase(begin());
}

//metodo public
template <class T, class P>
void linearlist<T, P>::pop_back()
{
	erase(last());
}

//metodo public
template <class T, class P>
void linearlist<T, P>::clear()
{
	while (!this->empty())
	{
		this->pop_front();
	}
}

template <class T, class P>
void linearlist<T, P>::reverse()
{
	auto poslast = last();
	int lunghezza_media = this->size() / 2;
	int i = 0;
	for (auto pos = begin(); !end(pos) && (i < lunghezza_media); pos = next(pos))
	{
		T temp = read(pos);
		write(read(poslast), pos);
		write(temp, poslast);
		poslast = previous(poslast);
		i++;
	}
}

template <class T, class P>
bool linearlist<T, P>::palindroma() const
{
	if (this->size() < 2)
	{
		return (true);
	}
	else
	{
		//verfico se la lista e' palindroma
		bool flag = true;
		auto prev = last();
		for (auto curr = begin(); !end(curr) && (flag); curr = next(curr))
		{
			if (read(curr) != read(prev))
			{
				flag = false;
			}
			prev = previous(prev);
		}
		return (flag);
	}
}

template <class T, class P>
void linearlist<T, P>::remove(value_type el)
{
	bool found = false;
	auto pos = begin();
	while (!end(pos) && !found)
	{
		if (read(pos) == el)
		{
			found = true;
		}
		else
		{
			pos = next(pos);
		}
	}
	if (found)
	{
		this->erase(pos);
	}
}

template <class T, class P>
int linearlist<T, P>::num_elements(position p1, position p2)
{
	int n = 0;
	auto pos = p1;
	while (!end(pos) && next(pos) != p2)
	{
		n++;
		pos = next(pos);
	}
	return (n);
}

template <class T, class P>
void linearlist<T, P>::exchange(position p1, position p2)
{
	if (!empty() && (p1 != p2))
	{
		T temp = read(p1);
		write(read(p2), p1);
		write(temp, p2);
	}
}

template <class T, class P>
bool linearlist<T, P>::member(value_type el) const
{
	bool found = false;
	if (!empty())
	{
		for (auto i = begin(); !end(i) && !found; i = next(i))
		{
			if (read(i) == el)
			{
				found = true;
			}
		}
	}
	return (found);
}

#endif
