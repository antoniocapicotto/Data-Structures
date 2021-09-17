#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <iostream>
#include <string>
#include "graph.h"
#define MAXDIMENSION 100
using namespace std;

//classe nodografo
class nodeg
{
public:
    nodeg(int i)
    {
        idnode = i;
    }
    nodeg()
    {
        idnode = 0;
    }
    int getid()
    {
        return (idnode);
    }
    void setid(int id)
    {
        idnode = id;
    }
    nodeg &operator=(const nodeg &n)
    {
        idnode = n.idnode;
        return *(this);
    }
    bool operator==(const nodeg &n)
    {
        return (idnode == n.idnode);
    }

private:
    int idnode;
};

//classe infoarco
template <class P>
class archinfo
{
public:
    P weight;
    nodeg _to;
    archinfo<P> &operator=(const archinfo<P> &archinfo)
    {
        weight = archinfo.weight;
        _to = archinfo._to;
    }
};

//classe infonodo
template <class E, class P>
class nodeinfo
{
public:
    E label;
    bool empty;
    void *info;
    linkedlist<archinfo<P>> arches;
    nodeinfo()
    {
        label = "";
        info = 0;
        empty = true;
    }
};

template <class E, class P>
class listgraph : public graph<E, P, nodeg>
{
public:
    //^^^tipi
    typedef E label;                                             //tipo etichetta
    typedef P weight;                                            //tipo peso
    typedef nodeg node;                                          //tipo nodo
    typedef class arch<weight, node> arch;                       //tipo arco
    typedef class graph<label, weight, node> graph;              //ticpo grafo con etichetta peso e nodo
    typedef typename graph::listnode listnode;                   //tipo listanodi
    typedef typename graph::position_listnode position_listnode; //tipo posizione listanodi
    //costruttore di default
    listgraph();
    //costruttore con parametro
    listgraph(int);
    //distruttore
    ~listgraph();
    //^^^operatori
    //metodo che inizializza il grafo
    void create();
    //metodo che restituisce vero se il grafo e' vuoto
    bool empty() const;
    //metodo che inserisce un nodo all'interno del grafolista
    void insNode(node &);
    //metodo che inserisce un arco nel grafolista
    void insArch(node, node, weight);
    //metodo che cancella un nodo dal grafolista se non vi sono ne nodi entranti ne nodi uscenti
    void eraseNode(node);
    //metodo che cancella un arco dal grafo
    void eraseArch(node, node);
    //metodo che restituisce vero se il nodo preso in input appartiene al grafo
    bool isNode(node) const;
    //metodo che restituisce vero se la coppia di nodi presi in input formano un arco nela grafo
    bool isArch(node, node) const;
    //metodo che restituisce la lista dei nodi adiacenti al nodo al quale si applica
    listnode adjacent(node) const;
    //metodo che restituisce la lista dei nodi che appartengono al grafo
    listnode listNode() const;
    //metodo che legge e restituisce l'etichetta di un nodo del grafo
    label readLabel(node) const;
    //metodo che scrive e sovrascrive l'etichetta di un nodo del grafo
    void writeLabel(node, label);
    //metodo che legge e restituisce il peso di un arco del grafo
    weight readWeight(node, node) const;
    //metodo che scrive e sovrascrive il peso di un arco del grafo
    void writeWeight(node, node, weight);
    //metodo che restituisce il numero totale dei nodi inseriti nel grafo
    int numNodes() const;
    //metodo che restituisce il totale degli archi nel grafo
    int numArches() const;
    //~funzioni di servizio
    //metodo che restiuisce vero se la matrice di adiacenza e' una matrice vuota
    bool isEmptyMatrix() const;
    void dfs(node) const;
    void dfs(node, int *) const;

private:
    nodeinfo<E, P> *matrix;
    int dimension;
    int nodes;
    int arches;
};

template <class E, class P>
listgraph<E, P>::listgraph()
{
    this->create();
    dimension = MAXDIMENSION;
    arches = 0;
    matrix = new nodeinfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches.create();
    }
}

template <class E, class P>
listgraph<E, P>::listgraph(int dim)
{
    this->create();
    dimension = dim;
    arches = 0;
    matrix = new nodeinfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches.create();
    }
}

template <class E, class P>
void listgraph<E, P>::create()
{
    nodes = 0;
}

template <class E, class P>
bool listgraph<E, P>::empty() const
{
    return (nodes == 0);
}

template <class E, class P>
bool listgraph<E, P>::isEmptyMatrix() const
{
    return (matrix == nullptr);
}

template <class E, class P>
listgraph<E, P>::~listgraph()
{
    if (!isEmptyMatrix())
    {
        for (int i = 0; i < dimension; i++)
        {
            matrix[i].arches.~linkedlist();
        }
    }
    delete[] matrix;
    matrix = nullptr;
}

template <class E, class P>
void listgraph<E, P>::insNode(node &nodegraph)
{
    int n = 0;
    if (nodes < dimension)
    {
        while (!matrix[n].empty)
        {
            n++;
        }
        nodes++;
        matrix[n].empty = false;
    }
    nodegraph.setid(n);
}

template <class E, class P>
bool listgraph<E, P>::isNode(node n) const
{
    return (!matrix[n.getid()].empty);
}

