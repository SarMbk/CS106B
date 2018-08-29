#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "myvector.h"
#include "mystack.h"
#include "mob.h"
using namespace std;

template<typename ElemType>
void reverseAsClient(mystack<ElemType> &stk){
    mystack <ElemType> result;
    while(!stk.isEmpty()){
        result.push(stk.pop());
    }
    stk = result;
}


int main() {
    myvector<string> vec;
    vec.add("a");
    vec.add("b");
    vec.add("c");
    vec.print();

    myvector<int> v;
    v.add(10);
    v.add(20);
    v.add(30);
    v.insertAt(0, 100);
    v.print();

    /* Assignment operator works by default. This is really bad. Object of class myvector
     * has a pointer *arr pointing at a start of array. when you say v=w you make two pointers
     * point to the same place. But when you double capacity of v, it creates a new vector,
     * copies all the contents and changes the pointer inside of v, so pointer of w gets orphaned.
     * you have to diasallow such initialization. Work out how to disallow copy using std libraries.
     * you can disallow copying by defining a = operator and defining it to make a deep copy */
    myvector<int> w; w=v;
    w.print();


    mystack<string> stk;
    stk.push("a"); stk.push("b"); stk.push("c"); stk.push("d"); stk.push("e");
    stk.reverse();
    cout << stk.print() << endl;
    reverseAsClient(stk);
    cout << stk.print() << endl;


    mob<string> m;
    m.enqueue("a"); m.enqueue("b"); m.enqueue("c"); m.enqueue("d"); m.enqueue("e"); m.enqueue("f");
    m.enqueue("g"); m.enqueue("h"); m.enqueue("i"); m.enqueue("j"); m.enqueue("k"); m.enqueue("l");
    m.printAll();

    return 0;
}
