#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include <cmath>
#include "time.h"
using namespace std;


/* Making a templatized solution */
template <typename Type>
int OperatorCmp(Type one, Type two){
    if (one == two) return 0;
    return (one < two ? -1 : 1);
}


/* You may use the same sorting algorithm and just change the comparison function to sort the
 * vecctor in the reverse order */
template <typename Type>
int ReverseCmp(Type one, Type two){
    if (one > two) return -1;
    else if (one < two) return 1;
    return 0;
}


/* Defining a templatized method with a default callback function */
template <typename Type>
void selectionSort(Vector<Type> & vec, int (cmp)(Type one, Type two) = OperatorCmp){
    int n = vec.size();
    for (int i=0; i<n-1; i++){
        int minIndex=i;
        for (int j=i+1; j<n; j++){
            if ( cmp(vec[minIndex], vec[j]) < 0 ) minIndex=j;
        }
        swap(vec[minIndex], vec[i]);
    }
}


int main() {

    Vector<int> vec {5, 4, 3, 2, 1, 8, 10, 9, 11, 23};
    selectionSort(vec);
    cout << vec.toString()<<endl;

    time t(9, 25);
    time t1(9, 39);

    cout << t.isLessThan(t1) << endl;
    cout << t.toString() << endl;


    return 0;
}
