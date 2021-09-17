#ifndef MATGRAPH_H
#define MATGRAPH_H

#include <iostream>
#include "graph.h"
#define MAXDIMENSION 100
using namespace std;

//definisco la classe archinfo che contiene le info di un nodoarco
template <class P>
class archInfo
{
public:
    P weight;
    bool empty;
    archInfo()
    {
        empty = true;
        weight = P(NULL);
    }
};

//definisco la classe nodeinfo che contiene le info del nodo
template <class E, class P>
class nodeInfo
{
public:
    E label;
    bool empty;
    void *info;
    archInfo<P> *arches;
    nodeInfo()
    {
        label = "";
        info = 0;
        empty = true;
    }
    ~nodeInfo()
    {
        if (!empty)
        {
            delete[] arches;
            arches = nullptr;
        }
    }
};

//definisco la classe nodografo contenente l'id del grafo nella matrice di adiacenza
class nodeGraph
{
public:
    nodeGraph(int id) //costruttore con parametro id
    {
        idnode = id;
    }
    nodeGraph() //costruttore di default
    {
        idnode = 0;
    }
    int getId() //restituisce l'id del nodo
    {
        return (idnode);
    }
    void setId(int id)
    {
        idnode = id;
    }
    nodeGraph &operator=(const nodeGraph &n)
    {
        idnode = n.idnode;
        return *(this);
    }
    bool operator==(const nodeGraph &n)
    {
        return (idnode == n.idnode);
    }

private:
    int idnode;
};

//definisco la classe matricegrafo con tipo parametrico etichetta(int,string,double,char..) e peso(int,double,float)
template <class E, class P>
class matgraph : public graph<E, P, nodeGraph>
{
public:
    //definisco un alias per i tipi template
    typedef E label;        //tipovalore o etichetta
    typedef P weight;       //tipo peso
    typedef nodeGraph node; //tipo nodo grafo
    //ridefiisco i tipi della classe astratta
    typedef class arch<weight, node> arch;                                            //tipo nodoarco
    typedef typename graph<label, weight, node>::listnode listnode;                   //tipo listanodi
    typedef typename graph<label, weight, node>::position_listnode position_listnode; //tipo posizione listanodi
    //costruttore con paramentro
    matgraph(int);
    //costruttore di default
    matgraph();
    //distruttore
    ~matgraph();
    //metodo che inizializza il grafo
    void create();
    //metodo che restituisce vero se il grafo e' vuoto
    bool empty() const;
    //metodo che inserisce un nodo nel grafo
    void insNode(node &);
    //metodo che inserisce un arco avendo in input il nodo uscente e il nodo entrante e il peso
    void insArch(node, node, weight);
    //metodo che elimina un nodo dalla matrice di adiacenza
    void eraseNode(node);
    //metodo che elimina un arco entrante da un nodo della matrice di adiacenza
    void eraseArch(node, node);
    //metodo che restituisce vero se il nodo passato in input e' un nodo del grafo
    bool isNode(node) const;
    //metodo che restituisce vero se dati due nodi in input essi formano un arco nel grafo
    bool isArch(node, node) const;
    //metodo che restituisce una lista dei nodi adiacenti al nodo a cui si applica
    listnode adjacent(node) const;
    //metodo che restituisce una lista con tutti i nodi del grafo
    listnode listNode() const;
    //metodo che legge e restituisce l'etichetta di un nodo
    label readLabel(node) const;
    //metodo che scrive e sovrascrive l'etichetta di un nodo con un altra etichetta
    void writeLabel(node, label);
    //metodo che legge e restituisce il peso di due nodi se questi formano un arco
    weight readWeight(node, node) const;
    //metodo che scrive e sovrascrive il peso di due nodi che formano un arco con un altro peso
    void writeWeight(node, node, weight);
    //metodo che restituisce il totale dei nodi presenti nel grafo
    int numNodes() const;
    //metodo che restituisce il totale degli archi presenti nel grafo
    int numArches() const;
    //^^^funzioni di servizio^^^
    //metodo che restituisce vero se la matrice di adiacenza e' nulla
    bool isEmptyMatrix() const;
    //metodo che stampa i nodi adiacenti al nodo a cui si applica
    void printAdjacent(node) const;
    //stampa tutti i nodi con gli archi associati
    void print(node) const;
    //metodo che permette di visualizzare le relazioni tra i nodi e i loro archi nella matrice di adiacenza
    void adjacencyMatrix() const;
    /** algoritmi di visita **/
    //algoritmo dfs visita in profondita'
    void dfs(node) const;
    void dfs(node, int *) const;
    //algoritmo bfs visita in ampiezza
    void bfs(node) const;
    //^^^funzioni  utili
    //funzione che restituisce il numero di archi entranti al nodo a cui si applica
    int inDegree(node) const;
    //funzione che restituisce il numero di archi uscenti al nodo a cui si applica
    int outDegree(node) const;
    //metodo che  restituisce la media del numero di archi uscenti per ogni nodo del grafo
    double meanOutDegree() const;
    //&metodo che stampa un percorso tra due nodi del grafo se tale cammino esiste
    void dfsPath(node, node) const;
    //~funzione di supporto che stampa l'intero cammino tra due nodi del grafo avente in input il vettore di marcatura
    void dfsPath(node, node, int *, bool &) const;
    //&metodo che verifica l'esistenza tra due nodi del grafo ed in caso positivo stampa tutto il cammino richiamando dfsPath()
    void findPath(node, node) const;
    //~funzione di supporto che restituisce vero se esiste un cammino tra due nodi del grafo avente in input il vettore di visite[]
    bool findPath(node, node, int *, bool) const;

private:
    nodeInfo<E, P> *matrix; //matrice di info nodi
    int dimension;          //dimensione massima o massima capienza della matrice
    int nodes;              //numero nodi presenti
    int arches;             //numero archi presenti
};

