#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


/* Function which returns the greatest common denominator of two ints */
int GCD(int x, int y){
    int larger, smaller;
    // First assign larger smaller so the function returned the same result
    // regardless of the order in which arguments are entered
    if (x>y){larger = x; smaller = y;}
    if (x<y){larger = y; smaller =x;}
    if (x==y) return y;

    // Now solve recursively
    if (larger % smaller==0) return smaller;
    else return GCD(smaller, larger%smaller);
}


int main(){
    cout << GCD(45, 36)<< endl;
    return 0;
}

