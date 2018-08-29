#include "mymap.h"

template <typename elemtype>
myMap<elemtype>::myMap(){
    for (int i=0; i<NUM_BUCKETS; i++)
        buckets[i] = nullptr;
}


template <typename elemtype>
myMap<elemtype>::~myMap(){
    // empty
}


const long Multiplier = -1664117991L;
template <typename elemtype>
int myMap<elemtype>::hash(string key, int nBuckets){
    unsigned long hashcode = 0;
    for (int i = 0; i < key.length(); i++) {
       hashcode = hashcode * Multiplier + key[i];
    }
    return (hashcode % nBuckets);
}


template <typename elemtype>
typename myMap<elemtype>:: cellT* myMap<elemtype>::findCell(string key, cellT *list){
    for (cellT *cur = list; cur != nullptr; cur = cur->next)
        if (cur->key == key) return cur;
    return nullptr;
}


template <typename elemtype>
elemtype myMap<elemtype>::getValue(string key){
    int whichBucket = hash(key, NUM_BUCKETS);
    cellT *match = findCell(key, buckets[whichBucket]);
    if (match != nullptr){
        return match->value;
    }
    error("no such key found");
}


template <typename elemtype>
void myMap<elemtype>::add(string key, elemtype val){
    int whichBucket = hash(key, NUM_BUCKETS);
    cellT *match = findCell(key, buckets[whichBucket]);
    if (match != nullptr)
        match->value = val;
    else{
        cellT *newOne = new cellT;
        newOne->key = key;
        newOne->value = val;
        newOne->next = buckets[whichBucket];
        buckets[whichBucket] = newOne;
    }
}
