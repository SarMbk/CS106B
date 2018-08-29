#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include "rectangle.h"
#include "car.h"
#include "queue.h"
using namespace std;


struct Node{
    int value;
    Node* next;
};


void PrintList(Node *list){
    for (Node *cur = list; cur!=NULL; cur=cur->next){
        cout << cur->value << "  ";
    }
    cout << endl;
}


void Stutter(Node *list){
    for (Node *cur = list; cur!=NULL; cur=cur->next){
        Node *newOne = new Node;
        newOne->value = cur->value;
        newOne->next = cur->next;
        cur->next = newOne;
        cur = newOne;
    }
}


void Unstutter(Node *list){
    for (Node *cur = list; cur!=NULL; cur=cur->next){
        if (cur->next != NULL  && cur->value == cur->next->value){
            Node* duplicate = cur->next;
            cur->next = cur->next->next;
            delete duplicate;
        }
    }
}


Node *GetNewEntry(){ //This sintax means the method will return a pointer to an EntryT structure
    cout << "Enter and int (or enter blank to quit): ";
    string val = getLine();
    if (val=="") return NULL;

    Node *newOne = new Node; // allocate space in the heap for a pointer to an Entry
    newOne->value = stringToInteger(val);
    newOne->next = NULL;
    return newOne;
}


Node *BuildList(){
    Node *list = NULL;
    while (true){
        Node *newOne = GetNewEntry();
        if (newOne==NULL) break;
        newOne->next = list;
        list = newOne;
    }
    return list;
}


int main() {
    // Problems 1 & 2 are in the lecture 18 notes; Problems 3 & 4 are discussion */

    Node *n = BuildList();
    PrintList(n);

    Stutter(n);
    PrintList(n);
    Unstutter(n);
    PrintList(n);

    return 0;
}
