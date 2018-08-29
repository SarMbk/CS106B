#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "error.h"

template<typename ElemType>
class myqueue
{
public:
    myqueue();
    ~myqueue();

    bool isEmpty();
    void enqueue(ElemType e);
    ElemType dequeue();

private:
    struct cellT{
        ElemType val;
        cellT *next;
    };

    cellT *head, *tail;
};

#include "myqueue.cpp"
#endif // MYQUEUE_H
