#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <string>
#include "error.h"
using namespace std;

template <typename elemtype>
class treeMap
{
public:
    treeMap();
    ~treeMap();

    void add(int key, elemtype val);
    elemtype getValue(int key);
    void printAll();

private:
    struct node
    {
        int key;
        elemtype value;
        node *left, *right;
    };

    node *root;
    node *treeSearch(node *t, int key);
    void treeEnter(node *&t, int key, elemtype val);
    void treePrint(node *t);
};

#include "treemap.cpp"
#endif // TREEMAP_H
