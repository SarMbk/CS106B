#ifndef MOB_H
#define MOB_H
#include <iostream>
#include "vector.h"
#include "random.h"
using namespace std;

template<typename ElemType>
class mob
{
public:
    mob();
    ~mob();
    void enqueue(ElemType newElem);
    ElemType dequeue();
    int size();
    void printAll();

private:
    Vector<ElemType> elems;

};

#include "mob.cpp"
#endif // MOB_H
