#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gobjects.h"
using namespace std;


// LETS TRY TO WRITE A RECURSIVE PERMUTATION FUNCION OURSELVES FROM SCRATCH

void recSubsets(string soFar, string rest){
    if(rest==""){
        cout << soFar << endl;
    }
    else {
        //add to subset, remove from rest, recur
        recSubsets(soFar+rest[0], rest.substr(1));

        // dont add to subset, remove from rest recur
        recSubsets(soFar, rest.substr(1));
    }
}

void listSubsets(string str){
    recSubsets("", str);
}



int main(){
    listSubsets("ABCD");
    return 0;

    
}

