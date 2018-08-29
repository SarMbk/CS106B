#ifndef MYSTACK_H
#define MYSTACK_H

#include "error.h"

template <typename ElemType>
class mystack
{
public:
    mystack();
    ~mystack();

    bool isEmpty();
    void push(ElemType e);
    ElemType pop();

private:
    struct cellT{
        ElemType val;
        cellT *next;
    };

    cellT *head;
};


#include "mystack.cpp"
#endif // MYSTACK_H