template <class E, class P>
matgraph<E, P>::matgraph()
{
    this->create();
    arches = 0;
    dimension = MAXDIMENSION;
    matrix = new nodeInfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches = new archInfo<P>[dimension];
    }
}

template <class E, class P>
matgraph<E, P>::matgraph(int dim)
{
    this->create();
    arches = 0;
    dimension = dim;
    matrix = new nodeInfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches = new archInfo<P>[dimension];
    }
}

template <class E, class P>
bool matgraph<E, P>::isEmptyMatrix() const
{
    return (matrix == nullptr);
}

template <class E, class P>
matgraph<E, P>::~matgraph()
{
    if (!isEmptyMatrix())
    {
        for (int i = 0; i < dimension; i++)
        {
            delete[] matrix[i].arches;
            matrix[i].arches = nullptr;
        }
    }
    delete[] matrix;
    matrix = nullptr;
}

template <class E, class P>
void matgraph<E, P>::create()
{
    nodes = 0;
}

template <class E, class P>
bool matgraph<E, P>::empty() const
{
    return (nodes == 0);
}

template <class E, class P>
void matgraph<E, P>::insNode(node &nodegraph)
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
    nodegraph.setId(n);
}

template <class E, class P>
void matgraph<E, P>::insArch(node n1, node n2, weight w)
{
    matrix[n1.getId()].arches[n2.getId()].weight = w;
    matrix[n1.getId()].arches[n2.getId()].empty = false;
    arches++;
}

template <class E, class P>
void matgraph<E, P>::eraseNode(node n)
{
    /*
    !!!!!!!!!!!!!!
     * nell'eliminazione di un nodo suppongo che non ci siano
     * nodi entranti ne nodi uscenti
    !!!!!!!!!!!!!!
    */
    bool canc = true;
    int i = 0;
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[n.getId()].arches[i].empty)
        {
            canc = false;
        }
    }
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[i].empty && !(matrix[i].arches[n.getId()].empty))
        {
            canc = false;
        }
    }
    if (canc)
    {
        delete[] matrix[n.getId()].arches;
        matrix[n.getId()].arches = nullptr;
        matrix[n.getId()].empty = true;
        arches--;
    }
}

template <class E, class P>
void matgraph<E, P>::eraseArch(node n1, node n2)
{
    matrix[n1.getId()].arches[n2.getId()].empty = true; //arco vuoto
    matrix[n1.getId()].arches[n2.getId()].weight = 0;   //imposto il peso ad un valore nullo
    arches--;
}

template <class E, class P>
typename matgraph<E, P>::listnode matgraph<E, P>::adjacent(node n) const
{
    listnode list;
    for (int j = 0; j < dimension; j++)
    {
        if (!matrix[n.getId()].arches[j].empty)
        {
            node copy(j); //copio il nodo arco
            //inserisco il nodo arco adiacente ad n nella lista
            list.push_back(copy);
        }
    }
    return (list);
}

