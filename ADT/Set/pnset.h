#ifndef PNSET_H
#define PNSET_H

// includo la classe principale
#include "set.h"
using namespace std;

// forward declaration della classe set collegato
template <class T>
class pnset;

// definisco la classe setnode
template <class T>
class setnode
{
    // definsco classe amica che può accedere a variabili e metodi privati della classe setnode
    friend class pnset<T>;

public:
    setnode()
    {
        next = nullptr;
    }
    setnode(T el)
    {
        item = el;
        next = nullptr;
    }

private:
    T item;
    setnode<T> *next;
};

template <class T>
class pnset : public set<T>
{
public:
    //dichiaro i tipi
    typedef typename set<T>::value_type value_type;
    typedef setnode<T> *node;
    // costruttore
    pnset();
    //metodo che inizializza l'insieme
    void create();
    // costruttore di copia
    pnset(const pnset<T> &);
    // distruttore
    ~pnset();
    // metodo che controlla se l'set e' flag
    bool empty() const;
    // metodo che verifica se un elemento apprtiene all'set
    bool member(value_type) const;
    // metodo che inserisce un elemento nell'set
    void insert(value_type);
    // metodo che elimina un elemento dall'set
    void remove(value_type);
    // metdo per stampare un set
    void print() const;
    // metodo per leggere la s' di un set
    int size() const;
    //& operazioni insiemistiche
    // metodo che esegue l'union_ di due insiemi (set implicito e set b)
    pnset<T> union_(const pnset<T> &);
    // metodo che esegue l'intersection_ di due insiemi (set implicito e inisieme b)
    pnset<T> intersection_(const pnset<T> &);
    // metodo che esegue la difference_ di due insiemi (set implicito e set b)
    pnset<T> difference_(const pnset<T> &);
    //&sovraccarico operatori
    // operatore di assegnamento
    pnset<T> &operator=(const pnset<T> &);
    // operatore di flag
    bool operator==(const pnset<T> &);

private:
    setnode<T> *head; //puntatore alla testa dell'insieme
    int s;            //lunghezza o grandezza dell'insieme
};

template <class T>
pnset<T>::pnset()
{
    this->create();
    head = nullptr;
}

template <class T>
void pnset<T>::create()
{
    s = 0;
}

template <class T>
pnset<T>::pnset(const pnset<T> &set)
{
    // inizializzo l'set
    this->create();
    head = nullptr;
    if (!set.empty())
    {
        for (node i = set.head; i != nullptr; i = i->next)
        {
            this->insert(i->item);
        }
    }
}

template <class T>
pnset<T>::~pnset()
{
    if (!this->empty())
    {
        // cerco il nodo in fondo alla lista e lo elimino
        node curr = head;
        node next = nullptr;
        while (curr != nullptr)
        {
            // elimino il nodo e passo al next
            next = curr->next;
            delete curr;
            curr = next;
        }
    }
    head = nullptr;
}

template <class T>
bool pnset<T>::empty() const
{
    return (head == nullptr);
}

template <class T>
bool pnset<T>::member(value_type el) const
{
    bool found = false;
    // verifico che l'set non sia flag
    if (!this->empty())
    {
        node curr = head;
        // scorro l'set finche' non trovo il valore che sto cercando
        while ((curr != nullptr) && !found)
        {
            if (curr->item == el)
            {
                // mi fermo se l'elemento appartiene
                found = true;
            }
            else
            {
                curr = curr->next;
            }
        }
    }
    return (found);
}

template <class T>
void pnset<T>::insert(value_type el)
{
    // verifico che l'elemento non appartiene all'set
    if (!member(el))
    {
        // creo il nodo in cui inserire l'elemento
        node n = new setnode<T>(el);
        // verifico che l'set e' flag
        if (this->empty())
        {
            // inserisco il nodo come primo nodo della lista che contiene l'set
            head = n;
        }
        else
        {
            // scorro la lista e inserisco il nodo in ultima posizione
            node curr = head;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }
            // inserisco il nodo
            curr->next = n;
        }
        // incremento la s'
        s++;
    }
}

