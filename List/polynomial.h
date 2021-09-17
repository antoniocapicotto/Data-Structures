#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "listvector.h"
using namespace std;

class polynomial
{
public:
    polynomial();
    ~polynomial();
    int grado();
    int valore(int x);
    //visualizza il polinomio
    void output(ostream &outStream);
    /*
    acquisisce un polinomio dallo stream di input inStream
    .Possiamo assumere che l'input sia il grado del polinomio seguito dai valori dei coefficienti.
    */
    void input(istream &inStream);
    //somma con il polinomio b
    void somma(const polynomial &b);
    //moltiplica con il polinomio b
    void moltiplica(const polynomial &b);
    polynomial &operator=(const polynomial &);

private:
    listvector<int> l;
};

polynomial::polynomial()
{
    l.create(); //inizializzo un polinomio di grado 0
}

polynomial::~polynomial()
{
    l.~listvector();
}

int polynomial::grado()
{
    return (l.size());
}

int polynomial::valore(int x)
{
    int v;
    if (!l.empty())
    {
        v = l.read(x); //restituisco il valore del polinomio con coefficiente x
    }
    return (v);
}

void polynomial::somma(const polynomial &b)
{
    auto j = b.l.begin();
    for (auto i = l.begin(); !l.end(i) && !b.l.end(j); i = l.next(i))
    {
        l.write(l.read(i) + b.l.read(j), i);
        j = b.l.next(j);
    }
    if (!b.l.end(j))
    {
        while (!b.l.end(j))
        {
            l.push_back(b.l.read(j));
            j = b.l.next(j);
        }
    }
}

void polynomial::output(ostream &outStream)
{
    for (auto i = l.begin(); !l.end(i); i = l.next(i))
    {
        if (l.read(i) != -1)
        {
            cout << "[" << i << "]coefficiente: " << l.read(i) << endl;
        }
    }
}

void polynomial::input(istream &inStream)
{
    int grado = 0;
    int valore = 0;
    cout << "inserisci grado: ";
    cin >> grado;
    cout << endl
         << "inserisci elementi: " << endl;
    int i = 0;
    while (i < grado)
    {
        cout << "\nn: ";
        cin >> valore;
        l.push_back(valore);
        i++;
    }
}

void polynomial::moltiplica(const polynomial &b)
{
    listvector<int> pl;
    int k;
    int s = l.size() + b.l.size();
    int it = 0;
    while (it < s)
    {
        pl.push_back(-1);
        it++;
    }
    //moltiplico ciascuno elemento del primo per il secondo e mano mano che vengono moltiplicati aumenta il grado del polinomio
    for (auto i = l.begin(); !l.end(i); i = l.next(i))
    {
        for (auto j = b.l.begin(); !b.l.end(j); j = b.l.next(j))
        {
            if (i + j != k)
            {
                pl.insert(l.read(i) * b.l.read(j), i + j);
            }
            else
            {
                int p = l.read(i) * b.l.read(j);
                pl.write(p+pl.read(i+j), i + j);
            }
            k = i + j;//grado precedente
        }
    }
    this->l = pl;
}

polynomial &polynomial::operator=(const polynomial &b)
{
    l = b.l;
    return *this;
}

#endif
