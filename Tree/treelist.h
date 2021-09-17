#ifndef TREELIST_H
#define TREELIST_H

#include <iostream>
#include "./../list/listvector.h"
#include "tree.h"
#define MAXNODES 100
using namespace std;

template <class I>
class treelist : public tree<I, int>
{
public:
	typedef typename tree<I, int>::item item; //tipo elemento
	typedef typename tree<I, int>::node node; //tipo nodo
	//costruttore
	treelist();
	//metodo che inizializza l'albero
	void create();
	//metodo che restituisce vero se l'albero e' vuoto
	bool empty() const;
	//metodo che alloca e innesta la radice
	void insRoot();
	//metodo che restituisce il riferimento alla radice
	node getRoot() const;
	//metodo che restituisce il riferimento al nodo genitore del nodo a cui si applica
	node parent(node) const;
	//metodo che restituisce vero se un nodo e' foglia
	bool leaf(node) const;
	//metodo che restituisce il riferimento del primo figlio
	node firstChild(node) const;
	//metodo che restituisce vero se il nodo a cui si applica e' ultimo fratello
	bool lastSibiling(node) const;
	//metodo che restituisce il riferimento al fratello successivo
	node nextSibiling(node) const;
	//inserisce un primo figlio al nodo a cui si applica con un item
	void insFirstChild(node, item);
	//inserisce un nodo come fratello del nodo a cui si applica con un item
	void insNextSibiling(node, item);
	//metodo che effettua la rimozione del sottoalbero radicato nel nodo a cui si applica
	void removeSubTree(node);
	//metodo che scrive il valore di un nodo con un item
	void write(node, item);
	//metodo che legge il valore del nodo a cui si applica
	item read(node) const;
	//distruttore della classe
	~treelist();
	//metodo che stampa il contenuto dell'albero partendo dal nodo radice
	void print() const;

private:
	struct Record
	{
		item el;
		bool used;
		listvector<int> childs; //vettore dei figli
	};
	typedef listvector<int>::position position; //tipo posizione vettore figli
	Record nodes[MAXNODES];						//vettore dei padri
	node root;									//nodo radice
	int numNodes;								//numero nodi occupati
};

template <class I>
treelist<I>::treelist()
{
	this->create();
}

template <class I>
void treelist<I>::create()
{
	numNodes = 0;
	for (int i = 0; i < MAXNODES; i++)
	{
		nodes[i].used = false;
		nodes[i].childs.create();
	}
}

template <class I>
bool treelist<I>::empty() const
{
	return (numNodes == 0);
}

template <class I>
void treelist<I>::insRoot()
{
	if (this->empty())
	{
		root = 0;
		nodes[0].used = true;
		numNodes++;
	}
}

template <class I>
typename treelist<I>::node treelist<I>::getRoot() const
{
	return (root);
}

template <class I>
typename treelist<I>::node treelist<I>::parent(node n) const
{
	position child;
	int p;
	for (int i = 0; i < MAXNODES; i++)
	{
		if (!nodes[i].childs.empty())
		{
			child = nodes[i].childs.begin();
			bool found = false;
			while (!nodes[i].childs.end(child) && !found)
			{
				if (nodes[i].childs.read(child) == n)
				{
					found = true;
					p = i;
				}
				child = nodes[i].childs.next(child);
			}
			if (found)
			{
				return (p);
			}
		}
	}
	return (n); //nessun nodo trovato
}

template <class I>
bool treelist<I>::leaf(node n) const
{
	return (nodes[n].childs.empty());
}

template <class I>
typename treelist<I>::node treelist<I>::firstChild(node n) const
{
	if (!leaf(n))
	{
		return (nodes[n].childs.read(nodes[n].childs.begin()));
	}
	return (n); //il nodo e' foglia
}

template <class I>
bool treelist<I>::lastSibiling(node n) const
{
	position c;
	node p = parent(n);
	c = nodes[p].childs.begin();
	while (!nodes[p].childs.end(c))
	{
		c = nodes[p].childs.next(c);
	}
	return (n == nodes[p].childs.read(c));
}

template <class I>
typename treelist<I>::node treelist<I>::nextSibiling(node n) const
{
	if (!lastSibiling(n))
	{
		position c;
		node p = parent(n);
		c = nodes[p].childs.begin();
		while (!nodes[p].childs.end(c))
		{
			if (nodes[p].childs.read(c) == n)
			{
				return (nodes[p].childs.read(nodes[p].childs.next(c)));
			}
			c = nodes[p].childs.next(c);
		}
	}
	return (n); //il nodo e' ultimo figlio
}

template <class I>
void treelist<I>::insFirstChild(node n, item el)
{
	//cerca una posizione libera
	int k = 0;
	while ((k < MAXNODES) && (nodes[k].used == true))
	{
		k++;
	}
	if (k < MAXNODES)
	{
		nodes[k].used = true;
		numNodes++;
		nodes[k].el = el;
		nodes[n].childs.push_front(k);
	}
}

template <class I>
void treelist<I>::insNextSibiling(node n, item el)
{
	//cerca una posizione libera
	int k = 0;
	while ((k < MAXNODES) && (nodes[k].used == true))
	{
		k++;
	}
	if (k < MAXNODES)
	{
		nodes[k].used = true;
		numNodes++;
		nodes[k].el = el;
		node p = parent(n);
		position child = nodes[p].childs.begin();
		bool found = false;
		while (!nodes[p].childs.end(child) && !found)
		{
			if (nodes[p].childs.read(child) == n)
			{
				found = true;
			}
			child = nodes[p].childs.next(child);
		}
		nodes[p].childs.insert(k, child);
	}
}

template <class I>
void treelist<I>::removeSubTree(node n)
{
	position c;
	if (!leaf(n))
	{
		while (!nodes[n].childs.empty())
		{
			removeSubTree(nodes[n].childs.read(nodes[n].childs.begin()));
		}
	}
	if (n != root)
	{
		node p = parent(n);
		c = nodes[p].childs.begin();
		while (nodes[p].childs.read(c) != n)
		{
			c = nodes[p].childs.next(c);
		}
		nodes[p].childs.erase(c);
	}
	nodes[n].used = false;
	numNodes--;
}

template <class I>
void treelist<I>::write(node n, item el)
{
	if (nodes[n].used == true)
	{
		nodes[n].el = el;
	}
}

template <class I>
typename treelist<I>::item treelist<I>::read(node n) const
{
	item el;
	if (nodes[n].used == true)
	{
		return (nodes[n].el);
	}
	return (el);
}

template <class I>
treelist<I>::~treelist()
{
	if (!this->empty())
	{
		this->removeSubTree(root);
	}
	numNodes = 0;
}

template <class I>
void treelist<I>::print() const
{
	cout << "\n{";
	for (int i = 0; i < MAXNODES; i++)
	{
		if (nodes[i].used == true)
		{
			cout << "\n " << read(i) << ": ";
			if (!leaf(i))
			{
				position child = nodes[i].childs.begin();
				while (!nodes[i].childs.end(child))
				{
					cout << read(nodes[i].childs.read(child)) << " ";
					child = nodes[i].childs.next(child);
				}
			}
		}
	}
	cout << "\n}\n";
}

#endif
