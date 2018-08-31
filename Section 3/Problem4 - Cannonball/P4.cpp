#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <math.h>
using namespace std;


/* Define cannonball function, takes an int representing the number of levels in a square based
 * neat pyramyd of cannonballs and returns total number of cannonbals in the pyramyd
 * returns -1 when input is negative as to notify the client of error */
int Cannonball(int numLevels){
    if (numLevels < 0) return -1;
    if (numLevels == 0) return 0;
    else return Cannonball(numLevels-1)+ pow(numLevels , 2);
}


int main(){
    /* Lets test the function and see if it works as required */
    cout << Cannonball(5) << endl;
    return 0;
}

