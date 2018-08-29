#include "myqueue.h"


template <typename ElemType>
myqueue<ElemType>::myqueue(){
    head = tail = nullptr;
}


template <typename ElemType>
myqueue<ElemType>::~myqueue(){
    // delete entire queue
}


template<typename ElemType>
bool myqueue<ElemType>::isEmpty(){
    return (head == nullptr);
}


template<typename ElemType>
void myqueue<ElemType>::enqueue(ElemType e){
    cellT *newCell = new cellT;
    newCell->val = e;
    newCell->next = nullptr;

    if (isEmpty()){
        head = tail = newCell;
    } else {
        tail->next = newCell;
        tail = newCell;
    }
}


template<typename ElemType>
ElemType myqueue<ElemType>::dequeue(){
    if (isEmpty()) error("dequeue empty queue");
    ElemType front = head->val;
    cellT *old = head;
    head = head->next;
    delete old;
    return front;
}
