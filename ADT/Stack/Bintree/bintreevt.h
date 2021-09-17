#ifndef BINTREEVT_H
#define BINTREEVT_H

#include <iostream>
#include <string>
#include "bintree.h"
using namespace std;

template <class I>
class bintreevt : public bintree<I, int>
{
    static const int NIL = -1;

public:
    typedef typename bintree<I, int>::item item;
    typedef typename bintree<I, int>::node node;
    struct cell
    {
        node parent;
        node left;
        node right;
        item value;
        int depth = 0;
    };
    typedef struct cell cell;
    //costruttore di default
    bintreevt();
    //costruttore per parametro
    bintreevt(int);
    //distruttore
    ~bintreevt();
    //&operatori
    //metodo che inizializza l'albero binario
    void create();
    //metodo che restituisce vero se l'albero binario e' vuoto
    bool empty() const;
    //metodo che restituisce la radice
    node get_root() const;
    //metodo che restituisce il riferimento del genitore
    node parent(node) const;
    //metodo che restituisce il riferimento del figlio sinistro
    node sx(node) const;
    //metodo che restituisce il riferimento del figlio destro
    node dx(node) const;
    //metodo che restituisce vero se il sinistro e' vuoto
    bool sx_empty(node) const;
    //metodo che restituisce vero se il destro e' vuoto
    bool dx_empty(node) const;
    //metodo che rimuove un sottoalbero
    void erase(node);
    //metodo che legge e restituisce l'item di un nodo
    item read(node) const;
    //metodo che scrive e sovrascrive l'item di un nodo
    void write(node, item);
    //metodo che alloca e innesta la radice nell'albero binario
    void ins_root();
    //metodo che inserisce e alloca un figlio sinistro al nodo a cui si applica
    void ins_sx(node);
    //metodo che inserisce e alloca un figlio sinistro al nodo a cui si applica con un item
    void ins_sx(node, item);
    //metodo che inserisce e alloca un figlio destro al nodo a cui si applica
    void ins_dx(node);
    //metodo che inserisce e alloca un figlio destro al nodo a cui si applica con un item
    void ins_dx(node, item);
    //&algoritmi di visita
    //&^visite in dfs (depth first search)
    //preordine
    void preorder(node) const;
    //postordine
    void postorder(node) const;
    //simmetrica
    void inorder(node) const;
    //metodo che restituisce vero se il nodo e' foglia
    bool leaf(node) const;
    //metodo che restituisce vero se il nodo e' vuoto
    bool is_empty_node(node) const;
    //metodo che restituisce la profondita' del nodo a cui si applica
    int depth(node) const;
    //metodo che restituisce l'altezza dell'albero
    int depth() const;

private:
    int MAXLUNG;  //massima capienza
    cell *spazio; //vettore di nodi
    int nNodi;    //totale nodi presenti
    node inizio;  //posizione della radice
    node libera;  //nodo libero
};

template <class I>
bintreevt<I>::bintreevt()
{
    MAXLUNG = 100;
    spazio = new cell[MAXLUNG];
    this->create();
}

template <class I>
bintreevt<I>::bintreevt(int N) : MAXLUNG(N)
{
    spazio = new cell[nNodi];
    this->create();
}

template <class I>
bintreevt<I>::~bintreevt()
{
    erase(inizio);
    delete[] spazio;
    spazio = nullptr;
}

template <class I>
void bintreevt<I>::create()
{
    inizio = NIL;
    for (int i = 0; i < MAXLUNG; i++)
    {
        spazio[i].left = (i + 1) % MAXLUNG;
    }
    libera = 0;
    nNodi = 0;
}

template <class I>
bool bintreevt<I>::empty() const
{
    return (nNodi == 0);
}

template <class I>
typename bintreevt<I>::node bintreevt<I>::get_root() const
{
    return (inizio);
}

template <class I>
typename bintreevt<I>::node bintreevt<I>::parent(node n) const
{
    if (n != inizio)
    {
        return (spazio[n].parent);
    }
    else
    {
        return (n);
    }
}

template <class I>
typename bintreevt<I>::node bintreevt<I>::sx(node n) const
{
    return (spazio[n].left);
}

template <class I>
typename bintreevt<I>::node bintreevt<I>::dx(node n) const
{
    return (spazio[n].right);
}

template <class I>
bool bintreevt<I>::sx_empty(node n) const
{
    return (spazio[n].left == NIL);
}

template <class I>
bool bintreevt<I>::dx_empty(node n) const
{
    return (spazio[n].right == NIL);
}

template <class I>
void bintreevt<I>::ins_root()
{
    if (inizio == NIL)
    {
        inizio = libera;
        libera = spazio[libera].left;
        spazio[inizio].left = NIL;
        spazio[inizio].right = NIL;
        nNodi++;
    }
}

template <class I>
void bintreevt<I>::ins_sx(node n)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].left != NIL)
    {
        cout << "\nsinistro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].left = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    nNodi++;
}

template <class I>
void bintreevt<I>::ins_sx(node n, item v)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].left != NIL)
    {
        cout << "\nsinistro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].left = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    spazio[q].value = v;
    nNodi++;
}

template <class I>
void bintreevt<I>::ins_dx(node n)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].right != NIL)
    {
        cout << "\ndestro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].right = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    nNodi++;
}

template <class I>
void bintreevt<I>::ins_dx(node n, item v)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].right != NIL)
    {
        cout << "\ndestro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].right = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    spazio[q].value = v;
    nNodi++;
}

template <class I>
void bintreevt<I>::erase(node n)
{
    if (n != NIL)
    {
        if (!sx_empty(n))
        {
            erase(spazio[n].left);
        }
        if (!dx_empty(n))
        {
            erase(spazio[n].right);
        }
        if (n != inizio)
        {
            node p = parent(n);
            if (spazio[p].left == n)
            {
                spazio[p].left = NIL;
            }
            else
            {
                spazio[p].right = NIL;
            }
        }
        else
        {
            inizio = NIL;
        }
        nNodi--;
        spazio[n].left = libera;
        libera = n;
    }
}

template <class I>
typename bintreevt<I>::item bintreevt<I>::read(node n) const
{
    item value;
    if (n != NIL)
    {
        return (spazio[n].value);
    }
    return (value);
}

template <class I>
void bintreevt<I>::write(node n, item v)
{
    if (n != NIL)
    {
        spazio[n].value = v;
    }
    else
    {
        cout << "\nnodo nullo\n";
    }
}

template <class I>
void bintreevt<I>::preorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    cout << " " << read(n) << " ";
    preorder(spazio[n].left);
    preorder(spazio[n].right);
}

template <class I>
void bintreevt<I>::postorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    postorder(spazio[n].left);
    postorder(spazio[n].right);
    cout << " " << read(n) << " ";
}

template <class I>
void bintreevt<I>::inorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    inorder(spazio[n].left);
    cout << " " << read(n) << " ";
    inorder(spazio[n].right);
}

template <class I>
bool bintreevt<I>::leaf(node n) const
{
    return (sx_empty(n) && dx_empty(n));
}

template <class I>
bool bintreevt<I>::is_empty_node(node n) const
{
    return (n == NIL);
}

template <class I>
int bintreevt<I>::depth(node sub_root) const
{
    if (sub_root == NIL)
    {
        return (-1); //nodo nullo
    }
    int left_depth = depth(spazio[sub_root].left);
    int right_depth = depth(spazio[sub_root].right);
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
int bintreevt<I>::depth() const
{
    int d = 0;
    if (!empty())
    {
        d = depth(get_root());
    }
    else
    {
        d = -1;
    }
    return (d);
}

#endif