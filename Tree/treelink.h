#ifndef TREELINK_H
#define TREELINK_H

#include <iostream>
#include "tree.h"
#include "./../queque/pnqueque.h"
using namespace std;

template <class I>
class treelink;

template <class I>
class treenode
{
	friend class treelink<I>;

public:
	treenode()
	{
		first = nullptr;
		next = nullptr;
		parent = nullptr;
		level = 0;
	}
	treenode(I el)
	{
		first = nullptr;
		next = nullptr;
		parent = nullptr;
		item = el;
		level = 0;
	}

private:
	treenode<I> *parent;
	treenode<I> *first;
	treenode<I> *next;
	I item;
	int level;
};

template <class I>
class treelink : public tree<I, treenode<I> *>
{
public:
	//definisco un alias per i tipi: item e nodo
	typedef typename tree<I, treenode<I> *>::item item;
	typedef treenode<I> *node;
	//costruttore
	treelink();
	//distruttore
	~treelink();
	//metodo che inizializza l'albero n-ario
	void create();
	//metodo che restituisce vero se l'albero n-ario e' vuoto
	bool empty() const;
	//metodo che alloca e innesta la radice
	void insRoot();
	//metodo che inserisce un nuovo primo figlio al nodo a cui si applica con un item
	void insFirstChild(node, item);
	//metodo che inserisce un nuovo nodo fratello al nodo a cui si applica con un item
	void insNextSibiling(node, item);
	//metodo che restituisce il riferimento alla radice
	node getRoot() const;
	//metodo che restituisce il riferimento del nodo genitore al nodo a cui si applica
	node parent(node) const;
	//metodo che restituisce vero se un nodo e' foglia
	bool leaf(node) const;
	//metodo che restituisce il riferimento al primo figlio
	node firstChild(node) const;
	//metodo che restituisce vero se il nodo e' ultimo fratello
	bool lastSibiling(node) const;
	//metodo che restituisce il riferimento al successivo fratello
	node nextSibiling(node) const;
	//metodo che inserisce e innesta un sottoalbero come primo figlio del nodo a cui si applica
	void insFirstSubTree(node, treelink<I> &);
	//metodo che inserisce e innesta un sottoalbero come prossimo fratello del nodo a cui si applica
	void insSubTree(node, treelink<I> &);
	//metodo che effettua la rimozione del sottoalbero radicato in n
	void removeSubTree(node);
	//metodo che modifica il valore di un nodo con un item
	void write(node, item);
	//metodo che restituisce l'item di un nodo
	item read(node) const;
	/**algoritmi di visita**/
	//&visite eseguite in dfs usando quindi la ricerca in profondita'
	//metodo che esegue una visita in preordine
	void preorder(node) const;
	//metodo che esegue una visita in post ordine
	void postorder(node) const;
	//metodo che esegue una visita in ampiezza
	void bfs(node) const;
	//^^^funzioni di servizio
	//metodo che stampa un sottoalbero radicato in n
	void print(node) const;
	//metodo che stampa l'intero albero n-ario
	void print() const;

private:
	treenode<I> *root;
};

template <class I>
treelink<I>::treelink()
{
	this->create();
}

template <class I>
treelink<I>::~treelink()
{
	if (!empty())
	{
		this->removeSubTree(root);
	}
	delete root;
	root = nullptr;
}

template <class I>
void treelink<I>::create()
{
	root = nullptr;
}

template <class I>
bool treelink<I>::empty() const
{
	return (root == nullptr);
}

template <class I>
void treelink<I>::insRoot()
{
	if (this->empty())
	{
		root = new treenode<I>;
	}
}

template <class I>
void treelink<I>::insFirstChild(node nodeparent, item el)
{
	if (!this->empty())
	{
		node newchild = new treenode<I>(el);
		newchild->level = nodeparent->level + 1;
		newchild->parent = nodeparent;
		newchild->next = nodeparent->first;
		nodeparent->first = newchild;
	}
}

template <class I>
void treelink<I>::insNextSibiling(node nodechild, item el)
{
	if (nodechild != root)
	{
		if (nodechild != nullptr)
		{
			node newsibiling = new treenode<I>(el);
			newsibiling->level = nodechild->level;
			newsibiling->parent = nodechild->parent;
			newsibiling->next = nodechild->next;
			nodechild->next = newsibiling;
		}
	}
}

template <class I>
typename treelink<I>::node treelink<I>::getRoot() const
{
	return (root);
}

