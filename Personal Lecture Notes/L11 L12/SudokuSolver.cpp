#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gobjects.h"
#include "ginteractors.h"
#include "grid.h"
#include "fstream"
using namespace std;


/* Independent Constants */
const int       UNASSIGNED = 0; // Used for checking if a sudoku cell doesn't have an assigned value
const int       SUDOKU_SIZE = 9; // Sudokus are always 9x9
const double    MARGIN = 50; // Top & side margins for graphics display
const double    GAPX = 30; // X direction gap between columns of numbers on the graphics display
const double    GAPY = 30; // Y direction gap between rows of numbers on the graphics display
const double    H = 680; // Graphics window height
const double    PAUSE_TIME = 200; // Used to control speed of animation, smaller = faster
const double    INIT_PAUSE = 100; // Used to control for how long to show a yet unsolved initial sudoku
const string    FONT = "Dialog-13";
const double    FONT_SIZE = 13;


/* Dependent Constants */
const double    W = H; // Graphics window width
const double    Y0_VLINE = MARGIN - GAPY; // starting y coordinate for vertical lines in the sudoku table
const double    Y1_VLINE = MARGIN + SUDOKU_SIZE*GAPY; // ending y coordinate for vertical lines in the sudoku table
const double    X0_HLINE = MARGIN - GAPX; // starting x coordinate for horizontal lines in the sudoku table
const double    X1_HLINE = MARGIN + SUDOKU_SIZE*GAPX; // ending x coordinate for horizontal lines in the sudoku table


/* Graphics window */
GWindow gw(W, H);

/* Input stream object to read from text file */
ifstream infile;

/* Grid object to store all input text fields */
Grid<int> sudokuGrid(SUDOKU_SIZE, SUDOKU_SIZE);


/* Open file method */
ifstream openFile(){
    string fileName = getLine("Enter name of text file to read the sudoku from: ");
    ifstream ifstr;
    while (true){
        ifstr.open(fileName.c_str());
        if(!ifstr.fail()) break;
        cout << "Unable to open file " << fileName << " try another file name: " << endl;
        string fileName = getLine("Enter file name: ");
        ifstr.clear();
    }
    return ifstr;
}


/* Read the text file and populate grid with numbers */
void readNumsIntoGrid(){
    int count = 0;
    while(true){
        int num;
        infile >> num;
        if(infile.fail()) break;
        if( sudokuGrid.inBounds(count/9, count%9) ) {
            sudokuGrid.set(count/9, count%9, num);
        }
        count++;
    }
}


/* Draw lines visually separating the 3x3 blocks */
void drawLines(int &row, int &col){
    if (col==2 && row==0 || col==5 && row==0) {
        double x = MARGIN + GAPX*col + 0.5*GAPX;
        GLine *line = new GLine(x, Y0_VLINE, x, Y1_VLINE);
        gw.add(line);
    }

    if (row==2 && col==0 || row==5 && col==0){
        double y = MARGIN + row * GAPY+ 0.5*(GAPY-FONT_SIZE);
        GLine *line = new GLine(X0_HLINE, y, X1_HLINE, y);
        gw.add(line);
    }
}


/* Display initial (uncompleted) sudoku grid graphically */
void displayStartingSudoku(){
    for (int row=0; row<SUDOKU_SIZE; row++){
        for (int col=0; col<SUDOKU_SIZE; col++){
            drawLines(row, col);
            if(sudokuGrid.get(row,col) != UNASSIGNED){
                double x = MARGIN + GAPX*col;
                double y = MARGIN + GAPY*row;
                string s = integerToString( sudokuGrid.get(row, col) );
                GLabel *label = new GLabel(s);
                label->setFont(FONT);
                gw.add(label,x,y);
            }
        }
    }
    pause(INIT_PAUSE);
}


/* Remove an assigned number from a given row col graphically */
void removeAssignmentGraphically(int &row, int &col){
    double x = MARGIN + GAPX*col;
    double y = MARGIN + GAPY*row;
    GObject *numLabel = gw.getGObjectAt(x,y);
    gw.remove(numLabel);
    pause(PAUSE_TIME);
}


