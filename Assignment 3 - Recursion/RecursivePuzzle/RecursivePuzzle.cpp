#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


bool Solvable(int start, Vector<int> & squares){
    if (squares[start] == 0) return true;
    else{
        int nextForward = start + squares[start];
        int nextBackward = start - squares[start];

        if( nextForward<=squares.size()-1   &&    nextBackward>=0  ){
            return (  Solvable(nextForward, squares) || Solvable(nextBackward,squares)  );
        }
        if ( nextForward>squares.size()-1 && nextBackward>=0) {
            return ( Solvable(nextBackward, squares));
        }
        if (nextForward<=squares.size()-1 && nextBackward<0 && squares[start]!=squares[nextForward]){
            return ( Solvable(nextForward, squares));
        }

        if (    squares[start] == squares[nextForward] &&
                nextBackward<0 &&
                nextForward+squares[nextForward]>squares.size()-1){
            return false;
        }

        else return false;
    }

}


int main(){
    Vector<int> puzzle1 {3, 6, 4, 1, 3 ,4, 2, 5, 3, 0};
    Vector<int> puzzle2 {3, 1, 2, 3, 0};
    Vector<int> puzzle3 {1,0};
    Vector<int> puzzle4 {1, 3, 2, 2, 1, 0};

    cout << boolToString( Solvable(0, puzzle1) ) << endl; // true
    cout << boolToString( Solvable(0, puzzle2) ) << endl; // false
    cout << boolToString( Solvable(0, puzzle3) ) << endl; // true
    cout << boolToString( Solvable(0, puzzle4) ) << endl; // true

    return 0;
}

