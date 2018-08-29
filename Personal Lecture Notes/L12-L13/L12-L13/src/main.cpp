#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include "fstream"
using namespace std;


struct Entry
{
    string name, phone;
    Entry *next;
};


void PrintEntry(Entry *e){
    cout << e->name << ": " << e->phone << endl;
}


Entry *GetNewEntry(){ //This sintax means the method will return a pointer to an EntryT structure
    cout << "Enter Name (or enter blank to quit): ";
    string name = getLine();
    if (name == "") return NULL;

    Entry *newOne = new Entry; // allocate space in the heap for a pointer to an Entry
    newOne->name = name;
    cout << "Enter phone: ";
    newOne->phone = getLine();
    newOne->next = NULL;

    return newOne;
}


Entry *BuildList(){
    Entry *list = NULL;
    while (true){
        Entry *newOne = GetNewEntry();
        if (newOne==NULL) break;
        newOne->next = list;
        list = newOne;
    }
    return list;
}


void PrintList(Entry *list){
    for (Entry *cur = list; cur!=NULL; cur=cur->next){
        PrintEntry(cur);
    }
}


void RecPrintList(Entry *list){
    if (list!=NULL){
        PrintEntry(list);
        RecPrintList(list->next);
    }
}


void RecPrintList2(Entry *list){
    if (list!=NULL){
        RecPrintList2(list->next);
        PrintEntry(list);
    }
}


int Count (Entry *list){
    if (list == NULL) return 0;
    return 1+Count (list->next);
}


void Deallocate(Entry *list){
    if (list != NULL){
        Deallocate(list->next);
        delete list;
    }
}


void Prepend(Entry *ent, Entry *&first){
    ent->next = first;
    first = ent;
}


Entry *BuildBook(){
    Entry *listHead = NULL;
    while (true){
        Entry *newOne = GetNewEntry();
        if (newOne == NULL) break;
        Prepend(newOne, listHead);
    }
    return listHead;
}

void InsertSorted(Entry *&list, Entry *newOne){
    Entry *cur;
    Entry *prev = NULL;
    for (cur=list; cur!=NULL; cur=cur->next){
        if (newOne->name < cur->name) break;
        prev = cur;
    }

    newOne->next=cur;
    if (prev!=NULL){
        prev->next = newOne;
    } else{
        list = newOne;
    }
}

void RecInsertSorted(Entry *&list, Entry *newOne){
    if (list == NULL || newOne->name < list->name){
        newOne->next = list;
        list = newOne;
    } else {
        RecInsertSorted(list->next, newOne);
    }
}

int main() {
    /*
    Entry *n = BuildList();
    PrintList(n);
    RecPrintList2(n);
    cout << Count(n) <<endl;
    return 0;
    */

    Entry *n = BuildBook();
    RecPrintList2(n);
    return 0;
}
