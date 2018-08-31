#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


/* Reverse string iteratively */
string iterRevString(string s){
    string result ="";
    for (int i=s.length()-1; i>=0; i--){
        result+=s[i];
    }
    return result;
}

/* Reverse string recursively */
string recRevString(string s){
    if (s.length()==0) return s;
    else return s[s.length()-1] + recRevString( s.substr(0, s.length()-1) );
}


int main(){
    cout << iterRevString("abcdefg") << endl;
    cout << recRevString("abcdefg") << endl;

    return 0;
}

