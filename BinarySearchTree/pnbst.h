#ifndef PNBST_H
#define PNBST_H

#include <iostream>
#include <string>
#include "bst.h"
using namespace std;

//dichiarazione della classe pnbst
template <class K, class E>
class pnbst;

//creo la classe binstreenode
template <class K, class E>
class binstreenode
{
    friend class pnbst<K, E>;

public:
    binstreenode()
    {
        parent = nullptr;
        sx = nullptr;
        dx = nullptr;
    }
    binstreenode(K k, E l)
    {
        parent = nullptr;
        sx = nullptr;
        dx = nullptr;
        key = k;
        label = l;
    }

private:
    binstreenode<K, E> *parent;
    binstreenode<K, E> *sx;
    binstreenode<K, E> *dx;
    K key;
    E label;
};

template <class K, class E>
class pnbst : public bst<K, E, binstreenode<K, E> *>
{
public:
    //definisco i tipi
    typedef typename bst<K, E, binstreenode<K, E> *>::key key;     //tipo chiave
    typedef typename bst<K, E, binstreenode<K, E> *>::label label; //tipo elemento
    typedef binstreenode<K, E> *node;                              //tipo nodo
    //costruttore
    pnbst();
    //^^^operatori
    //metodo che inizializza il bst
    void create();
    //metodo che restituisce vero se il bst e' vuoto
    bool empty() const;
    //metodo che inserisce un nuovo nodo di chiave k ed elemento e
    void insert(key, label);
    //metodo che modifica l'elemento di un nodo lasciando inalterata la sua chiave
    void modify(key, label);
    //metodo che cancella un nodo con chiave k dal bst
    void erase(key);
    //metodo che collega ad un nodo genitore un nodo figlio in maniera corretta (o come sinistro o come destro in base alla chiave)
    void link(node, node, key);
    //metodo che cancella un sottoalbero radicato in un nodo
    void erase_sub_tree(node);
    //metodo che restituisce un riferimento ad un nodo prendendo in input la sua chiave
    node search(key) const;
    //metodo che resituisce il nodo con chiave minima partendo da un nodo n
    node minimum(node) const;
    //metodo che resituisce il nodo con chiave minima partendo dalla radice
    node minimum() const;
    //metodo che restituisce il massimo nodo con chiave massima partendo dal sottoalbero radicato nel nodo n
    node maximum(node) const;
    //metodo che restituisce il nodo contenente chiave massima partendo dalla radice
    node maximum() const;
    // metodo che restituisce un riferimento al predecessore del nodo n
    node predecessor(node) const;
    //metodo che restituisce il successore del nodo n
    node successor(node) const;
    //metodo che alloca e innesta la radice nell'albero con chiave k ed elemento e
    void ins_root(key, label);
    //metodo che innesta e alloca la radice
    void ins_root();
    //metodo che restituisce vero se il nodo sinistro al nodo a cui si applica e' vuoto
    bool sx_empty(node) const;
    //metodo che restituisce vero se il nodo destro al nodo a cui si applica e' vuoto
    bool dx_empty(node) const;
    //metodo che restituisce un riferimento alla radice
    node get_root() const;
    //metodo che restituisce vero se il nodo a cui si applica e' una foglia
    bool leaf(node) const;
    //metodo che restituisce un label leggendo il nodo a cui si applica
    label read_label(node) const;
    //metodo che modifica il valore di un label al nodo a cui si applica
    void write_label(node, label);
    //metodo che legge la chiave di un nodo n
    key read_key(node) const;
    //metodo che restituisce un riferimento al figlio sinistro
    node get_sx(node) const;
    //metodo che restituisce un riferimento al figlio destro
    node get_dx(node) const;
    /*** algoritmo di visita ***/
    //&metodo che permette di leggere le chiavi di un BST in ordine crescente
    void inorder(node) const;
    //distruttore
    ~pnbst();

private:
    binstreenode<K, E> *root;
};

template <class K, class E>
pnbst<K, E>::pnbst()
{
    this->create();
}

template <class K, class E>
void pnbst<K, E>::create()
{
    root = nullptr;
}

template <class K, class E>
bool pnbst<K, E>::empty() const
{
    return (root == nullptr);
}

template <class K, class E>
void pnbst<K, E>::insert(key k, label l)
{
    node parent = nullptr; //puntatore al genitore
    node n = root;         //puntatore alla radice
    while ((n != nullptr) && (n->key != k))
    {
        parent = n;
        if (n != nullptr)
        {
            if (k < n->key)
            {
                n = n->sx;
            }
        }
        if (n != nullptr)
        {
            if (k > n->key)
            {
                n = n->dx;
            }
        }
    }
    //se la chiave e' uguale , modifico solo il dato  del nodo
    if ((n != nullptr) && (n->key == k))
    {
        n->label = l;
    }
    else
    {
        //alloco il nodo
        n = new binstreenode<K, E>(k, l);
        link(parent, n, k);
        if (parent == nullptr)
        {
            root = n;
        }
    }
}

template <class K, class E>
void pnbst<K, E>::modify(key k, label l)
{
    if (!this->empty())
    {
        node n = search(k);
        if (n != nullptr)
        {
            n->label = l;
        }
    }
}

template <class K, class E>
void pnbst<K, E>::ins_root(key k, label l)
{
    if (this->empty())
    {
        root = new binstreenode<K, E>(k, l);
    }
}

template <class K, class E>
void pnbst<K, E>::ins_root()
{
    if (this->empty())
    {
        root = new binstreenode<K, E>;
    }
}

template <class K, class E>
bool pnbst<K, E>::sx_empty(node n) const
{
    return (n->sx == nullptr);
}

