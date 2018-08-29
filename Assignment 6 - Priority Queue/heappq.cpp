#include "heappq.h"

/* Constructor. Zeroth element of an array is never used. That's why we initiate an array for 3 ints but
 * initiate numAllocated to 2 */
heapPQ::heapPQ(){
    arr = new int[3];
    arr[0] = 0; // zeroth element is never used and is always zero
    numAllocated = 2;
    numUsed = 0;
}


/* Destructor, deleting the array */
heapPQ::~heapPQ(){
    delete [] arr;
}


/* Public method returns the number of elements currently in the queue */
int heapPQ::size(){
    return numUsed;
}


/* Returns true if queue is empty */
bool heapPQ::isEmpty(){
    return (numUsed==0);
}


/* Implementation of the enqueue method, uses heap method of sorting. Complexity O(logN). */
void heapPQ::enqueue(int num){
    /* If the array is full, double its capacity first */
    if (numUsed==numAllocated)
        doubleCapacity();

    /*If the array is empty, assign the value of array at position 1 (not zero!) to num. Note: zeroth element
     * is never used. It is always zero. That's because it's easier to leave off the zeroth element and deal with
     * indexes starting from one when elements are sorted in a heap */
    if (numUsed==0){
        arr[1] = num;
        numUsed++;
        return;
    }

    /* If array is not empty, assign num to the next available position in an array and bubble it up according
     * to the heap logic. Every step up the heap halves the number of elements to consider.
     * Therefore big O(Log base 2 of N) or just O(logN) */
    else if (numUsed>0) {
        arr[++numUsed] = num;
        int index= numUsed;
        while (arr[index] > arr[index/2] && index/2 >=1){
            swap(arr[index], arr[index/2]);
            index = index/2;
        }
    }
}


/* Implementation of the dequeue method, uses the heap logic to re-sort the elements.
 * Therefore complexity is also O(logN) */
int heapPQ::dequeueMax(){
    /* Throw an error if dequeuing an empty queue */
    if (isEmpty()) error("Cannot dequeue an empty queue");

    /* Largest element is always at position 1 (not at zero, position zero is never used) */
    int result = arr[1];

    /* If there is only one element in the queue */
    if (numUsed==1){
        numUsed--;
        return result;
    }

    /* If there is more than one element in the queue */
    else {
        arr[1] = 0;  //the value of the larges element is already noted, so just set the arr[1] to zero for cleanliness
        swap(arr[1], arr[numUsed]);  //put the last element in at position 1
        numUsed--;  //decrement numUsed
        int index = 1;
        /* Trickle down value that we just placed from the end to the root of the heap.
         * Continue while the value is greater than either of it's daughters and you
         * didn't yet hit the end of the array */
        while( (arr[index]< arr[2*index] || arr[index] < arr[2*index+1]) && 2*index<=numUsed){
            /* These two conditionals say: swap the value with the greater one of it's daughters and increment
             * the index according to the heap sorting logic */
            if (arr[2*index+1] >= arr[2*index]){
                swap(arr[index], arr[2*index+1]);
                index = 2*index+1;
            }
            else {
                swap(arr[index], arr[2*index]);
                index = 2*index;
            }
        }
    }
    /* Once the heap is re-sorted again, return the value */
    return result;
}


/* Used for debugging */
void heapPQ::printAll(){
    for (int i=0; i<=numUsed; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}


/* Implementation of the private, doubleCapacity method. Creates a new array with double the capacity and
 * copies the elements to the new bigger array. Thus the complexity is O(N) */
void heapPQ::doubleCapacity(){
    int *bigger = new int[numAllocated*2];
    for (int i=1; i<=numUsed; i++){
        bigger[i] = arr[i];
    }
    delete[] arr;
    arr = bigger;
    numAllocated*=2;
}