template <class E, class P>
typename matgraph<E, P>::listnode matgraph<E, P>::listNode() const
{
    listnode list;
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            node nodecopy(i);
            list.push_back(nodecopy);
        }
    }
    return (list);
}

template <class E, class P>
typename matgraph<E, P>::label matgraph<E, P>::readLabel(node n) const
{
    return (matrix[n.getId()].label);
}

template <class E, class P>
void matgraph<E, P>::writeLabel(node n, label l)
{
    matrix[n.getId()].label = l;
}

template <class E, class P>
typename matgraph<E, P>::weight matgraph<E, P>::readWeight(node n1, node n2) const
{
    return (matrix[n1.getId()].arches[n2.getId()].weight);
}

template <class E, class P>
void matgraph<E, P>::writeWeight(node n1, node n2, weight w)
{
    matrix[n1.getId()].arches[n2.getId()].weight = w;
}

template <class E, class P>
bool matgraph<E, P>::isNode(node n) const
{
    return (!matrix[n.getId()].empty);
}

template <class E, class P>
bool matgraph<E, P>::isArch(node n1, node n2) const
{
    return (!matrix[n1.getId()].arches[n2.getId()].empty);
}

template <class E, class P>
int matgraph<E, P>::numNodes() const
{
    return (nodes);
}

template <class E, class P>
int matgraph<E, P>::numArches() const
{
    return (arches);
}

template <class E, class P>
void matgraph<E, P>::printAdjacent(node n) const
{
    cout << "\nnodes adjacent: (" << readLabel(n) << "):\n";
    if (!empty())
    {
        listnode l = adjacent(n);
        position_listnode p = l.begin();
        while (!l.end(p))
        {
            cout << "\t\t    -->(" << readLabel(l.read(p)) << ")\n";
            p = l.next(p);
        }
    }
}

template <class E, class P>
void matgraph<E, P>::print(node u) const
{
    if (isNode(u))
    {
        for (int i = u.getId(); i < dimension; i++)
        {
            if (matrix[i].empty == false)
            {
                node node_n(i);
                cout << "\nnodo: " << readLabel(node_n) << "\n";
                for (int j = 0; j < dimension; j++)
                {
                    if (matrix[i].arches[j].empty == false)
                    {
                        node node_a(j);
                        cout << "\tarco: " << readLabel(node_a);
                    }
                }
            }
        }
    }
}

template <class E, class P>
void matgraph<E, P>::adjacencyMatrix() const
{
    int adjacency_matrix[dimension][dimension]; //dichiaro la matrice di adiacenza
    //inizializzo la matrice
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            adjacency_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < dimension; i++)
    {
        for (int j = i; j < dimension; j++)
        {
            if (matrix[i].arches[j].empty == false)
            {
                adjacency_matrix[i][j] = 1;
            }
            if (matrix[j].arches[i].empty == false)
            {
                adjacency_matrix[j][i] = 1;
            }
        }
    }
    cout << "\n :::::::: matrice di adiacenza :::::::: \n";
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << "\t" << adjacency_matrix[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

template <class E, class P>
void matgraph<E, P>::dfs(node u) const
{
    if (isNode(u))
    {
        int vettore[dimension];
        //inizializzo il vettore di marcatura
        for (int i = 0; i < dimension; i++)
        {
            vettore[i] = 0;
        }
        //marco le posizioni occupate dalla matrice
        for (int i = 0; i < dimension; i++)
        {
            if (matrix[i].empty == false)
            {
                vettore[i] = 1; //nodo occupato
            }
        }
        dfs(u, vettore);
    }
}

template <class E, class P>
void matgraph<E, P>::dfs(node u, int *visitato) const
{
    //esamino il nodo u
    cout << " (" << matrix[u.getId()].label << ") --> ";
    visitato[u.getId()] = 2; //nodo visitato
    listnode l = adjacent(u);
    if (!l.empty())
    {
        position_listnode p = l.begin();
        while (!l.end(p))
        {
            node n = l.read(p);
            if (visitato[n.getId()] == 1)
            {
                dfs(n, visitato);
            }
            p = l.next(p);
        }
    }
}

template <class E, class P>
int matgraph<E, P>::inDegree(node n) const
{
    int numarchi = 0;
    //scorro la lista dei nodi
    for (int i = 0; i < dimension; i++)
    {
        //verifico se l'i-esimo nodo fa un arco con n, in caso positivo aumento il contatore
        if (!matrix[i].arches[n.getId()].empty)
        {
            numarchi++;
        }
    }
    return (numarchi);
}

template <class E, class P>
int matgraph<E, P>::outDegree(node n) const
{
    int numarchi = 0;

    for (int j = 0; j < dimension; j++)
    {
        if (!matrix[n.getId()].arches[j].empty)
        {
            numarchi++;
        }
    }

    return (numarchi);
}

template <class E, class P>
double matgraph<E, P>::meanOutDegree() const
{
    double media = 0;
    if (!this->empty())
    {
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                node nodegraph(i);
                media = media + outDegree(nodegraph);
            }
        }
        media = media / this->numNodes();
    }
    return (media);
}

