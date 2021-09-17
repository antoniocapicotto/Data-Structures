#ifndef PNBINTREE_H
#define PNBINTREE_H

#include <iostream>
#include <string>
#include "bintree.h"
using namespace std;

//dichiaro la classe albero binario
template <class I>
class pnbintree;

//creo la classe nodo del mio albero binario
template <class I>
class bintreenode
{
	friend class pnbintree<I>;

public:
	bintreenode()
	{
		parent = nullptr;
		sx = nullptr;
		dx = nullptr;
		level = 0;
		depth = 0;
	}
	bintreenode(I el)
	{
		parent = nullptr;
		sx = nullptr;
		dx = nullptr;
		item = el;
		level = 0;
		depth = 0;
	}

private:
	bintreenode<I> *parent; //riferimento al nodo genitore
	bintreenode<I> *sx;		//riferimento al nodo sinistro
	bintreenode<I> *dx;		//riferimento al nodo destro
	I item;					//valore associato al nodo
	int level;				//altezza del nodo(numero di nodi che ci sono sotto n)
	int depth;				//campo intero relativo alla profondita' del nodo
};

template <class I>
class pnbintree : public bintree<I, bintreenode<I> *>
{
public:
	//definisco gli alias per il tipo generico typeitem e il tipo nodo
	typedef typename bintree<I, bintreenode<I> *>::item item; //tipoelem
	typedef bintreenode<I> *node;							  //tiponodo
	//&costruttore
	pnbintree();
	//&costruttore di copia
	pnbintree(const pnbintree<I> &);
	//metodo che inizializza l'albero binario
	void create();
	//&?metodo che restituisce un boolean, ed indica se l'albero e' vuoto
	bool empty() const;
	//metodo che restituisce il riferimento alla radice
	node get_root() const;
	//metodo che restituisce il riferimento al genitore
	node parent(node) const;
	//metodo che restituisce il nodo sinistro al nodo a cui si applica la funzione
	node sx(node) const;
	//metodo che restituisce il reiferimento al figlio destro
	node dx(node) const;
	//&?metodo che restituisce vero se il figlio sinistro e' vuoto
	bool sx_empty(node) const;
	//&?metodo che restituisce vero se il figlio destro e' vuoto
	bool dx_empty(node) const;
	//&?metodo che restituisce vero se il nodo e' foglia
	bool leaf(node) const;
	//metodo che restituisce un valore letto in posizione del nodo n
	item read(node) const;
	//metodo che modifica il valore di un nodo
	void write(node, item);
	//metodo che alloca la radice
	void ins_root();
	//metodo che inserisce un figlio sinistro con un valore preso in input
	void ins_sx(node, item);
	//metodo che inserisce un sottoalbero t come figlio sinistro di n
	void ins_sub_sx(node, pnbintree<I> &);
	//metodo che inserisce un figlio destro con un valore preso in input
	void ins_dx(node, item);
	//metodo che inserisce un sottoalbero t come figlio destro di n
	void ins_sub_dx(node, pnbintree<I> &);
	//metodo che cancella un sottoalbero
	void erase(node);
	//& algoritmi di visita dfs (depth first search)
	//visita in preordine dell'albero
	void preorder(node) const;
	//visita simmetrica dell'albero
	void inorder(node) const;
	//visita in postordine dell'albero
	void postorder(node) const;
	//^funzioni utili
	//metodo che cancella da un albero di interi tutte le foglie con valore pari
	void canc_foglie_pari();
	//metodo che cancella da un sottoalbero di interi tutte le folgie pari
	void canc_foglie_pari(bintreenode<int> *);
	//metodo che restituisce vero se un nodo ha valore nullo
	bool is_empty_node(node) const;
	//&metodo che restituisce la profondita' di un sottoalbero radicato in n
	int depth(node) const;
	//metodo che restituisce la profondita' dell'albero binario
	int depth() const;
	//&metodo che permette di costruire un albero binario avendo come figlio sinisetro l'oggetto this e figlio destro tree
	void costr_bintree(pnbintree<I> &);
	//^metodo che permette di incrementare il livello di tutti i nodi
	void increase_level(node);
	//^metodo che restituisce il livello del nodo a cui si applica
	int get_level(node) const;
	//^metodo che scrive il valore del nodo con un intero l
	void write_level(node, int);
	//^metodo che restituisce un sottoalbero a partire dal nodo a cui si applica
	node get_sub_bintree(node);
	/*
 	* Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A
 	* e v appartenente a B, implementare la funzione mutation che scambia i
 	* sottoalberi con radice u e v.
 	*/
	void mutation(node, node, pnbintree<I> &);
	//&**sovraccarico operatori**
	//~assegnamento
	pnbintree<I> &operator=(const pnbintree<I> &);
	//~distruttore della classe albero binario
	~pnbintree();

private:
	//riferimento alla radice dell'albero
	bintreenode<I> *root;
};

