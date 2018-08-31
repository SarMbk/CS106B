#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;



string toBinary(int num){
    if (num==0) return "0";
    if (num == 1) return "1";
    else{
        return toBinary(num/2) + integerToString(num%2);
    }
}

int main(){
    cout << toBinary(15)<< endl;
    return 0;    
}

