#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "stack.h"
#include "queue.h"
using namespace std;


/* FUNCTION PROTOTYPES */
void reverseQueue(Queue<string> &q);


/* MAIN METHOD */
int main(){

    // Get user to enter a series of strings to enter into a queue
    Queue<string> q;
    string s = "dummy initiation";
    while (true){
        s=getLine("Enter a string to place in the queue: ");
        if (s=="") break;
        q.enqueue(s);
    }

    cout << q.toString() << endl;
    reverseQueue(q);
    cout << q.toString() << endl;

    return 0;
}


void reverseQueue(Queue<string> &q){
    Stack<string> stck;
    while(!q.isEmpty()){
        stck.push(q.dequeue());
    }
    while(!stck.isEmpty()){
        q.enqueue(stck.pop());
    }
}







