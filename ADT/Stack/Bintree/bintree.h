#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <string>
using namespace std;

template <class I, class N>
class bintree
{
public:
	//tipi
	typedef I item;
	typedef N node;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual node get_root() const = 0;
	virtual node parent(node) const = 0;
	virtual node sx(node) const = 0;
	virtual node dx(node) const = 0;
	virtual bool sx_empty(node) const = 0;
	virtual bool dx_empty(node) const = 0;
	virtual bool leaf(node) const = 0;
	virtual void erase(node) = 0;
	virtual item read(node) const = 0;
	virtual void write(node, item) = 0;
	virtual void ins_root() = 0;
	virtual void ins_sx(node, item) = 0;
	virtual void ins_dx(node, item) = 0;
	virtual void preorder(node) const = 0;
	virtual void inorder(node) const = 0;
	virtual void postorder(node) const = 0;
	virtual bool is_empty_node(node) const = 0;
	virtual int depth() const = 0;
	void print() const;
	virtual ~bintree(){};

private:
	void printSubTree(const node) const;
};

template <class I, class N>
void bintree<I, N>::print() const
{
	if (!empty())
	{
		printSubTree(get_root());
	}
	else
	{
		std::cout << "[]" << std::endl;
	}
	std::cout << std::endl;
}

template <class I, class N>
void bintree<I, N>::printSubTree(const node n) const
{
	std::cout << "[" << read(n) << ", ";
	if (!sx_empty(n))
	{
		printSubTree(sx(n));
	}
	else
	{
		std::cout << "NIL";
	}
	std::cout << ", ";
	if (!dx_empty(n))
	{
		printSubTree(dx(n));
	}
	else
	{
		std::cout << "NIL";
	}
	std::cout << " ]";
}

template <class I, class N>
std::ostream &operator<<(std::ostream &os, const bintree<I, N> &t)
{
	t.print();
	return (os);
}

#endif