/* Remove assigned number from a position with given row & col
 * takes care of internal and graphical removal */
void removeAssignment(int &row, int &col){
    sudokuGrid.set(row, col, UNASSIGNED);
    removeAssignmentGraphically(row, col);
}


/* Show an assigned number at a particular cell given row and col
 * takes care of graphical aspect only */
void assignGraphically(int &row, int &col){
    removeAssignmentGraphically(row, col);
    double x = MARGIN + GAPX*col;
    double y = MARGIN + GAPY*row;
    string s = integerToString( sudokuGrid.get(row, col) );
    GLabel *label = new GLabel(s);
    label->setFont(FONT);
    gw.add(label,x,y);
    pause(PAUSE_TIME);
}


/* Assign a selected number to a particular cell given row & col
 * takes care of both graphical and internal representation */
void assign(int &row, int &col, int num){
    sudokuGrid.set(row, col, num);
    assignGraphically(row, col);
}


/* Returns true if the number is not repeated in the given row, otherwise returns false */
bool isRowOK(int &row, int &col, int num){
    for (int colSearch=0; colSearch<SUDOKU_SIZE; colSearch++){
        if (sudokuGrid.get(row, colSearch) == num  && col!=colSearch){
            return false;
        }
    }
    return true;
}


/* Returns true if the number is not repeated in the given column, otherwise returns false */
bool isColOK(int &row, int &col, int num){
    for (int rowSearch=0; rowSearch<SUDOKU_SIZE; rowSearch++){
        if (sudokuGrid.get(rowSearch, col) == num  && row!=rowSearch){
            return false;
        }
    }
    return true;
}


/* Returns true if the number is not repeated in the 3x3 sudoku subblock, otherwise returns false */
bool isBlockOK(int &row, int &col, int num){
    int boxStartRow = row - row%3;
    int boxStartCol = col - col%3;
    for(int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if( sudokuGrid.get(i+boxStartRow, j+boxStartCol)==num){
                return false;
            }
        }
    }
    return true;
}


/* Returns true if a given number is ok to place in cell of given row and column according to
 * sudoku rules. Otherwise return false */
bool isAssignmentOK(int &row, int &col, int num){
    if ( isRowOK(row, col, num) && isColOK(row, col, num) && isBlockOK(row, col, num) ) {
        return true;
    }
    return false;
}


/* Returns true if there are no empty cells in the sudoku grid, otherwise returns false */
bool isAllAssigned( int &row, int &col){
    for ( row=0; row<SUDOKU_SIZE; row++){
        for (col=0; col<SUDOKU_SIZE; col++){
            if( sudokuGrid.get(row,col) == UNASSIGNED ) return false;
        }
    }
    return true;
}


/* Recursive backtracking sudoku solving algorithm */
bool solveSudoku(){
    int row, col;
    /* if no more zeros left - success; This will also set row & col variables to an unassigned location */
    if (isAllAssigned(row, col)) return true;

    /* Once the method above sets col and row to unassigned location, try numbers 1 to 9 */
    for (int num = 1; num <= 9; num++) {
        if(isAssignmentOK(row,col,num)){    // if a number works, assign it
            assign(row, col, num);
            if(solveSudoku()) return true;  // from there move on and if you can solve the rest - return true and youre done
            removeAssignment(row, col);     // if you cant solve the rest from there, remove the previous assignment
        }
    }
    return false;
}

/* Wraps everithing into one neat function */
void runGame(){
    while (true){

        infile = openFile();
        gw.clearCanvas();
        readNumsIntoGrid();
        displayStartingSudoku();

        if(solveSudoku() == false){
            cout << "NOT SOLVABLE!!!"<< endl;
        } else{
            cout << "SOLVED!" << endl;
        }
    }
}


int main(){
    runGame();
    return 0;
}





