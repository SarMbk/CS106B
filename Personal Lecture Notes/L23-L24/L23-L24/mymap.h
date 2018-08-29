#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
#include <string>
#include "error.h"
using namespace std;

template <typename elemtype>
class myMap
{
public:
    myMap();
    ~myMap();

    void add(string key, elemtype val);
    elemtype getValue(string key);
    void printAll();

private:
    static const int NUM_BUCKETS = 99;

    struct cellT{
        string key;
        elemtype value;
        cellT *next;
    };

    cellT *buckets[NUM_BUCKETS]; // Syntax for declaring an array of pointers to cells

    int hash(string key, int nBuckets);
    cellT *findCell(string key, cellT *list); // Syntax for function returning a pointer to a cell
};

#include "mymap.cpp"
#endif // MYMAP_H
