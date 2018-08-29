#include "mystack.h"


template <typename ElemType>
mystack<ElemType>::mystack(){
    head = nullptr;
}


template <typename ElemType>
mystack<ElemType>::~mystack(){
    // delete entire list
}


template<typename ElemType>
bool mystack<ElemType>::isEmpty(){
    return (head==nullptr);
}


template<typename ElemType>
void mystack<ElemType>::push(ElemType e){
    cellT *newCell = new cellT;
    newCell->val = e;
    newCell->next = head;
    head = newCell;
}


template<typename ElemType>
ElemType mystack<ElemType>::pop(){
    if (isEmpty()) error("pop emty stack");
    ElemType top = head->val;
    cellT *old = head;
    head = head->next;
    delete old;
    return top;
}




