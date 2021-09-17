#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include "./../list/listvector.h"
#include "./../list/linkedlist.h"
#include "./../queque/pnqueque.h"
using namespace std;

template <class P, class N>
class arch
{
public:
    N node1;  //nodo uscente a->b
    N node2;  //nodo entrante b<-a
    P weight; //peso
};

template <class E, class P, class N>
class graph
{
public:
    // definisco un alias per i tipi
    typedef E label;  //etichetta
    typedef P weight; //peso
    typedef N node;   //nodo
    //definisco le classi come nuovi tipi
    typedef class arch<weight, node> arch;                 //tipo nodoarco<peso,nodo>
    typedef listvector<node> listnode;                     //tipo listanodi grafo
    typedef typename listnode::position position_listnode; //tipo posizione di listanodi grafo
    typedef listvector<arch> listarch;                     //tipo lista nodi arco
    //operatori
    virtual void create() = 0;
    virtual bool empty() const = 0;
    virtual void insNode(node &) = 0;
    virtual void insArch(node, node, weight) = 0;
    virtual void eraseNode(node) = 0;
    virtual void eraseArch(node, node) = 0;
    virtual bool isNode(node) const = 0;
    virtual bool isArch(node, node) const = 0;
    virtual listnode adjacent(node) const = 0;
    virtual listnode listNode() const = 0;
    virtual label readLabel(node) const = 0;
    virtual void writeLabel(node, label) = 0;
    virtual weight readWeight(node, node) const = 0;
    virtual void writeWeight(node, node, weight) = 0;
    virtual int numNodes() const = 0;
    virtual int numArches() const = 0;
    virtual void dfs(node) const = 0;
    virtual ~graph(){};
};

#endif
