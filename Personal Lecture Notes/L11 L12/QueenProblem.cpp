#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gobjects.h"
using namespace std;


/* Independent Constants used for graphics */
const int       BOARD_SIZE = 12;        // number of columns, rows in the board
const double    MARGIN = 50;
const double    H = 680;                // screen width
const double    W = H;                  // screen depth
const double    X0 = MARGIN;            // starting X coordinate for drawing gridlines on the board
const double    Y0 = H-MARGIN;          // starting Y coordinate for drawing vertical lines
const double    X1 = W-MARGIN;          // ending X coordinate for drawing horizontal lines
const double    Y1 = MARGIN;            // ending Y cooriate for drawing vertical lines
const double    SQUARE_SIZE = (H-2*MARGIN)/BOARD_SIZE;
const double    GAP = 0.1*SQUARE_SIZE;  // Gap between gridline and circle representing a chess
const double    CHESS_SIZE = SQUARE_SIZE-2*GAP;
const double    PAUSE_TIME = 500;
const string    CHESS_COLOR = "PURPLE";


/* Private variable for graphics window */
GWindow gw(W, H);


/* Private variable for grid object of true/false values representing the board */
Grid<bool> board(BOARD_SIZE, BOARD_SIZE);


/* Draw an empty grid nxn representing the chess board */
void drawBoard(){
    // Draw vertical lines
    for (int i = 0; i<=BOARD_SIZE; i++){
        GLine *vline = new GLine(MARGIN+i*SQUARE_SIZE, Y0, MARGIN+i*SQUARE_SIZE, Y1);
        GLine *hline = new GLine(X0,Y0-i*SQUARE_SIZE,X1, Y0-i*SQUARE_SIZE);
        gw.add(vline);
        gw.add(hline);
    }
}


/* Draw a circle inside the square, representing a position of queen given a row and column
 * rows and columns start from 1 not from zero */
void putQueenGraphically(int row, int col){
    GOval *queen = new GOval(CHESS_SIZE, CHESS_SIZE);
    queen->setFillColor(CHESS_COLOR);
    double x = MARGIN+col*SQUARE_SIZE + GAP;
    double y = MARGIN+row*SQUARE_SIZE+GAP;
    gw.add(queen, x, y);
    pause(PAUSE_TIME);
}


/* Remove a circle inside the square of in a given row and column */
void removeQueenGraphically(int row, int col){
    double x = MARGIN+col*SQUARE_SIZE + SQUARE_SIZE/2;
    double y = MARGIN+row*SQUARE_SIZE+SQUARE_SIZE/2;
    GObject *queen = gw.getGObjectAt(x,y);
    gw.remove(queen);
    pause(PAUSE_TIME);
}


/* Initiate board with no chess at the start of each run. Used for readability of code */
void initChessGrid(){
    board.fill(false);
}


/* Place a queen given a row and a column, updates both the graphic display
 * and the internal board grid object */
void putQueen(int row, int col){
    board.set(row,col, true);
    putQueenGraphically(row, col);
}


/* Remove a queen from a spot given a row and a column, updates both the graphic display
 * and the internal board grid object */
void removeQueen(int row, int col){
    board.set(row, col, false);
    removeQueenGraphically(row, col);
}


/* Returns true if there are no queens placed in a given row,
 * otherwise returns false */
bool rowIsClear (int row){
    for (int i=0; i<BOARD_SIZE; i++){
        if (board.get(row, i) == true) return false;
    }
    return true;
}


/* Returns true if there are no queens placed in a column row,
 * otherwise returns false */
bool columnIsClear (int col){
    for (int i=0; i<BOARD_SIZE; i++){
        if (board.get(i, col) == true) return false;
    }
    return true;
}


/* Methods diagIsClear1...4 return true if there are no queens placed
 * diagonally from a position given column and row number; otherwise return false;
 * there are 4 similar methods because for any position there are 4 diagonal directions*/
bool diagIsClear1(int row, int col){
    while (board.inBounds(row, col)){
        if (board.get(row, col) == true) return false;
        row++; col++;
    }
    return true;
}
// See comments above diagIsClear1 function
bool diagIsClear2(int row, int col){
    while (board.inBounds(row, col)){
        if (board.get(row, col) == true) return false;
        row--; col--;
    }
    return true;
}
// See comments above diagIsClear1 function
bool diagIsClear3(int row, int col){
    while (board.inBounds(row, col)){
        if (board.get(row, col) == true) return false;
        row++; col--;
    }
    return true;
}
// See comments above diagIsClear1 function
bool diagIsClear4(int row, int col){
    while (board.inBounds(row, col)){
        if (board.get(row, col) == true) return false;
        row--; col++;
    }
    return true;
}


/* Wrapper function for methods diagIsClear 1...4; used for brevity and readability of code */
bool allDiagsAreClear(int row, int col){
    return diagIsClear1(row, col) && diagIsClear2(row, col)
            && diagIsClear3(row, col) && diagIsClear4(row, col);
}


/* Wrapper function; given row and col, returns true if there are no queens threatening this position
 * from any direction; otherwise returns false */
bool isSafe(int row, int col){
    if (rowIsClear(row) && columnIsClear(col) && allDiagsAreClear(row, col) ) return true;
    else return false;
}


/* Recursive backtracking solve method, placing n queens on an nxn board in a way that no one queen
 * threatens the other */
bool Solve(int col){
    if(col>=board.numCols()) return true;

    for (int tryRow = 0; tryRow < board.numRows(); tryRow++){
        if(isSafe(tryRow, col)){
            putQueen(tryRow, col);
            if (Solve(col+1)) return true;
            removeQueen(tryRow, col);
        }
    }
    return false;
}


int main(){
    drawBoard();
    initChessGrid();
    Solve(0);
    return 0;    
}

