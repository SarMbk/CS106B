#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <map>
#include "error.h"
using namespace std;


string digitToLetters(char digit){
    string result;
    switch (digit) {
    case '0':
        result = "0"; break;
    case '1':
        result = "1"; break;
    case '2':
        result = "ABC"; break;
    case '3':
        result = "DEF"; break;
    case '4':
        result = "GHI"; break;
    case '5':
        result =  "JKL"; break;
    case '6':
        result =  "MNO"; break;
    case '7':
        result =  "PRS"; break;
    case '8':
        result = "TUV"; break;
    case '9':
        result = "WXY"; break;
    default:
        error("Illegal digit");
    }
    return result;
}


void RecBuildPossibleLetters(string lettersSoFar, string remDigits){

    if (remDigits==""){
        cout << lettersSoFar << endl;
    }

    else{
        string nextLetters = digitToLetters(remDigits[0]);
        for (int i=0; i<nextLetters.length(); i++){
            RecBuildPossibleLetters(lettersSoFar+nextLetters[i], remDigits.substr(1));
        }
    }
}


void ListMneumonics(string digits){
    RecBuildPossibleLetters("", digits);
}


int main(){
    ListMneumonics("01237");
    return 0;
}

