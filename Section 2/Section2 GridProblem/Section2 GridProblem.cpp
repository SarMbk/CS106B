#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "grid.h"
using namespace std;


//CONSTANTS
const bool F = false;
const bool T = true;


//PROTOTYPES
Grid<int> MakeGridOfCounts(Grid<bool> &mines);
void countMines(int row, int col, Grid<bool> &mines, Grid<int> &countGrid);


//MAIN METHOD
int main(){
    Grid<bool> mines {  {T, F, F, F, F, T},
                        {F, F, F, F, F, T},
                        {T, T, F, T, F, T},
                        {T, F, F, F, F, F},
                        {F, F, T, F, F, F},
                        {F, F, F, F, F, F}
                     };

    cout << mines.toString2D() << endl;
    cout << MakeGridOfCounts(mines).toString2D() << endl;
    return 0;
}


//PRIVATE FUNCTIONS

Grid<int> MakeGridOfCounts(Grid<bool> &mines){
    Grid<int> countGrid(mines.numRows(), mines.numCols());
    for (int row = 0; row<mines.numRows(); row++){
        for(int col = 0; col<mines.numCols(); col++){
            countMines(row,col, mines, countGrid);
        }
    }
    return countGrid;
}


// Counts the number of mines in the neighborhood of row, column and sets the number in the count grid
void countMines(int row, int col, Grid<bool> &mines, Grid<int> &countGrid){
    int sum = 0;

    for (int i = -1; i<=1; i++){
        for (int j = -1; j<=1; j++){
            if(mines.inBounds(row+i,col+j)){
                sum+=mines.get(row+i,col+j);
            }
        }
    }
    countGrid.set(row, col, sum);
}



