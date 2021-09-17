#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
using namespace std;

template <class I, class N>
class tree
{
public:
	//tipi
	typedef I item;
	typedef N node;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual void insRoot() = 0;
	virtual void insFirstChild(node, item) = 0;
	virtual void insNextSibiling(node, item) = 0;
	virtual node getRoot() const = 0;
	virtual node parent(node) const = 0;
	virtual bool leaf(node) const = 0;
	virtual node firstChild(node) const = 0;
	virtual bool lastSibiling(node) const = 0;
	virtual node nextSibiling(node) const = 0;
	virtual void removeSubTree(node) = 0;
	virtual void write(node, item) = 0;
	virtual item read(node) const = 0;
	int depth() const;
	void depth(node, int, int &) const;
	int width() const;
	void width(node, int, int &) const;
	virtual ~tree(){};
};

template <class I, class N>
int tree<I, N>::depth() const
{
	int maxdepth;
	if (!empty())
	{
		maxdepth = 0;
		depth(getRoot(), 0, maxdepth);
	}
	else
	{
		maxdepth = -1;
	}
	return maxdepth;
}

template <class I, class N>
void tree<I, N>::depth(node curr, int currdepth, int &maxdepth) const
{
	if (!leaf(curr))
	{
		depth(firstChild(curr), currdepth + 1, maxdepth);
	}
	else
	{
		if (maxdepth < currdepth)
		{
			maxdepth = currdepth;
		}
	}
	if (!lastSibiling(curr))
	{
		depth(nextSibiling(curr), currdepth, maxdepth);
	}
}

template <class I, class N>
int tree<I, N>::width() const
{
	int maxwidth;
	if (!empty())
	{
		maxwidth = 1;
		width(getRoot(), 0, maxwidth);
	}
	else
	{
		maxwidth = 0;
	}
	return maxwidth;
}

template <class I, class N>
void tree<I, N>::width(node n, int currwidth, int &maxwidth) const
{
	if (leaf(n))
	{
		return;
	}
	node child = firstChild(n);
	currwidth = 1;
	while (!lastSibiling(child))
	{
		currwidth = currwidth + 1;
		child = nextSibiling(child);
	}
	if (maxwidth < currwidth)
	{
		maxwidth = currwidth;
	}
	width(firstChild(n), currwidth, maxwidth);
}

#endif