template <class E, class P>
void listgraph<E, P>::eraseNode(node n)
{
    /*
    !!!!!!!!!!!!!!
     * nell'eliminazione di un nodo suppongo che non ci siano
     * nodi entranti ne nodi uscenti
    !!!!!!!!!!!!!!
    */
    bool canc = true;
    //controllo sugli archi uscenti
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[n.getid()].arches.empty())
        {
            canc = false;
        }
    }
    //controllo sugli archi entranti
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[i].empty)
        {
            for (auto p = matrix[i].arches.begin(); !matrix[i].arches.end(p); p = matrix[i].arches.next(p))
            {
                if (matrix[i].arches.read(p)._to.getid() == n.getid())
                {
                    canc = false;
                }
            }
        }
    }
    //se canc e' vero elimino il nodo
    if (canc)
    {
        //per sicurezza elimino eventuali archi uscenti
        while (!matrix[n.getid()].arches.empty())
        {
            matrix[n.getid()].arches.pop_front();
        }
        //imposto il nodo come vuoto
        matrix[n.getid()].empty = true;
        //decremento il totale nodi
        nodes--;
    }
}

template <class E, class P>
void listgraph<E, P>::insArch(node n1, node n2, weight w)
{
    //creo il nodo arco da inserire
    archinfo<P> infoarco;
    infoarco.weight = w;
    infoarco._to = n2;
    matrix[n1.getid()].arches.push_back(infoarco);
    arches++;
}

template <class E, class P>
bool listgraph<E, P>::isArch(node n1, node n2) const
{
    bool found = false;
    if (!matrix[n1.getid()].arches.empty())
    {
        typename linkedlist<archinfo<P>>::position p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !(found))
        {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
            {
                found = true;
            }
            p = matrix[n1.getid()].arches.next(p);
        }
    }
    return (found);
}

template <class E, class P>
void listgraph<E, P>::eraseArch(node n1, node n2)
{
    typename linkedlist<archinfo<P>>::position p;
    p = matrix[n1.getid()].arches.begin();
    bool found = false;
    while (!matrix[n1.getid()].arches.end(p) && !(found))
    {
        if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
        {
            found = true;
        }
        else
        {
            p = matrix[n1.getid()].arches.next(p);
        }
    }
    if (found)
    {
        matrix[n1.getid()].arches.erase(p);
        arches--;
    }
}

template <class E, class P>
typename listgraph<E, P>::listnode listgraph<E, P>::adjacent(node n) const
{
    listnode list;
    if (isNode(n))
    {
        if (!matrix[n.getid()].arches.empty())
        {
            //scansiono la lista archi
            for (auto i = matrix[n.getid()].arches.begin(); !matrix[n.getid()].arches.end(i); i = matrix[n.getid()].arches.next(i))
            {
                //inserisco il p-esimo arco nella lista dei nodi adiacenti l
                node copy(matrix[n.getid()].arches.read(i)._to.getid());
                list.push_back(copy);
            }
        }
    }
    return (list);
}

template <class E, class P>
typename listgraph<E, P>::listnode listgraph<E, P>::listNode() const
{
    listnode list;
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            node copy(i);
            list.push_back(copy);
        }
    }
    return (list);
}

template <class E, class P>
E listgraph<E, P>::readLabel(node n) const
{
    return (matrix[n.getid()].label);
}

template <class E, class P>
void listgraph<E, P>::writeLabel(node n, E label)
{
    matrix[n.getid()].label = label;
}

template <class E, class P>
typename listgraph<E, P>::weight listgraph<E, P>::readWeight(node n1, node n2) const
{
    P weight = -1;
    if (isArch(n1, n2))
    {
        bool found = false;
        auto p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !found)
        {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
            {
                found = true;
            }
            else
            {
                p = matrix[n1.getid()].arches.next(p);
            }
        }
        if (found)
        {
            return (matrix[n1.getid()].arches.read(p).weight);
        }
    }
    return (weight);
}

template <class E, class P>
void listgraph<E, P>::writeWeight(node n1, node n2, P weight)
{
    if (isArch(n1, n2))
    {
        bool found = false;
        auto p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !found)
        {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
            {
                found = true;
            }
            else
            {
                p = matrix[n1.getid()].arches.next(p);
            }
        }
        if (found)
        {
            archinfo<P> infoarco;
            infoarco.weight = weight;
            infoarco._to = n2;
            matrix[n1.getid()].arches.write(infoarco, p);
        }
    }
}

template <class E, class P>
int listgraph<E, P>::numNodes() const
{
    return (nodes);
}

template <class E, class P>
int listgraph<E, P>::numArches() const
{
    return (arches);
}

template <class E, class P>
void listgraph<E, P>::dfs(node n) const
{
    if (isNode(n))
    {
        int visitato[dimension];
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                visitato[i] = 0; //nodo occupato
            }
            else
            {
                visitato[i] = -1; //nodo nullo
            }
        }
        dfs(n, visitato);
    }
}

template <class E, class P>
void listgraph<E, P>::dfs(node n, int *visitato) const
{
    //esamino il nodo
    cout << " node(" << readLabel(n) << ") --> ";
    //marco il nodo come visitato
    visitato[n.getid()] = 1;
    listnode l = this->adjacent(n);
    if (!l.empty())
    {
        for (auto p = l.begin(); !l.end(p); p = l.next(p))
        {
            node i(l.read(p).getid());
            if (visitato[i.getid()] == 0)
            {
                dfs(i, visitato);
            }
        }
    }
}

#endif