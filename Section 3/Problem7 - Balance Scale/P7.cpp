#include <iostream>
#include <algorithm>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


bool RecIsMeasurable(int target, Vector<int> &weights, int index){
    if(target==0) return true;
    if(index >= weights.size()) return false;
    else {
        return (
                RecIsMeasurable(target+weights[index], weights, index +1) ||
                RecIsMeasurable(target, weights, index+1) ||
                RecIsMeasurable(target-weights[index], weights, index+1)
               );
    }
}

// Wrapper function
bool IsMeasurable(int target, Vector<int> &weights){
    return RecIsMeasurable(target, weights, 0);
}


bool RecIsMeasurable2(int target, Vector<int> &weights, int index){

    if(target==0) return true;
    if(target==weights[index]) return true;

    // If target equals sum of all weights
    int sumAll = 0;
    for (int i=index; i<weights.size(); i++){
        sumAll+=weights[i];
    }
    if (target==sumAll) return true;
    if (target>sumAll) return false;


    if (index>=weights.size()) return false;


    else{
        return (
                    RecIsMeasurable2(target+weights[index], weights, index+1) ||
                    RecIsMeasurable2(target, weights, index+1) ||
                    RecIsMeasurable2(target-weights[index], weights, index+1)
               );
    }
}


bool IsMeasurable2(int target, Vector<int> &weights){
    return RecIsMeasurable2(target, weights, 0);
}





int main(){

    Vector<int> sampleWeights;
    sampleWeights.add(1);
    sampleWeights.add(3);
    sampleWeights.add(5);

    cout << boolToString( IsMeasurable(2, sampleWeights) ) << endl;
    cout << boolToString( IsMeasurable2(2, sampleWeights)) << endl;



    return 0;
}