template <class I>
pnbintree<I>::pnbintree()
{
	this->create();
}

template <class I>
void pnbintree<I>::create()
{
	root = nullptr;
}

template <class I>
pnbintree<I>::pnbintree(const pnbintree<I> &bintree)
{
	this->create();
	root = get_sub_bintree(bintree.root);
}

template <class I>
bool pnbintree<I>::empty() const
{
	return (root == nullptr);
}

template <class I>
typename pnbintree<I>::node pnbintree<I>::get_root() const
{
	return (root);
}

template <class I>
typename pnbintree<I>::node pnbintree<I>::parent(node n) const
{
	if (n != root)
	{
		return (n->parent);
	}
	else
	{
		return (n);
	}
}

template <class I>
typename pnbintree<I>::node pnbintree<I>::sx(node n) const
{
	return (n->sx);
}

template <class I>
typename pnbintree<I>::node pnbintree<I>::dx(node n) const
{
	return (n->dx);
}

template <class I>
bool pnbintree<I>::sx_empty(node n) const
{
	return (n->sx == nullptr);
}

template <class I>
bool pnbintree<I>::dx_empty(node n) const
{
	return (n->dx == nullptr);
}

template <class I>
bool pnbintree<I>::leaf(node n) const
{
	return ((n->sx == nullptr) && (n->dx == nullptr));
}

template <class I>
typename pnbintree<I>::item pnbintree<I>::read(node n) const
{
	item item; //valore vuoto
	if (n != nullptr)
	{
		return (n->item);
	}
	return (item);
}

template <class I>
void pnbintree<I>::write(node n, item el)
{
	if (n != nullptr)
	{
		n->item = el;
	}
}

template <class I>
void pnbintree<I>::ins_root()
{
	if (this->empty())
	{
		root = new bintreenode<I>;
	}
}

template <class I>
void pnbintree<I>::ins_sx(node parent, item el)
{
	if (!empty() && (parent != nullptr))
	{
		if (sx_empty(parent))
		{
			//creo il nodo da inserire
			node child = new bintreenode<I>(el);
			//inserisco il livello di altezza dell'albero
			child->level = parent->level + 1;
			//inserisco il nodo come figlio sinistro
			child->parent = parent;
			parent->sx = child;
		}
		else
		{
			//cambio solo il valore
			parent->sx->item = el;
		}
	}
}

template <class I>
void pnbintree<I>::ins_dx(node parent, item el)
{
	if (!empty() && (parent != nullptr))
	{
		if (dx_empty(parent))
		{
			//creo il nodo da inserire con valore e
			node child = new bintreenode<I>(el);
			child->level = parent->level + 1;
			//innesto il nodo child con genitore parent
			child->parent = parent;
			parent->dx = child;
		}
		else
		{
			//il nodo esiste e quindi cambio solo l'item
			parent->dx->item = el;
		}
	}
}

template <class I>
void pnbintree<I>::erase(node n)
{
	//algoritmo che cancella ricorsivamente un sottoalbero radicato in n
	if (n != nullptr && !empty())
	{
		if (!sx_empty(n))
		{
			erase(n->sx);
		}
		if (!dx_empty(n))
		{
			erase(n->dx);
		}
		if (leaf(n))
		{
			if (n != root)
			{
				node p = n->parent;
				if (p != nullptr)
				{
					if (n == p->sx)
					{
						p->sx = nullptr;
					}
					else
					{
						p->dx = nullptr;
					}
				}
			}
			else
			{
				root = nullptr;
			}
			delete n;
			n = nullptr;
		}
	}
}

template <class I>
void pnbintree<I>::preorder(node n) const
{
	if (n != nullptr)
	{
		cout << "\nnode: " << read(n) << " level: " << n->level << " depth: " << (n->depth = depth(n)); //preorder
		preorder(n->sx);
		preorder(n->dx);
	}
}

template <class I>
void pnbintree<I>::inorder(node n) const
{
	if (n != nullptr)
	{
		inorder(n->sx);
		cout << " " << read(n) << " "; //inorder
		inorder(n->dx);
	}
}

template <class I>
void pnbintree<I>::postorder(node n) const
{
	if (n != nullptr)
	{
		postorder(n->sx);
		postorder(n->dx);
		cout << " " << read(n) << " "; //postorder
	}
}