template <class I>
typename treelink<I>::node treelink<I>::parent(node n) const
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
bool treelink<I>::leaf(node n) const
{
	return (n->first == nullptr);
}

template <class I>
typename treelink<I>::node treelink<I>::firstChild(node n) const
{
	if (!leaf(n))
	{
		return (n->first);
	}
	else
	{
		return (n);
	}
}

template <class I>
bool treelink<I>::lastSibiling(node n) const
{
	return (n->next == nullptr);
}

template <class I>
typename treelink<I>::node treelink<I>::nextSibiling(node n) const
{
	if (!lastSibiling(n))
	{
		return (n->next);
	}
	else
	{
		return (n);
	}
}

template <class I>
void treelink<I>::insFirstSubTree(node nodeparent, treelink<I> &tree)
{
	if (!this->empty() && !tree.empty())
	{
		if (nodeparent != nullptr)
		{
			node nodechild = nodeparent->first;
			nodeparent->first = tree.root;
			tree.root->parent = nodeparent;
			tree.root->next = nodechild;
			tree.root = nullptr;
		}
		else
		{
			cout << "\nnodo nullo insFirstSubTree\n";
		}
	}
}

template <class I>
void treelink<I>::insSubTree(node nodechild, treelink<I> &tree)
{
	if (!this->empty() && !tree.empty() && (nodechild != root))
	{
		if (nodechild != nullptr)
		{
			node nodesibiling = nodechild->next;
			nodechild->next = tree.root;
			tree.root->parent = nodechild->parent;
			tree.root->next = nodesibiling;
			tree.root = nullptr;
		}
	}
}

template <class I>
void treelink<I>::removeSubTree(node n)
{
	if (n != nullptr)
	{
		node i;
		if (!leaf(n))
		{
			for (i = firstChild(n); !lastSibiling(i); i = nextSibiling(i))
			{
				removeSubTree(i);
			}
			removeSubTree(i);
		}
		if (leaf(n))
		{
			if (n != root)
			{
				if (n == n->parent->first)
				{
					n->parent->first = n->next;
				}
				else
				{
					i = n->parent->first;
					while (i->next != n)
					{
						i = i->next;
					}
					i->next = n->next;
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
void treelink<I>::write(node n, item el)
{
	if (n != nullptr)
	{
		n->item = el;
	}
	else
	{
		cout << "\nnodo nullo scrittura\n";
	}
}

template <class I>
typename treelink<I>::item treelink<I>::read(node n) const
{
	item item; //elemento vuoto
	if (n != nullptr)
	{
		return (n->item);
	}
	return (item);
}

template <class I>
void treelink<I>::preorder(node n) const
{
	if (n != nullptr)
	{
		node child;
		cout << "\nitem: " << read(n) << " level: " << n->level; //(1) preorder
		if (!leaf(n))
		{
			child = firstChild(n);
			while (!lastSibiling(child))
			{
				preorder(child);
				child = nextSibiling(child);
			}
			preorder(child);
		}
	}
}

template <class I>
void treelink<I>::postorder(node n) const
{
	if (n != nullptr)
	{
		node child;
		if (!leaf(n))
		{
			child = firstChild(n);
			while (!lastSibiling(child))
			{
				postorder(child);
				child = nextSibiling(child);
			}
			postorder(child);
		}
		cout << "\nitem: " << read(n); //(2) postorder
	}
}

template <class I>
void treelink<I>::bfs(node n) const
{
	if (n != nullptr)
	{
		pnqueque<node> queque;
		queque.enqueque(n);
		while (!queque.empty())
		{
			node i = queque.top();
			queque.dequeque();
			//esame per livelli del nodo i
			cout << " (" << read(i) << ") ";
			i = i->first;
			while (i != nullptr)
			{
				queque.enqueque(i);
				i = i->next;
			}
		}
	}
}


template <class I>
void treelink<I>::print(node n) const
{
	node p;
	cout << read(n) << ":";
	if (!leaf(n))
	{
		p = firstChild(n);
		while (!lastSibiling(p))
		{
			cout << " " << read(p);
			p = nextSibiling(p);
		}
		cout << " " << read(p) << "\n";
		p = firstChild(n);
		while (!lastSibiling(p))
		{
			print(p);
			p = nextSibiling(p);
		}
		print(p);
	}
	else
	{
		cout << "\n";
	}
}

template <class I>
void treelink<I>::print() const
{
	if (!empty())
	{
		this->print(root);
	}
}

#endif
