#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include "dictionary.h"
#include "./../list/listvector.h"
using namespace std;

template <class T>
class hash_
{
public:
	size_t operator()(const T the_key) const;
};

/*a specialization with type string*/
template <>
class hash_<string>
{
public:
	size_t operator()(const string the_key) const
	{
		unsigned long hash_value = 0;
		int lenght = (int)the_key.length();
		for (int i = 0; i < lenght; i++)
		{
			hash_value = 5 * hash_value + the_key.at(i);
		}
		return (size_t(hash_value));
	}
};

//struttura che contiene una coppia chiave-valore
template <class K, class E>
struct mypair;

//classe dizionario come hashtable
template <class K, class E>
class hashtable : public dictionary<K, E>
{
public:
	//definisco i tipi
	typedef typename dictionary<K, E>::key key;		//tipo chiave
	typedef typename dictionary<K, E>::label label; //tipo etichetta
	typedef listvector<label> listvalues;			//tipo listaelementi o listavalori
	typedef listvector<key> listkeys;				//tipo listachiavi
	typedef listvector<mypair<K, E>> listpair;		//tipo listacoppie
	//costruttore
	hashtable();
	//costruttore con parametro
	hashtable(int);
	//metodo che inizializza la hashtable
	void create();
	//metodo che restituisce vero se la hashtable e' vuota
	bool empty() const;
	//metodo che restituisce il totale delle coppie presenti della hashtable
	int size() const;
	//metodo che ricerca la posizione nel vettore  di coppie a partire da una chiave k
	int search(const K &) const;
	//metodo che restituisce il riferimento da una coppia della hashtable a partire dalla chiave k
	mypair<K, E> *find(const K &) const;
	//metodo che inserisce una coppia nella hashtable
	void insert(mypair<K, E> &);
	//metodo che restituisce vero se la chiave k e' presente nella hahstable
	bool member(const K &) const;
	//metodo che rimuove una coppia con chiave k
	void remove(const K &);
	//metodo che modifica il valore di una chiave con un nuovo valore
	void modify(const K &, const E &);
	//metodo che recupera il valore da una chiave k
	const E &retrieves(const K &);
	//metodo che restituisce vero se una o piu' chiavi contengono l'elemento
	bool containsValue(const E &);
	//metodo che restituisce vero se la coppia chiave-valore e' presente nella hashtable
	bool containsPair(const mypair<K, E> &);
	//metodo che stampa la lista di tutte le chiavi presenti nella hashtable
	void printkeys();
	//metodo che restituisce la lista di tutti i valori o gli elementi della hashtable
	listvalues values();
	//metodo che restituisce la lista di tutte le chiavi della hashtable
	listkeys keys();
	//metodo che raddoppia la massima capienza della tabella mantenendo gli stessi elementi
	void resize();
	//metodo che restituisce vero se il primo dizionario e' sottoinsieme del secondo
	bool sottoinsieme(const hashtable<K, E> &);
	//metodo che restituisce il valore del divisore
	int divisor_size() const;
	/**sovraccarico operatore di uguaglianza**/
	//&uguaglianza
	bool operator==(const hashtable<K, E> &);
	//distruttore
	~hashtable();

private:
	mypair<K, E> **table; //the hash table
	hash_<K> hashmap;	  //maps type K to nonnegative integer
	int s;				  //number of pairs in dictionary
	int divisor;		  //hash function divisor
};

