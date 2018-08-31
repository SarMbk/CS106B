#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;




int sumVector(Vector<int> &v){
    int sum = 0;
    for (int i=0; i<v.size(); i++){
        sum+=v[i];
    }
    return sum;
}


int cutStock( Vector<int> & requests, int stockLength){
    int units = 0;   
    if (sumVector(requests) = stockLength ) units+=1;
    else{
        // Pick and choose and then find max
    }
}


int main(){

    Vector<int> requests {4,3,4,1,7,8};

    cout << cutStock(requests, 10);

    return 0;
}

