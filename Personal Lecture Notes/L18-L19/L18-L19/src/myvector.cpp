#include "myvector.h"

/* Constructor */
template <typename ElemType>
myvector<ElemType>::myvector(){
    arr = new ElemType[2];
    numAllocated = 2;
    numUsed = 0;
}


/* Destructor */
template <typename ElemType>
myvector<ElemType>::~myvector(){
    delete[] arr;
}


template <typename ElemType>
int myvector<ElemType>::size(){
    return numUsed;
}


template <typename ElemType>
void myvector<ElemType>::add(ElemType el){
    if (numUsed==numAllocated) doubleCapacity();
    arr[numUsed++] = el;
}

template <typename ElemType>
ElemType myvector<ElemType>::getAt(int index){
    if (index<0 || index >=size()) error("out of bounds");
    return arr[index];
}


template <typename ElemType>
void myvector<ElemType>::doubleCapacity(){
    ElemType *bigger = new ElemType[numAllocated*2];
    for (int i=0; i<numUsed; i++){
        bigger[i] = arr[i];
    }
    delete[] arr;
    arr = bigger;
    numAllocated*=2;
}


template <typename ElemType>
void myvector<ElemType>::print(){
    for (int i=0; i<numUsed; i++){
        cout << getAt(i) << endl;
    }
}


template <typename ElemType>
void myvector<ElemType>::insertAt(int index, ElemType e){
    if (index<0 || index >=size()) error("out of bounds");
    if (numUsed==numAllocated) doubleCapacity();
    for (int i=size()-1; i>= index; i--)
        arr[i+1] = arr[i];
    arr[index] = e;
    numUsed++;
}


