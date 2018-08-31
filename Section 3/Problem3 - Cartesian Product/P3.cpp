#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"
using namespace std;



/* Define a structure for pairs */
struct pairT {
    string first, second;
};


/* Define a structure to compare pairs */
int comparePairs(pairT a, pairT b){
    if(a.first==b.first  && a.second == b.second) return 0;
    if(a.first < b.first) return -1;
    else return 1;
}


/* Define a function to compute cartesian pairs,
 * input: two sets of strings
 * output: one set of objects of type pairT representing cartesian pairs */
Set<pairT> CartesianProduct(Set<string> &setOne, Set<string> &setTwo){
    Set<pairT> result(comparePairs); // define a set of pair and provide callback function
    for (Set<string>::iterator itFirst = setOne.begin(); itFirst != setOne.end(); itFirst++) {
        pairT entry;
        entry.first = *itFirst;
        for(Set<string>::iterator itSecond = setTwo.begin(); itSecond != setTwo.end(); itSecond++ ){
            entry.second = *itSecond;
            result.add(entry);
        }
    }
    return result;
}


int main(){
    // Lets initiate two sets, test our function, print the cartesian product and see if it works right
    Set<string> ab {"A" , "B"};
    Set<string> xy {"X" , "Y"};
    Set<pairT> abxy(comparePairs);
    abxy = CartesianProduct(ab,xy);
    for(Set<pairT>::iterator it = abxy.begin(); it!= abxy.end(); it++){
        cout << (*it).first << " - " << (*it).second << endl;
    }
    return 0;
}

