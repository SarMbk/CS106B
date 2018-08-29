#ifndef VECMAP_H
#define VECMAP_H

#include <iostream>
#include <string>
#include "vector.h"
#include "error.h"
using namespace std;

template <typename elemtype>
class vecmap
{
public:
    vecmap();
    ~vecmap();

    void add(string key, elemtype val);
    elemtype getValue(string key);
    void printAll();

private:
    struct pairT{
        string key;
        elemtype val;
    };
    Vector <pairT> entries;

    int findIndexforKey(string key);
};

#include "vecmap.cpp"
#endif // VECMAP_H
