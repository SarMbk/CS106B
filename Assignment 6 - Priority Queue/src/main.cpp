/* File: main.cpp
 * --------------
 * Simple main module for PQueue assignment.
 */
 
#include "pqueuetest.h"
#include "performance.h"
#include <iostream>
#include "console.h"
#include "hybridpqueue.h"
#include "heappq.h"
#include "random.h"
using namespace std;



/*
 * Use these functions to test your PQueue implementation.
 * Comment out those tests you aren't interested in running
 * while you are mid-development.
 */

int main(){
    /*
    // This part tests hybrid PQ
    hpque hpq;
    for (int i=0; i<100; i++){
        int num = randomInteger(0, 15);
        hpq.enqueue(num);
    }

    cout << endl;
    hpq.printAll();
    cout << "size: " << hpq.size() << endl << endl;

    int count =0;
    while (!hpq.isEmpty()){
        cout << hpq.dequeueMin() << " ";
        count++;
    } cout << endl << "count: " << count << endl;
    */



    // This part is the stanford tester
    //BasicPQueueTest();
    //MorePQueueTest();
    //PQueueSortTest();
    //PQueuePerformance();
    //cout << endl << "Goodbye and have a nice day!" << endl;



    // This part tests heap PQ

    heapPQ pq;
    pq.enqueue(1); pq.enqueue(0); pq.enqueue(1); pq.enqueue(0);

    for (int i=0; i<20; i++){
        pq.enqueue(randomInteger(0,100));
    }
    pq.printAll();
    cout << "size " << pq.size() << endl<< endl;

    int count =0;
    while(!pq.isEmpty()){
        cout << pq.dequeueMax() << endl;
        count++;
    }
    cout << endl << "count=" << count << endl;

    return (0);
}

/* Comments about different implementations of the priority queue
 *
 * 1. Linked List Implementation:
 *      -Memory Usage
 *      Linked list has to store a pointer to the next cell with each entry. That takes up some extra mamory.
 *      However there is never any extra memory reserved and unused.
 *
 *      -Speed of Operations:
 *      Enqueueing complexity is O(N). Every time we enqueue we have to go down the list and look at each entry one by
 *      one to find the correct spot to insert the entry into so it was in sorted order.
 *      Dequeueing is fast, runs in constant time. Only need to dequeue the largest entry and rewire the list.
 *
 *      -Difficulty of writing and maintaining:
 *      More difficult than a vector implementation but not super difficult.
 *
 * 2. Unsorted Vector Implementation:
 *      -Memory Usage:
 *      No extra memory overhead. Only when a vector becomes full, the new vector is created with double the capacity
 *      and the vector at that moment has twice the reserved memory which is unused.
 *
 *      -Speed of Operations:
 *      Enqeueing is just appending an entry at the end of a vector. It runs in constant time O(1).
 *      When dequeueing we perform a linear search for the largest element so it's complexity is O(N).
 *
 *      -Difficulty of writing and maintaining:
 *      Easy. Easiest of the four options considered in this exercise.
 *
 * 3. Sorted Chunklist (hybridpqueue) Implementation:
 *      -Memory Usage:
 *      Uses extra memory for pointers to other cells as any linked list does. However, because one cell
 *      contains an array of entries and not just one entry, for the same size of problem,
 *      pointers take up a lesser portion of memory than they do in the regular linked list implementation.
 *      When a cell becomes full, a new cell is created by breaking up an existing cell in half. In the end
 *      it likely results in a linked list of partially full arrays, and that's reserving extra memory that is not
 *      efficiently used.
 *
 *      -Speed of Operations:
 *      Enqueueing has complexity O(N). Dequeuing runs in constant time i.e. O(1).
 *      See comments in the implementation file for reasoning.
 *
 *      -Difficulty of writing and maintaining:
 *      The most difficult of the four options considered in this exercise.
 *
 * 4. Heap (heappq) Implementation:
 *      -Memory Usage:
 *      No extra memory overhead. Only when a vector becomes full, the new vector is created with double the capacity
 *      and the vector at that moment has twice the reserved memory which is unused. Same as the vector implementation.
 *
 *      -Speed of Operations:
 *      Both enqueuing and dequeuing run in logarithmic time i.e. O(N). See comments in the implementation file
 *      for reasoning.
 *
 *      -Difficulty of writing and maintaining:
 *      Not too difficult. Took me less than 5 hours to write from scratch. Medium difficulty.
 */
























