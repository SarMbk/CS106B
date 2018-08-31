#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;

// Structures and methods for linked list
struct Entry{
    string name, phone;
    Entry *next;
};

void printEntry (Entry *e){
    cout << e->name << " " << e->phone << endl;
}

Entry *getNewEntry(){
    cout << " Enter name: (Enter to quit): ";
    string name = getLine();
    if (name =="") return NULL;

    Entry *newOne = new Entry;
    newOne->name = name;
    cout << "Enter phone: ";
    newOne->phone = getLine();
    newOne->next = NULL;
    return newOne;
}

Entry *buildList(){
    Entry *list = NULL;
    while (true){
        Entry *newOne = getNewEntry();
        if (newOne == NULL) break;
        newOne->next = list;
        list = newOne;
    }
    return list;
}



/* Simple pointer operations */
int main(){
    int num;
    int *p, *q; // initialize pointers they are created in the stack; all local variables live in the stack
                // they hold adress of the number somewhere else

    p = new int; // allocates space in the heap for an int and assigns its address to the pointer p
    // you have to initiate a pointer, you cant say *p=42; you have to allocate space first
    *p = 10;     // when you use star next to pointer, you are "dereferencing a pointer"
                 // This command says follow address that is stored in the pointer (i.e. go to the space in the heap)
                 // and assign value 10 to that place in the heap
    cout << p << endl;
    cout << *p << endl;


    q = new int; // allocate space in a heap for pointer q
    // for anything if you use new command, it creates that object on the heap
    *q = 11;
    cout << q << endl;
    cout << *q << endl;

    *q=*p; // dereference p (meaning get int 10) and go to adress of q and put 10 in the space for q
           // now the original address stored in q is strangled in the heap and no way to get back to it.
           // its called orphan piece of memory or orphan address, now you cant use this memory for something else
           // and you cant access it to delete it
    cout << q << endl;
    cout << *q << endl;
    cout << p << endl;
    cout << *p << endl;

    q=p; // means take the address thats in p and assign to q, now both pointers q & p point to the same place in the heap
    cout << q << endl;

    delete p; // take the address of p and delete whatever is stored in that location. cant use the pointer p anymore
              // that space has been freed up.
   // delete q; // you technically dont need this because q & p point to the same location so the command above alone is enough

    q=NULL; // since we deleted p, we need to assign null to q so we knew it's an empty pointer


    //=====POINTERS AND ARRAYS =======//
    int *arr = new int[10]; // pointer arr initialized to point to an array of ints in the heap
    for (int i=0; i<10; i++){
        arr[i]=i;
    }
    delete[] arr;

    //=====LINKED LIST======//

    Entry *n = buildList();
    printEntry(n);


    string s = "saruar";
    cout << s.substr(1) << endl;


    return 0;
}

