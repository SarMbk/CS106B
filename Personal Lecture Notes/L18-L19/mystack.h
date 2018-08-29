#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include "vector.h"
#include "error.h"
using namespace std;

template <typename ElemType>
class mystack
{
public:
    mystack();
    ~mystack();

    int size();
    void push(ElemType e);
    ElemType pop();
    bool isEmpty();
    void reverse();
    string print();


private:
    Vector<ElemType> elems;
};

#include "mystack.cpp"
#endif // MYSTACK_H
