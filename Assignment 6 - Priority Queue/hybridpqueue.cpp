#include "hybridpqueue.h"


/* Constructor, only required to initiate the head of the list to a null pointer */
hpque::hpque(){
    head = nullptr;
    tail = nullptr;
}


/* Destructor, follow through the linked list one by one and delete all blocks */
hpque::~hpque(){
    while(head!=nullptr){
        nodeT *next = head->next;
        delete head;
        head = next;
    }
}


/* Method to check if the linked list is empty */
bool hpque::isEmpty(){
    return (head==nullptr);
}


/* Implementation of the enqueue method. Whenever we insert an element, we insert it into a constant size vector,
 * so insertion runs in constant time. However we need to find the correct node to insert a number into. To achieve
 * that, we look at an element at the end of each node. Because of this, the enqueueing complexity is O(N) */
void hpque::enqueue(int num){

    /* If the list is empty, create a new node and wire the head and tail to it, it is the only node, so the
     * next and prev values are nullptr */
    if (isEmpty()){
        nodeT *newBlock = new nodeT;
        newBlock->numUsed = 0;
        newBlock->next = nullptr;
        newBlock->prev = nullptr;
        head = newBlock;
        tail = newBlock;
        orderedInsert(num, newBlock);
    }

    /* Otherwise, if the list is not empty, then find the right node to enqueue the number into. Start from the tail and
     * look at the last number of each node one by one going backwards. Since the numbers are being placed in ascending
     * order, if the number is >= than the last number of the node, then it is the correct node to place the num into.
     * Note when this while loop breaks out, the cur pointer points to the the node just before the required node,
     * so we need to increment cur by one node once it has broken out of the loop */
    else{
        nodeT *cur;
        cur = tail;
        while (cur!=nullptr && num < cur->arr[cur->numUsed-1]){
            cur = cur->prev;
        }

        /* The num may be the smallest number so far, in which case cur will iterate through the whole linked list
         * and be equal to nullptr i.e. there is no more nodes before it, in this case set cur to the head of
         * the linked list so it added the num to the first node */
        if (cur==nullptr)
            cur = head;

        /* When the while loop breaks out, cur points at a node just before the required node, so we need to
         * increment by one */
        else if (cur->next != nullptr)
            cur = cur->next;

        /* It the node that we now found is not full, just insert the number into that node */
        if (cur->numUsed < NODE_SIZE)
            orderedInsert(num, cur);

        /* Otherwise, split the node and insert the number into one of the two resulting nodes depending
         * on whether the number is greater or less than the number that was in the middle of the yet unsplit node */
        else {
            splitNode(cur);
            if (num <= cur->arr[cur->numUsed-1])
                orderedInsert(num, cur);
            else
                orderedInsert(num, cur->next);
        }
    }
}


/* Private helper function: given the node, insert number into the array of the node in sorted order, regardles of the
 * size of the problem, whenever we insert a number into a node we are always dealing with a node of constant size.
 * Therefore, this operation runs in constant time */
void hpque::orderedInsert(int num, nodeT *node){
    /* If node is empty */
    if (node->numUsed==0)
        node->arr[0] = num;

    /* If node is not empty, use the conventional ordered insert algorithm of shifting all numbers to the side
     * and inserting the num at the appropriate position */
    else {
        int i = node->numUsed;
        while ((i > 0) && (num < node->arr[i-1])){
            node->arr[i] = node->arr[i-1];
            i--;
        }
        node->arr[i] = num;
    }
    node->numUsed++;
}


/* Used for debugging only */
void hpque::printAll(){
    nodeT *cur;
    for (cur=head; cur!=nullptr; cur=cur->next){
        for (int i=0; i<cur->numUsed; i++){
            cout << cur->arr[i] << " ";
        }
        cout << endl;
    }
}


/* Split the block in two halves down the middle when it is full in order to be able to insert a num into the queue
 * This problem also inly splits one node locally and rewires them. Therefore it tuns in constant time */
