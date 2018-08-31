#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"
using namespace std;



int countWays(int numSteps){
    if (numSteps==0) return 1;
    if (numSteps==1) return 1;
    if (numSteps==2) return 2;
    else{
        return countWays(numSteps-1) + countWays(numSteps-2);
    }
}


int main(){

    cout << countWays(4) << endl;

    return 0;
}

