#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "stack.h"
#include "queue.h"
using namespace std;



int main(){

    /* String reversal, use of stack*/
    cout << "Enter a string: ";
    string s = getLine();

    Stack <char> charStack;

    for(int i=0; i<s.length(); i++){
        charStack.push(s[i]);
    }

    cout << "That backwards is: ";
    while(!charStack.isEmpty()){
        cout << charStack.pop();
    }



    cout << endl << endl << endl;



    /* Use of queues */
    Queue<string> q;
    while (true){
        string response = getLine("Please enter response: ");
        if (response == "") break;
        if (response == "next"){
            if(q.isEmpty()){
                cout << "Nobody else in the queue" << endl;
            }
            else{
                cout << q.dequeue() << " is next" << endl;
            }
        }
        else{
            q.enqueue(response);
            cout << response << " was added to the queue" << endl;
        }
    }

    return 0;
}

