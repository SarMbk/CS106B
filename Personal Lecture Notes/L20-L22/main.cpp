#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "mystack.h"
#include "myqueue.h"
#include "buffer.h"
#include "random.h"
#include "linkbuffer.h"
#include "vecmap.h"
#include "treemap.h"
using namespace std;



int main() {

    /* Class mystack is a stack implementation using linked list */
    mystack<int> s;
    s.push(1); s.push(2); s.push(3); s.push(4); s.push(5); s.push(6); s.push(7);
    while(!s.isEmpty()){
        cout << s.pop() << " ";
    }
    cout << endl;


    /* Class myqueue is a queue implementation using a linked list */
    myqueue<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3); q.enqueue(4); q.enqueue(5); q.enqueue(6); q.enqueue(7);
    while (!q.isEmpty()){
        cout << q.dequeue() << " ";
    }
    cout << endl;


    /* Testing out the vector based buffer */
    buffer b;
    char achar = 'A';
    char zchar = 'Z';
    for (int i=0; i<10; i++){
        char letter = (char)randomInteger(achar, zchar);
        b.insertCharacter(letter);
    }
    b.insertCharacter(' ');
    for (int i=0; i<10; i++){
        char letter = (char)randomInteger(achar, zchar);
        b.insertCharacter(letter);
    }

    for (int i=0; i<5; i++){
        b.moveCursorBackward();
    }
    b.moveToWordBegin(); // testing out assignment 8
    b.display();


    /* Testing the linked list based buffer */
    linkbuffer lb;
    for (int i=0; i<10; i++){
        char letter = (char)randomInteger(achar, zchar);
        lb.insertCharacter(letter);
    }
    lb.insertCharacter(' ');
    for (int i=0; i<10; i++){
        char letter = (char)randomInteger(achar, zchar);
        lb.insertCharacter(letter);
    }

    for (int i=0; i<5; i++){
        lb.moveCursorBackward();
    }

    lb.moveToWordBegin();
    lb.display();

    //lb.moveCursorToStart();
    //lb.insertCharacter('1');
    //lb.moveCursorToEnd();
    //lb.insertCharacter('9');


    /* Testing the vector implementation of map */
    vecmap<int> vm;
    vm.add("one", 1);
    vm.add("two", 2);
    vm.add("three", 3);
    vm.add("four", 4);
    vm.add("five", 5);
    vm.add("six", 6);
    vm.add("seven", 7);
    vm.add("eight", 8);
    vm.add("nine", 9);
    vm.printAll();
    cout << vm.getValue("six") <<endl << endl;



    /* Testing the tree implementation of treemap */
    treeMap<string> tm;
    tm.add(1, "one");
    tm.add(2,"two");
    tm.add(3, "three");
    tm.add(4, "four");
    tm.add(5, "five");
    tm.add(6, "six");
    tm.add(7, "seven");
    tm.add(8, "eight");
    tm.add(9, "nine");
    tm.add(0, "zero");
    tm.add(-100, "negative one hundred");
    tm.printAll();
    cout << tm.getValue(0) <<endl;


    return 0;
}
