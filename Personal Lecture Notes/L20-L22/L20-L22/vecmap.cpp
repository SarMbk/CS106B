#include "vecmap.h"

template <typename elemtype>
vecmap<elemtype>::vecmap(){

}

template <typename elemtype>
vecmap<elemtype>::~vecmap(){
}

template<typename elemtype>
elemtype vecmap<elemtype>::getValue(string key){
    int found = findIndexforKey(key);
    if (found == -1){
        error ("key not found");
    }
    return entries[found].val;
}

template<typename elemtype>
void vecmap<elemtype>::add(string key, elemtype val){
    pairT p;
    int found = findIndexforKey(key);
    if (found!=-1){
        entries[found].val = val;
    } else {
        p.key = key;
        p.val = val;
        entries.add(p);
    }
}

template<typename elemtype>
void vecmap<elemtype>::printAll(){
    for(int i=0; i<entries.size(); i++){
        cout << entries[i].key <<": "<< entries[i].val << endl;
    }
}

template<typename elemtype>
int vecmap<elemtype>::findIndexforKey(string key){
    for (int i=0; i<entries.size(); i++){
        if (entries[i].key == key) return i;
    }
    return -1;
}