template <class E, class P>
void matgraph<E, P>::findPath(node s, node d) const
{
    bool flag;
    //eseguo una verifica col vettore di marcatura
    int visitato[dimension];
    for (int i = 0; i < dimension; i++)
    {
        if (matrix[i].empty == false)
        {
            visitato[i] = 0; //nodo occupato
        }
        else
        {
            visitato[i] = -1; //nodo vuoto
        }
    }
    //restituisce vero se esiste un cammino da s in d
    flag = findPath(s, d, visitato, false);

    //se tale cammino esiste lo stampo
    if (flag)
    {
        cout << "\ncammino che congiunge il nodo (" << readLabel(s) << ") al nodo (" << readLabel(d) << ") : ";
        dfsPath(s, d);
    }
    else
    {
        cout << "\ncammino non esistente tra il nodo(" << readLabel(s) << ") e il nodo(" << readLabel(d) << ")";
    }
}

template <class E, class P>
bool matgraph<E, P>::findPath(node s, node d, int *visitato, bool found) const
{
    //esame con marcatura del nodo s
    visitato[s.getId()] = 1; //marco il nodo s come visitato
    listnode lista_adiacenti = this->adjacent(s);
    if (!lista_adiacenti.empty())
    {
        auto pos = lista_adiacenti.begin();
        while (!lista_adiacenti.end(pos) && !found)
        {
            node n = lista_adiacenti.read(pos);
            if (n == d)
            {
                found = true;
            }
            if (visitato[n.getId()] == 0)
            {
                found = findPath(n, d, visitato, found);
            }
            pos = lista_adiacenti.next(pos);
        }
    }
    return (found);
}

template <class E, class P>
void matgraph<E, P>::dfsPath(node s, node d) const
{
    int v[dimension];
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            v[i] = 0; //nodo presente
        }
        else
        {
            v[i] = -1; //nodo assente
        }
    }
    if (findPath(s, d, v, false))
    {
        //creo il vettore di marcatura
        bool found = false;
        int visitato[dimension];
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                visitato[i] = 0; //nodo presente
            }
            else
            {
                visitato[i] = -1; //nodo assente
            }
        }
        dfsPath(s, d, visitato, found);
    }
}

template <class E, class P>
void matgraph<E, P>::dfsPath(node s, node d, int *visitato, bool &found) const
{
    //esamino il nodo u
    cout << " (" << readLabel(s) << ") --> ";
    visitato[s.getId()] = 1; //nodo visitato
    listnode l = adjacent(s);
    if (!l.empty())
    {
        position_listnode p = l.begin();
        while (!l.end(p) && !found)
        {
            node n = l.read(p);
            if (n == d)
            {
                cout << "(" << readLabel(n) << ")";
                found = true;
            }
            else if (visitato[n.getId()] == 0)
            {
                dfsPath(n, d, visitato, found);
            }
            p = l.next(p);
        }
    }
}

template <class E, class P>
void matgraph<E, P>::bfs(node n) const
{
    //creo il vettore di marcatura
    bool visited[dimension];
    for (int i = 0; i < dimension; i++)
    {
        visited[i] = false;
    }
    //creo la coda per il bfs
    pnqueque<node> queque;
    visited[n.getId()] = true;
    queque.enqueque(n.getId());
    while (!queque.empty())
    {
        node i = queque.top();
        cout << " (" << readLabel(i) << ") --> ";
        queque.dequeque();
        listnode l = adjacent(i);
        if (!l.empty())
        {
            for (auto p = l.begin(); !l.end(p); p = l.next(p))
            {
                if (visited[l.read(p).getId()] == false)
                {
                    visited[l.read(p).getId()] = true;
                    queque.enqueque(l.read(p));
                }
            }
        }
    }
}

#endif