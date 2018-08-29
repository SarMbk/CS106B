#ifndef HYBRIDPQUEUE_H
#define HYBRIDPQUEUE_H

#include <iostream>
#include "error.h"
using namespace std;

class hpque
{
public:

    /* Constructor: hpque
     * Usage:   hpque pq;
     *          hpque *ppq = new hpque
     * Initializes a new hybrid priority queue to have no elements */
    hpque();


    /* Destructor: ~hpque
     * Usage: delete ppq;
     * ------------------
     * Deallocates all the storage associated with this hpque */
    ~hpque();


    /* Member function: size();
     * Usage: int size = pq.size();
     * Returns an integer representing the number of entries contained in the priority queue */
    int size();


    /* Member function: isEmpty();
     * Usage: return pq.isEmpty();
     * Returns true if this instance of hybrid priority queue is empty */
    bool isEmpty();


    /* Member function: enqueue(int num);
     * Usage: pq.enqueue(val);
     * Adds the specified element to this pqueue. No effort is made to avoid duplicates */
    void enqueue(int num);


    /* Member function: dequeueMax();
     * Usage: maxElem = pq.dequeueMax();
     * Removes the largest priority element from this pqueue and returns it.
     * If this pqueue is empty, this function raises an error */
    int dequeueMax();


    /* Member function: dequeueMin();
     * Usage: maxElem = pq.dequeueMin();
     * Removes the smallest priority element from this pqueue and returns it.
     * If this pqueue is empty, this function raises an error */
    int dequeueMin();


    /* Member function: printAll;
     * Usage: pq.printAll();
     * prints all elements of the queue to the console, does not remove any elements; only prints
     * used during implementation for debugging */
    void printAll();

private:
    /* Size of array inside a node is defined by this constant */
    static const int NODE_SIZE = 5;

    /* This is a doubly linked list so it has an array, a variable to track number of used variables and
     * two pointers pointing to next and previous nodes */
    struct nodeT{
        int arr[NODE_SIZE];
        int numUsed;
        nodeT *next;
        nodeT *prev;
    };

    /* Standard for any linked list, head and tail pointers */
    nodeT *head, *tail;

    /* Private helper functions unavailable for use outside the class */
    void orderedInsert(int num, nodeT *node);
    void splitNode(nodeT *node);
};

#endif // HYBRIDPQUEUE_H