template <class K, class E>
bool pnbst<K, E>::dx_empty(node n) const
{
    return (n->dx == nullptr);
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::get_root() const
{
    return (root);
}

template <class K, class E>
pnbst<K, E>::~pnbst()
{
    if (!this->empty())
    {
        //elimino il sotto albero radicato nella radice
        this->erase_sub_tree(root);
    }
    //elimino il nodo radice
    delete root;
    root = nullptr;
}

template <class K, class E>
void pnbst<K, E>::erase_sub_tree(node n)
{
    if (n == nullptr)
    {
        return;
    }
    erase_sub_tree(n->sx);
    erase_sub_tree(n->dx);
    if (n != root)
    {
        node p = n->parent;
        if (n == p->sx)
        {
            p->sx = nullptr;
        }
        else if (n == p->dx)
        {
            p->dx = nullptr;
        }
    }
    else
    {
        root = nullptr;
    }
    delete n;
    n = nullptr;
}

template <class K, class E>
bool pnbst<K, E>::leaf(node n) const
{
    return ((n->sx == nullptr) && (n->dx == nullptr));
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::search(key k) const
{
    node n = root;
    while ((n != nullptr) && (n->key != k))
    {
        if (n != nullptr)
        {
            if (k < n->key)
            {
                n = n->sx;
            }
        }
        if (n != nullptr)
        {
            if (k > n->key)
            {
                n = n->dx;
            }
        }
    }
    return (n); //restituisce un nodo contenente la chiave oppure un nodo nullo
}

template <class K, class E>
typename pnbst<K, E>::label pnbst<K, E>::read_label(node n) const
{
    label label;
    if (n != nullptr)
    {
        return (n->label);
    }
    return (label);
}

template <class K, class E>
typename pnbst<K, E>::key pnbst<K, E>::read_key(node n) const
{
    key key;
    if (n != nullptr)
    {
        return (n->key);
    }
    return (key);
}

template <class K, class E>
void pnbst<K, E>::write_label(node n, label l)
{
    if (n != nullptr)
    {
        n->label = l;
    }
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::get_sx(node n) const
{
    if (n != nullptr)
    {
        return (n->sx);
    }
    else
    {
        return (n);
    }
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::get_dx(node n) const
{
    if (n != nullptr)
    {
        return (n->dx);
    }
    else
    {
        return (n);
    }
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::minimum() const
{
    if (!this->empty())
    {
        return (minimum(root));
    }
    else
    {
        return (root);
    }
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::minimum(node n) const
{
    if (n->sx == nullptr)
    {
        return (n);
    }
    return (minimum(n->sx));
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::maximum() const
{
    if (!this->empty())
    {
        return (maximum(root));
    }
    else
    {
        return (root);
    }
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::maximum(node n) const
{
    if (n->dx == nullptr)
    {
        return (n);
    }
    return (maximum(n->dx));
}

template <class K, class E>
void pnbst<K, E>::erase(key k)
{
    //cerco il nodo da eliminare
    node n = search(k);
    if (n == nullptr)
    {
        //il nodo da eliminare non esiste
        return;
    }
    //caso 1 : il nodo da eliminare e' una foglia
    if (leaf(n))
    {
        if (n != root)
        {
            if (n->parent->sx == n)
            {
                n->parent->sx = nullptr;
            }
            else
            {
                n->parent->dx = nullptr;
            }
        }
        else
        {
            //il nodo da eliminare e' radice
            root = nullptr;
        }
        delete n;
        n = nullptr;
    } //caso 2: il nodo da eliminare ha due figli
    else if (!sx_empty(n) && !dx_empty(n))
    {
        //individuo il successore di n
        node s = minimum(n->dx);
        //memorizzo la chiave del successore
        key tempkey = s->key;
        //memorizzo il valore del successore
        label templabel = s->label;
        erase(s->key);
        n->key = tempkey;
        n->label = templabel;
    }
    else //caso 3: il nodo da eliminare ha un solo figlio
    {
        node child = nullptr;
        if (!sx_empty(n) && dx_empty(n))
        {
            child = n->sx;
        }
        else
        {
            child = n->dx;
        }
        if (n != root)
        {
            if (n == n->parent->sx)
            {
                n->parent->sx = child;
            }
            else
            {
                n->parent->dx = child;
            }
        }
        else
        {
            root = child;
        }
        delete n;
        n = nullptr;
    }
}

template <class K, class E>
void pnbst<K, E>::link(node parent, node child, key key)
{
    if (child != nullptr)
    {
        child->parent = parent;
    }
    //se il genitore non e' nullo
    if (parent != nullptr)
    {
        if (key < parent->key)
        {
            parent->sx = child;
        }
        if (key > parent->key)
        {
            parent->dx = child;
        }
    }
}

template <class K, class E>
void pnbst<K, E>::inorder(node n) const
{
    if (n == nullptr)
    {
        return;
    }
    inorder(n->sx);
    //esamino il nodo
    cout << " " << read_key(n) << " ";
    inorder(n->dx);
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::successor(node n) const
{
    if (n == nullptr)
    {
        return (n);
    }
    if (n->dx != nullptr)
    {
        return (minimum(n->dx));
    }
    node parent = n->parent;
    while ((parent != nullptr) && (n == parent->dx))
    {
        n = parent;
        parent = parent->parent;
    }
    return (parent);
}

template <class K, class E>
typename pnbst<K, E>::node pnbst<K, E>::predecessor(node n) const
{
    if (n == nullptr)
    {
        return (n);
    }
    if (n->sx != nullptr)
    {
        return (maximum(n->sx));
    }
    node parent = n->parent;
    while ((parent != nullptr) && (n == parent->sx))
    {
        n = parent;
        parent = parent->parent;
    }
    return (parent);
}

#endif