void hpque::splitNode(nodeT *node){
    /* Copy second half of elements from a full block into the first half of positions of the new block */
    nodeT *otherHalf = new nodeT;
    for (int i = NODE_SIZE/2; i<NODE_SIZE; i++){
        otherHalf->arr[i-NODE_SIZE/2] = node->arr[i];
        node->arr[i] = 0;
    }

    /* Update numUsed for both blocks */
    otherHalf->numUsed =NODE_SIZE-NODE_SIZE/2; // this is in case NODE_SIZE is an odd number
    node->numUsed = NODE_SIZE/2;

    /* Re-wire the linked list i.e. splice otherHalf into the linked list */
    /* If we just split the last node of the list, splice the new half to the end of list */
    if (node->next == nullptr){
        tail = otherHalf;           //wire the tail to the new node
        node->next = otherHalf;     //wire old node to the new node
        otherHalf->prev = node;     //wire new node back to old node
        otherHalf->next = nullptr;  //since we are adding from the back, otherHalf is now the last node.
    }
    /* If it is somewhere else in the list, break the node and splice the new half in the middle of the list */
    else {
        node->next->prev = otherHalf;   //wire the node that's after the old node to the new node backwards
        otherHalf->next = node->next;   //wire new node to the node that was after the old node
        node->next = otherHalf;         //wire new node after the old one going forward
        otherHalf->prev = node;         //wire new node after the old one going backwards
    }
}


/* Returns the number of elements currently stored in the  queue */
int hpque::size(){
    nodeT *cur;
    int size = 0;
    for (cur = head; cur!= nullptr; cur=cur->next)
        size+=cur->numUsed;
    return size;
}


/* Implementation of the dequeueMax method, dequeues the largest number. Dequeuing is very efficient.
 * Since when we enqueue, elements into the list in a sorted order, we simply get the last element at the tail
 * and reqire the nodes (if necessary when the node becomes empty as a result of dequeueing). Thus, dequeueing
 * runs in constant time */
int hpque::dequeueMax(){
    if(isEmpty()) error("Trying to dequeue an empty queue");

    /* Get the value and decrement the numUsed in the node */
    int num = tail->arr[tail->numUsed-1];   // Get the value to dequeue; (first one from the end)
    tail->arr[tail->numUsed-1] = 0;         // Set the unused space in vector to zero
    tail->numUsed--;                        // Decrement the numUsed of the node

    /* If after you dequeue a number, the node becomes empty, delete the node and rewire the linked list */
    if (tail->numUsed == 0){
        nodeT *toBeDeleted = tail;      // Note the adress of the node to be deleted
        if (tail->prev!=nullptr){       // If there are more nodes behind this one
            tail = tail->prev;          // Wire the tail pointer to the previous node
            tail->next = nullptr;       // Since it's there is no next node, set the tail->next to null
        }
        else if (tail->prev==nullptr){  // If it is the only node left and no previous nodes in front of it
            tail = nullptr;             // set head and tail to null
            head = nullptr;
        }
        delete toBeDeleted;             // In any case, delete the current node
    }

    return num;
}


/* Implementation of the dequeueMin method, dequeues the lowest number. This method also runs in constant time
 * for the same reasons as described in the dequeueMax() method */
int hpque::dequeueMin(){
    if(isEmpty()) error("Trying to dequeue an empty queue");

    /* Get the value and decrement the numUsed in the node */
    int num = head->arr[0];                 // Get the value to dequeue; (first one from the start)
    for (int i=1; i<head->numUsed; i++){    // After dequeing shift all remaining elements back one step
        head->arr[i-1] = head->arr[i];
    }
    head->arr[head->numUsed-1] = 0;         // Set the newly unused space in vector to zero
    head->numUsed--;                        // Decrement the numUsed of the node

    /* If after you dequeue a number, the node becomes empty, delete the node and rewire the linked list */
    if (head->numUsed == 0){
        nodeT *toBeDeleted = head;          // Note the adress of the node to be deleted
        if (head->next != nullptr){         // If it is not the only node in the queue
            head = head->next;              // Set the following node to be at the head
            head->prev = nullptr;           // Set the new head node's prev pointer to null
        } else if (head->next == nullptr){  // But if its the only node left
            tail = nullptr;                 // Set had and tail to null
            head = nullptr;
        }
        delete toBeDeleted;                 // In any case, delete the current node
    }

    return num;
}
