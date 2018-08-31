#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"
#include "strlib.h"
#include <string>
using namespace std;


// Define a structure entryT that has a person's name and phone number
struct entryT {
    string firstName, lastName; // objects inside a struct are called members of a struct
    string phoneNum;
};


/* Define a function that will tell the computer how to compare the
 * <code> studentT </code> data structures, i.e. provide a callback function
 * it will return 0 if elements are same, 1 if elements are not same and
 * it needs some sort of sorting so it will return -1 if a.phonenum < b.phonenum
 * so it will internally sort entries by ascending order of phone numbers */
int compareEntries(entryT a, entryT b){
    if (a.lastName < b.lastName) return -1;
    else if (a.lastName > b.lastName) return 1;
    else if (a.firstName < b.firstName) return -1;
    else if (a.firstName > b.firstName) return 1;
    if (a.firstName ==b.firstName && a.lastName == b.lastName && a.phoneNum==b.phoneNum) return 0;
    else return 1;
}


int compareCaseInsensitive(string s1, string s2){
    if (toUpperCase(s1)==toUpperCase(s2)) return 0;
    if (toUpperCase(s1)<toUpperCase(s2)) return -1;
    else return 1;
}


int main(){
    // Now when you initiate a set, pass the function as a parameter
    // This is called "supplying a callback function"
    Set<entryT> phonebook(compareEntries);

    entryT a;
    a.firstName = "Saruar";
    a.lastName = "Manarbek";
    a.phoneNum = "6173083573";

    entryT b;
    b.firstName = "Mama";
    b.phoneNum = "7245118";

    entryT c;
    c.firstName = "Anton";
    c.lastName = "Chekhov";
    c.phoneNum = "111111";

    entryT d;
    d.firstName = "Anton";
    d.lastName = "Chekhov";
    d.phoneNum = "111112";

    entryT e;
    e.firstName = "Saruar";
    e.lastName = "Mubarak";
    e.phoneNum = "6173083573";

    phonebook.add(a);
    phonebook.add(b);
    phonebook.add(c);
    phonebook.add(d);
    phonebook.add(e);

    /* When you are iterating over a collection of structs (in this case a set).
     * To access a member of a struct inside the iterator loop you do this:
     * (*it).firstName */
    Set<entryT>::iterator it;
    for (it = phonebook.begin(); it != phonebook.end(); it++) {
      cout << (*it).firstName << " " << (*it).lastName << ": " << (*it).phoneNum << endl;
    }


    // Part B
    string s1 = "Abc";
    string s2 = "aBc";
    string s3 = "deF";
    string s4 = "dEf";
    string s5 = "ghi";

    Set<string> myset(compareCaseInsensitive);
    myset.add(s1);
    myset.add(s2);
    myset.add(s3);
    myset.add(s4);
    myset.add(s5);


    cout << " " << endl;
    Set<string>::iterator itr;
    for (itr = myset.begin(); itr!=myset.end(); itr++){
        cout << *itr << endl;
    }

    return 0;
}




