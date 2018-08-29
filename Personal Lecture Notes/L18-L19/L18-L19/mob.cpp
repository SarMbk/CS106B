#include "mob.h"


template<typename ElemType>
mob<ElemType>::mob(){}


template<typename ElemType>
mob<ElemType>::~mob(){}


template<typename ElemType>
void mob<ElemType>::enqueue(ElemType newElem){
    elems.add(newElem);
}


template<typename ElemType>
ElemType mob<ElemType>::dequeue(){
    int elemNum = randomInteger(0, elems.size()-1);
    ElemType value = elems.get(elemNum);
    elems.remove(elemNum);
    return value;
}


template<typename ElemType>
int mob<ElemType>::size(){
    return elems.size();
}


template<typename ElemType>
void mob<ElemType>::printAll(){
    while(elems.size()>0){
        ElemType value = dequeue();
        cout << value << endl;
    }
}
