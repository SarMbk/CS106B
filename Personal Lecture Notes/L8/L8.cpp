#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;

// RECURSION


// non recursive raise to power
int raise(int base, int exp){
    int result = 1;
    for (int i=1; i<exp; i++){
        result*=base;
    }
    return result;
}

// recursive raise to power
int recRaise (int base, int exp){
    if(exp == 0){
        return 1;
    } else {
        return base*recRaise(base, exp-1);
    }
}


// recursive raise to power more efficient
int recRaise2(int base, int exp){
    if (exp ==0) {
        return 1;
    }
    else{
        int half = recRaise2(base, exp/2);
        if(exp%2==0){
            return half*half;
        }
        else{
            return base*half*half;
        }
    }
}


bool isPalindrome(string s){
    if (s.length()<=1){
        return true;
    }
    else{
        return ( s[0]==s[s.length()-1] ) && isPalindrome( s.substr(1, s.length()-2) );
    }
}


// Recursive binary search
const int notFound = -1;

int BSearch(Vector<int> &v, int start, int stop, int key){
    if (start>stop){
        return notFound;
    }
    int mid = (start+stop)/2;
    if(key==v[mid]){
        return mid;
    }
    else if(key < mid){
        return BSearch(v, start, mid-1, key);
    }
    else {
        return BSearch(v, mid+1, stop, key );
    }
}



// Recursive n choose k; how many ways there are to pick n people out of a group of k
int C(int given, int choose){
    if (choose ==0 || given==choose){
        return 1;
    }
    else{
        return C(given-1, choose-1)+ C(given-1, choose);
    }
}



int main(){
    

    cout << recRaise(-2,3) << endl;

    cout << recRaise2(2,10) << endl;

    cout << boolToString( isPalindrome("gohangasalamiimalasagnahog") ) << endl;

    cout << C(12,4) << endl;

    return 0;
}

