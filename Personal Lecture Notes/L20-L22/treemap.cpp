#include "treemap.h"

template <typename elemtype>
treeMap<elemtype>::treeMap(){
    root = nullptr;
}


template <typename elemtype>
treeMap<elemtype>::~treeMap(){
}


template <typename elemtype>
elemtype treeMap<elemtype>::getValue(int key){   // get value as a wrapper for treesearch recursive function
    node *found = treeSearch(root, key);
    if (found==nullptr) error("Get value of non-existent key!");
    return found->value;
}


// Pay attention to syntax. This is how to return a private variable of a class
template <typename elemtype>
typename treeMap<elemtype>::node *treeMap<elemtype>::treeSearch(node *t, int key){
    if (t==nullptr) return nullptr;     // doesn't exist
    if (key == t->key) return t;        // found match
    else if (key < t->key) return treeSearch(t->left, key);
    else return treeSearch(t->right, key);
}


template <typename elemtype>
void treeMap<elemtype>::add(int key, elemtype val){  // add entry as a wrapper for a recursive function
    treeEnter(root, key, val);
}


template <typename elemtype>
void treeMap<elemtype>::treeEnter(node *&t, int key, elemtype val){
    if (t==nullptr){
        t = new node;
        t->key = key;
        t->value = val;
        t->left = t->right = nullptr;
    }
    else if (key == t->key){
        t->value = val;
    }
    else if (key < t->key){
        treeEnter(t->left, key, val);
    }
    else {
        treeEnter(t->right, key, val);
    }
}


template <typename elemtype>
void treeMap<elemtype>::treePrint(node *t){
    if (t != nullptr){
        treePrint(t->left);
        cout << t->key << endl;
        treePrint(t->right);
    }
}


template <typename elemtype>
void treeMap<elemtype>::printAll(){
    treePrint(root);
}




















