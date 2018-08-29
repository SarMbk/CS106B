#ifndef HEAPPQ_H
#define HEAPPQ_H
#include "error.h"
#include <array>
using namespace std;


class heapPQ
{
public:    
    /* Constructor: heapPQ
     * Usage:   heapPQ hpq;
     *          heapPQ *hpq = new heapPQ;
     * Initializes a new heap based priority queue to have no elements */
    heapPQ();


    /* Destructor: ~heapPQ
     * Usage: delete hpq;
     * ------------------
     * Deallocates all the storage associated with this heap base priority queue */
    ~heapPQ();


    /* Member function: size();
     * Usage: int size = pq.size();
     * Returns an integer representing the number of entries contained in the priority queue */
    int size();


    /* Member function: isEmpty();
     * Usage: return pq.isEmpty();
     * Returns true if this instance of hybrid priority queue is empty, otherwise returns false */
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


    /* Member function: printAll;
     * Usage: pq.printAll();
     * prints all elements of the queue to the console, does not remove any elements; only prints
     * used during implementation for debugging */
    void printAll();

private:
    /* All numbers stored in an array */
    int *arr;
    int numUsed, numAllocated;
    /* Private method to increase capacity when array is full */
    void doubleCapacity();
};

#endif // HEAPPQ_H