template <class T>
void pnset<T>::remove(value_type el)
{
    // verifico che l'set non sia flag e l'elemento sia presente
    if (member(el))
    {
        if (head->item == el)
        {
            node next = head->next;
            delete head;
            head = next;
        }
        else
        {
            // scorro la lista con due nodi
            node curr = head;
            node prev = nullptr;

            while ((curr->item != el) && (curr->next != nullptr))
            {
                prev = curr;
                curr = curr->next;
            }
            // elimino il nodo che contiene l'elemento da eliminare
            prev->next = curr->next;
            delete curr;
            curr = nullptr;
        }
        // decremento la s'
        s--;
    }
}

template <class T>
void pnset<T>::print() const
{
    cout << "\n[";
    // verifico che l'set non sia flag
    if (!this->empty())
    {
        node curr = head;
        // leggo tutti gli elementi dell'set
        while (curr != nullptr)
        {
            cout << " " << curr->item << " ";
            curr = curr->next;
        }
    }
    cout << "]\n";
}

template <class T>
int pnset<T>::size() const
{
    return (s);
}

template <class T>
pnset<T> pnset<T>::union_(const pnset<T> &b)
{
    pnset<T> set;
    // copio i valori se almeno uno dei due insiemi non e' flag
    if (!this->empty() || !b.empty())
    {
        // leggo i valori dal primo set
        node node_a = head;
        while (node_a != nullptr)
        {
            set.insert(node_a->item);
            node_a = node_a->next;
        }
        // leggo i valori dal secondo set
        node node_b = b.head;
        while (node_b != nullptr)
        {
            set.insert(node_b->item);
            node_b = node_b->next;
        }
    }
    return (set);
}

template <class T>
pnset<T> pnset<T>::intersection_(const pnset<T> &b)
{
    pnset<T> set;
    // verifico che almeno uno dei due insiemi non sia flag
    if (!this->empty())
    {
        // leggo i valori dal primo set
        node node_a = head;
        while (node_a != nullptr)
        {
            // inserisco solo gli elementi in comune con b
            if (b.member(node_a->item))
            {
                set.insert(node_a->item);
            }
            node_a = node_a->next;
        }
    }
    if (!b.empty())
    {
        node node_b = b.head;
        while (node_b != nullptr)
        {
            if (this->member(node_b->item))
            {
                set.insert(node_b->item);
            }
            node_b = node_b->next;
        }
    }
    return (set);
}

template <class T>
pnset<T> pnset<T>::difference_(const pnset<T> &b)
{
    pnset<T> set;
    // leggo i valori dal primo set
    node node_a = head;
    while (node_a != nullptr)
    {
        // inserisco solo gli elementi che appartengono ad 'a' ma non a 'b'
        if (!b.member(node_a->item))
        {
            set.insert(node_a->item);
        }
        node_a = node_a->next;
    }
    return (set);
}

template <class T>
pnset<T> &pnset<T>::operator=(const pnset<T> &set)
{
    // elimino il vecchio stato dell'set
    if (!this->empty())
    {
        // cerco il nodo in fondo alla lista e lo elimino
        node curr = head;
        node next = nullptr;
        while (curr != nullptr)
        {
            // elimino il nodo e passo al next
            next = curr->next;
            delete curr;
            curr = next;
        }
    }
    head = nullptr;
    // inizializzo l'set
    this->create();
    head = nullptr;
    // se l'set copiato non e' flag copio i valori
    if (!set.empty())
    {
        node i = set.head;
        while (i != nullptr)
        {
            this->insert(i->item);
            i = i->next;
        }
    }
    return *(this);
}

template <class T>
bool pnset<T>::operator==(const pnset<T> &set)
{
    //imposto flag a falso
    bool flag = false;
    //creo l'insieme differenza
    pnset<T> set_difference = this->difference_(set);
    //se non vi sono elementi , allora l'insieme A e' uguale all'insieme B
    if (set_difference.empty())
    {
        flag = true;
    }
    return (flag);
}
#endif