template <class I>
pnbintree<I>::~pnbintree()
{
	if (!empty())
	{
		//elimino il sotto albero radicato nella radice
		this->erase(root);
	}
	//imposto la radice a nullpointer
	root = nullptr;
}

template <>
void pnbintree<int>::canc_foglie_pari(bintreenode<int> *subroot)
{
	if (subroot == nullptr)
	{
		return;
	}
	if (!leaf(subroot))
	{
		canc_foglie_pari(subroot->sx);
		canc_foglie_pari(subroot->dx);
	}
	if (leaf(subroot) && (subroot->item % 2 == 0))
	{
		erase(subroot);
	}
}

template <>
void pnbintree<int>::canc_foglie_pari()
{
	this->canc_foglie_pari(this->get_root());
}

template <class I>
bool pnbintree<I>::is_empty_node(node n) const
{
	return (n == nullptr);
}

template <class I>
int pnbintree<I>::depth(node sub_root) const
{
	if (sub_root == nullptr)
	{
		return (-1); //nodo nullo
	}
	int left_depth = depth(sub_root->sx);
	int right_depth = depth(sub_root->dx);
	if (left_depth > right_depth)
	{
		return (left_depth + 1);
	}
	else
	{
		return (right_depth + 1);
	}
}

template <class I>
int pnbintree<I>::depth() const
{
	return depth(this->get_root());
}

template <class I>
void pnbintree<I>::ins_sub_sx(node parent, pnbintree<I> &tree)
{
	if (!empty() && (parent != nullptr))
	{
		if (sx_empty(parent))
		{
			//incremento il livello di tutti i nodi
			increase_level(tree.root);
			//innesto la radice del sottoalbero come figlio sinistro del nodo a cui si applica
			parent->sx = tree.root;
			tree.root->parent = parent;
			tree.root = nullptr;
		}
	}
}

template <class I>
void pnbintree<I>::ins_sub_dx(node parent, pnbintree<I> &tree)
{
	if (!empty() && (parent != nullptr))
	{
		if (dx_empty(parent))
		{
			increase_level(tree.root);
			parent->dx = tree.root;
			tree.root->parent = parent;
			tree.root = nullptr;
		}
	}
}

template <class I>
void pnbintree<I>::increase_level(node n)
{
	if (n == nullptr)
	{
		return;
	}
	increase_level(n->sx);
	increase_level(n->dx);
	n->level++;
}

template <class I>
void pnbintree<I>::costr_bintree(pnbintree<I> &tree)
{
	node newroot = new bintreenode<I>(item(NULL));
	ins_sub_sx(newroot, *this);
	ins_sub_dx(newroot, tree);
	root = newroot;
}

template <class I>
int pnbintree<I>::get_level(node n) const
{
	int level = 0;
	if (!empty())
	{
		if (n != nullptr)
		{
			level = n->level;
		}
	}
	else
	{
		level = -1; //albero vuoto
	}
	return (level);
}

template <class I>
void pnbintree<I>::write_level(node n, int l)
{
	if (!empty())
	{
		if (n != nullptr)
		{
			n->level = l;
		}
	}
}

template <class I>
typename pnbintree<I>::node pnbintree<I>::get_sub_bintree(node i)
{
	//copia tutti i nodi a partire da i e li mette in temp
	if (i != nullptr)
	{
		node temp = new bintreenode<I>;
		node sx = new bintreenode<I>;
		node dx = new bintreenode<I>;
		temp->item = i->item;
		temp->level = i->level;
		temp->parent = i->parent; //se i era radice, prende nullptr, altrimenti prende il padre
		sx = get_sub_bintree(i->sx);
		temp->sx = sx;
		dx = get_sub_bintree(i->dx);
		temp->dx = dx;
		return (temp);
	}
	else
	{
		return (nullptr);
	}
}

template <class I>
pnbintree<I> &pnbintree<I>::operator=(const pnbintree<I> &bintree)
{
	//cancello il vecchio stato
	if (!empty())
	{
		this->erase(root);
	}
	root = nullptr;
	//copio il nuovo stato
	root = this->get_sub_bintree(bintree.root);
	return *(this);
}

template <class I>
void pnbintree<I>::mutation(node u, node v, pnbintree<I> &bintree)
{
	if ((u != root) && (v != root))
	{
		if (u == u->parent->sx)
		{
			u->parent->sx = v;
		}
		else
		{
			u->parent->dx = v;
		}
		if (v == v->parent->sx)
		{
			v->parent->sx = u;
		}
		else
		{
			v->parent->dx = u;
		}
		node parent = u->parent;
		u->parent = v->parent;
		v->parent = u->parent;
	}
}

#endif