template <class K, class E>
hashtable<K, E>::hashtable(int the_divisor)
{
	this->create();
	divisor = the_divisor;
	table = new mypair<K, E> *[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
}

template <class K, class E>
hashtable<K, E>::hashtable()
{
	this->create();
	divisor = 100;
	table = new mypair<K, E> *[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
}

template <class K, class E>
void hashtable<K, E>::create()
{
	s = 0;
}

template <class K, class E>
bool hashtable<K, E>::empty() const
{
	return (s == 0);
}

template <class K, class E>
int hashtable<K, E>::size() const
{
	return (s);
}

template <class K, class E>
int hashtable<K, E>::search(const K &the_key) const
{
	int i = (int)hashmap(the_key) % divisor; //the home bucket
	int j = i;
	do
	{
		if ((table[j] == nullptr) || (table[j]->first == the_key))
		{
			return j;
		}
		j = (j + 1) % divisor; // the next bucket

	} while (j != i);

	return (j); //full table
}

template <class K, class E>
mypair<K, E> *hashtable<K, E>::find(const K &the_key) const
{
	//search the table
	int b = search(the_key);
	//see if a match was found at table[b]
	if ((table[b] == nullptr) || (table[b]->first != the_key))
	{
		return (nullptr); //no match found
	}
	return (table[b]); //matching pair
}

template <class K, class E>
void hashtable<K, E>::insert(mypair<K, E> &the_pair)
{
	if (!member(the_pair.first))
	{
		int b = search(the_pair.first);
		//chack if matching element found
		if (table[b] == nullptr)
		{
			//no matching element and table not full
			table[b] = new mypair<K, E>(the_pair);
			s++;
		}
		else
		{
			//check id duplicate or table full
			if (table[b]->first == the_pair.first)
			{
				//duplicate, change table[b]->second
				table[b]->second = the_pair.second;
			}
			else
			{
				//table is full
				return;
			}
		}
	}
}

template <class K, class E>
bool hashtable<K, E>::member(const K &the_key) const
{
	if (!this->empty())
	{
		int position = search(the_key);
		if (table[position] != nullptr)
		{
			return (table[position]->first == the_key);
		}
	}
	return (false);
}

template <class K, class E>
void hashtable<K, E>::remove(const K &the_key)
{
	if (member(the_key))
	{
		int position = search(the_key);
		if (table[position]->first == the_key)
		{
			delete table[position];
			table[position] = nullptr;
			s--;
		}
	}
}

template <class K, class E>
void hashtable<K, E>::modify(const K &the_key, const E &the_element)
{
	//verify if dictionary contains the_key
	if (member(the_key))
	{
		int position = search(the_key);
		table[position]->second = the_element;
	}
	else
	{
		cout << "\nno match found";
	}
}

template <class K, class E>
const E &hashtable<K, E>::retrieves(const K &thekey)
{
	const E &element = E(NULL);
	if (member(thekey))
	{
		int position = search(thekey);
		return (table[position]->second);
	}
	return (element); // return null
}

template <class K, class E>
void hashtable<K, E>::printkeys()
{
	listkeys l = keys();
	cout << l;
}

template <class K, class E>
hashtable<K, E>::~hashtable()
{
	if (!this->empty())
	{
		for (int i = 0; i < divisor; i++)
		{
			if (table[i] != nullptr)
			{
				delete table[i];
				table[i] = nullptr;
				s--;
			}
		}
	}
	delete[] table;
	table = nullptr;
}

template <class K, class E>
bool hashtable<K, E>::containsValue(const E &value)
{
	bool found = false;
	if (!this->empty())
	{
		//cerco il valore nel dizionario
		for (int i = 0; (i < divisor) && !found; i++)
		{
			if (table[i] != nullptr)
			{
				if (table[i]->second == value)
				{
					found = true;
				}
			}
		}
	}
	return (found);
}

template <class K, class E>
typename hashtable<K, E>::listvalues hashtable<K, E>::values()
{
	listvalues l;
	if (!this->empty())
	{
		for (int i = 0; i < divisor; i++)
		{
			if (table[i] != nullptr)
			{
				l.push_back(table[i]->second);
			}
		}
	}
	return (l);
}

template <class K, class E>
typename hashtable<K, E>::listkeys hashtable<K, E>::keys()
{
	listkeys l;
	if (!empty())
	{
		for (int i = 0; i < divisor; i++)
		{
			if (table[i] != nullptr)
			{
				l.push_back(table[i]->first);
			}
		}
	}
	return (l);
}

template <class K, class E>
void hashtable<K, E>::resize()
{
	//salvo in una lista tutte le coppie chiave valore
	listpair l;
	for (int i = 0; i < divisor; i++)
	{
		if (table[i] != nullptr)
		{
			mypair<K, E> pair_copy = *(table[i]);
			l.push_back(pair_copy);
		}
	}
	//cancello il vecchio stato
	for (int i = 0; i < divisor; i++)
	{
		if (table[i] != nullptr)
		{
			delete table[i];
			table[i] = nullptr;
			s--;
		}
	}
	delete[] table;
	table = nullptr;
	//creo il nuovo stato dell'oggetto raddoppiando il divisore
	this->create();
	divisor = divisor * 2;
	table = new mypair<K, E> *[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
	if (!l.empty())
	{
		for (auto i = l.begin(); !l.end(i); i = l.next(i))
		{
			mypair<K, E> pair;
			pair.first = l.read(i).first;
			pair.second = l.read(i).second;
			this->insert(pair);
		}
	}
}

template <class K, class E>
int hashtable<K, E>::divisor_size() const
{
	return (divisor);
}

template <class K, class E>
bool hashtable<K, E>::operator==(const hashtable<K, E> &h)
{
	if (this->size() != h.size())
	{
		return (false);
	}
	listpair l1;
	for (int i = 0; i < divisor; i++)
	{
		if (table[i] != nullptr)
		{
			mypair<K, E> pair_copy = *(table[i]);
			l1.push_back(pair_copy);
		}
	}
	listpair l2;
	for (int i = 0; i < h.divisor; i++)
	{
		if (h.table[i] != nullptr)
		{
			mypair<K, E> pair_copy = *(h.table[i]);
			l2.push_back(pair_copy);
		}
	}
	return (l1 == l2);
}

template <class K, class E>
bool hashtable<K, E>::sottoinsieme(const hashtable<K, E> &h)
{
	bool found = true;
	for (int i = 0; (i < divisor) && found; i++)
	{
		if (table[i] != nullptr)
		{
			if (h.find(table[i]->first) == nullptr)
			{
				found = false;
			}
			else
			{
				found = (*(table[i]) == *(h.find(table[i]->first)));
			}
		}
	}
	return (found);
}

template <class K, class E>
bool hashtable<K, E>::containsPair(const mypair<K, E> &pair)
{
	bool found = false;
	for (int i = 0; (i < divisor) && !found; i++)
	{
		if (table[i] != nullptr)
		{
			found = (*(table[i]) == pair);
		}
	}
	return (found);
}

#endif
