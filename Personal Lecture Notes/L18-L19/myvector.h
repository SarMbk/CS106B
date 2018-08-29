#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include "error.h"
using namespace std;

template <typename ElemType>
class myvector
{
public:
    myvector();
    ~myvector();

    int size();
    void add(ElemType s);
    void insertAt(int index, ElemType e);
    ElemType getAt(int index);
    void print();

private:
    ElemType *arr;
    int numUsed, numAllocated;
    void doubleCapacity();
};



#include "myvector.cpp"
#endif // MYVECTOR_H
