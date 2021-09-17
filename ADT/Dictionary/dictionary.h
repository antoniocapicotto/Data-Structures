#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
using namespace std;

/* 
 * A dictionary is a collection of pairs of the form (k,v), where k is a key and v is the value
 * associated with the key k (equivalently, v is the value whose key is k).
 */
template <class K, class E>
struct mypair
{
	//data member
	K first;
	E second;
	//methods
	mypair() {}
	mypair(K the_key, E the_element)
	{
		first = the_key;
		second = the_element;
	}
	mypair(mypair<K, E> &the_pair)
	{
		first = the_pair.first;
		second = the_pair.second;
	}
	mypair<K, E> &operator=(const mypair<K, E> &the_second)
	{
		first = the_second.first;
		second = the_second.second;
		return *(this);
	}
	bool operator==(const mypair<K, E> &the_pair)
	{
		return ((first == the_pair.first) && (second == the_pair.second));
	}
	friend ostream &operator<<(ostream &os, const mypair<K, E> &mp)
	{
		os << " < " << mp.first << ", " << mp.second << " > ";
		return (os);
	}
};

template <class K, class E>
class dictionary
{
public:
	//tipi
	typedef K key;
	typedef E label;
	//operatori
	virtual void create() = 0; //create an empty dictionary
	virtual bool empty() const = 0;
	virtual int size() const = 0;					 //return the number of pairs in dictionary
	virtual mypair<K, E> *find(const K &) const = 0; //return the pair with key k
	virtual void insert(mypair<K, E> &) = 0;		 //insert the pair into the dictionary
	virtual void remove(const K &) = 0;				 //delete the pair with key k
	virtual void modify(const K &, const E &) = 0;	 //modify the value of the pair with key k to e
	virtual ~dictionary(){};
};

#endif
