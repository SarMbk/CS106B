#include "mystack.h"

template <typename ElemType>
mystack<ElemType>::mystack()
{
}


template <typename ElemType>
mystack<ElemType>::~mystack()
{
}


template <typename ElemType>
int mystack<ElemType>::size(){
    return elems.size();
}


template <typename ElemType>
ElemType mystack<ElemType>::pop(){
    if(isEmpty()) error("empty stack");
    ElemType top = elems.get(elems.size()-1);
    elems.remove(elems.size()-1);
    return top;
}


template <typename ElemType>
void mystack<ElemType>::push(ElemType e){
    elems.add(e);
}


template <typename ElemType>
bool mystack<ElemType>::isEmpty(){
    if (elems.size()==0) return true;
    return false;
}


template <typename ElemType>
void mystack<ElemType>::reverse(){
    int mid = size()/2;
    for (int i=0; i<mid; i++){
        //swap(elems[elems.size()-1-i] = elems[i]);
        ElemType tmp = elems[elems.size()-1-i];
        elems[elems.size()-1-i] = elems[i];
        elems[i] = tmp;
    }
}


template<typename ElemType>
string mystack<ElemType>::print(){
    string s = elems.toString();
    return s;
}

