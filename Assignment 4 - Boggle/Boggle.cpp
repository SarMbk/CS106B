#include "Boggle.h"
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "bogglegui.h"
#include "grid.h"
#include "set.h"
#include "stack.h"
using namespace std;



/* =============== STUCTURES =============== */

/* pointT structure is used to record the row and column coordinates of used letters in the humanWordSearch function */
struct pointT{
    int row, col;
};



/* =============== CONSTANTS =============== */

const int SIZE = 4;             // size of board
const int MIN_WORD_LEN = 4;     // minimum acceptable length of word
const int WORD_SCORE_ADJUSTER = 3; // for a word of 4 letters you get 4-3 = 1 point; for 5 letters: two points etc.



/* =============== INSTANCE VARIABLES ============== */

/* This stack is used to assist with the humanWordSearch algorithm and wordIsBuildable algorithm,
 * when the recursive algorithm determining the possibility of constructing a word is performed, the row/column
 * locations are recorded as pointT objects inside the usedCubeStack. When the algorithm backtracks, the pointT objects
 * are popped from the stack, when the algorithm checks if the next letter is suitable
 * (i.e. adjacent to the previously used letter) the algorithm peeks into the stack and compares
 * the coordinates of the next letter with the topmost pointT in the stack.
 * When the new word is being built, the stack is cleared */
Stack<pointT> usedCubeStack;


/* This is a grid of boolean values, if usedCubeGrid(i,j)==false this means the cube positioned at i,j is not
 * used in a particular word, this grid helps check buildability if words. When a new word is being built,
 * all grid values are set to false */
Grid<bool> usedCubeGrid(SIZE, SIZE);


/* This grid is used to store all letters (manually or randomly generated), the recursive humanWordSearch and
 * isWordBuildable algorithms search through this grid when determining constructability of words */
Grid<char> boggleGrid (SIZE,SIZE);


/* Set object to keep track internally of found words by human */
Set<string> foundWordsHuman;


/* This set is for all the words found by the computer, but which are not buildable on the board */
Set<string> foundWordsComputer;


/*This set is a result of iterating through the foundWordsComputer set and picking inly the words that are buildable
 * I tried not introducing it and removing entries from the original set but somehow i was getting bugs */
Set<string> foundWordsComputerBuildable;


/* Pointer to the lexicon used to check if words exist */
Lexicon *lex;


/* letters on all 6 sides of every cube */
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


/* letters on every cube in 5x5 "Big Boggle" version (extension) */
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};



/* =============== GAME BOARD SETUP FUNCTIONS =============== */



/* Boggle starting function */
Boggle::Boggle(Lexicon& dictionary, string boardText) {
    //Set the lexicon pointer to an initialized dictionary
    lex = &dictionary;

    // Generate manual or random board
    if (boardText != ""){
        generateManualBoard(boardText);
    }
    else {
        generateRandomBoard();
    }

    // Reset all private variables that still contain data from previous games
    foundWordsHuman.clear();
    foundWordsComputer.clear();
    foundWordsComputerBuildable.clear();
    usedCubeGrid.fill(false);
    usedCubeStack.clear();
}



/* Function to generate the board through manual input */
void Boggle::generateManualBoard(string boardText){
    boardText = toUpperCase(boardText);

    // Ensure user enters exactly a string of 16 characters
    while (boardText.length()!=16){
        boardText = getLine("Please enter a string of 16 characters to generate a board from");
    }

    // Read all letters into the grid object & represent graphically
    for (string::size_type i = 0; i<boardText.size(); i++){
        boggleGrid.set(i/SIZE, i%SIZE, boardText[i]);
    }
    BoggleGUI::labelAllCubes(boardText);
}



/* Function to generate the board randomly */
void Boggle::generateRandomBoard(){
    Set<int> usedRandCubes;
    for (int i=0; i<16; i++){
        int randCubeNum = randomInteger(0,15);
        while(usedRandCubes.contains(randCubeNum)){
            randCubeNum = randomInteger(0,15);
        }
        usedRandCubes.add(randCubeNum);
        string cubeLetters = CUBES[randCubeNum];
        char randLetter = cubeLetters[randomInteger(0,5)];
        boggleGrid.set(i/SIZE, i%SIZE, randLetter);
        BoggleGUI::labelCube(i/SIZE, i%SIZE, randLetter, false);
    }
}



/*=============== HUMAN GAMEPLAY FUNCTIONS ===============*/



/* Function controlling human gameplay */
void Boggle::letHumanPlay(){
    bool humansTurn = true;
    while (humansTurn){

        // Breaks out of the loop if player enters blank line
        string word = getLine("Enter a word (hit enter if you cant find any more words): ");
        word = toUpperCase(word);
        if (word == "") humansTurn = false;

        // Checks validity of inputted word
        if (checkWord(word)){
            usedCubeStack.clear(); // clear the usedLetters instance stack before starting a new word
            usedCubeGrid.fill(false); // clear the used cube set before starting a new word
            BoggleGUI::clearHighlighting();
            if(humanWordSearch(word)){ //recursively check if word can be built per game rules
                foundWordsHuman.add(word); // add word to the set of words guessed by human
                BoggleGUI::recordWord(word, BoggleGUI::HUMAN); // record word graphically
                int humanScore = getScoreHuman();
                BoggleGUI::setScore(humanScore, BoggleGUI::HUMAN); // record score graphically
                BoggleGUI::setStatusMessage("You found a new word! " + word);
            }
        }
    }
}



/* Returns an int representing human player's score */
int Boggle::getScoreHuman() {
    int humanScore = 0;
    for (Set<string>::iterator it = foundWordsHuman.begin(); it != foundWordsHuman.end(); ++it) {
        humanScore+=(*it).length()-WORD_SCORE_ADJUSTER;
    }
    return humanScore;
}



/* Recursively checks if an entered valid word can be built up from available letters on the board
 * Recursive backtracking algorithm. Same as isWordBuildable but with animation effects */
bool Boggle::humanWordSearch(string word){
    word = toUpperCase(word); // ensure case insensitivity
    if(word.empty()) return true; // base case, if no more letters left  - success
    for (int i=0; i<16; i++){
        if(boggleGrid.get(i/SIZE, i%SIZE)==word[0]){ // search for the first letter in the grid
            if (isPositionOK(i/SIZE, i%SIZE)){ // check if position is suitable
                pickPosition(i/SIZE, i%SIZE); // if position is suitable, optimistically pick the position and recur
                if(humanWordSearch(word.substr(1))) return true; // continue and if you finish - success
                unPickPosition(i/SIZE, i%SIZE); // otherwise make a step back and try another option
            }
        }
    }
    return false; // if nothing above worked, return false
}



/* Support function for humanWordSearch
 * If position is suitable create a pointT object with the row and col coordinates of the letter and place it in the stack
 * to use for checking whether the position of the next letter is allowable.
 * Simultaneously takes care of animation delays and graphically highlighting the letters */
void Boggle::pickPosition(int row, int col){
    pointT usedPoint;
    usedPoint.col = col;
    usedPoint.row = row;
    usedCubeStack.push(usedPoint);
    usedCubeGrid.set(row, col, true);
    BoggleGUI::setHighlighted(row,col, true);
    BoggleGUI::setAnimationDelay(BoggleGUI::standardDelay());
}



/* Support function for humanWordSearch
 * When the humanWordSearch algorithm backtracks, this function pops the pointT object representing the used letter
 * row and column coordinates from the stack. Simultaneously it takes care of graphically unhighlighting unpicked points*/
void Boggle::unPickPosition(int row, int col){
    usedCubeStack.pop();
    usedCubeGrid.set(row, col, false);
    BoggleGUI::setHighlighted(row,col, false);
    BoggleGUI::setAnimationDelay(BoggleGUI::standardDelay());
}



/*=============== COMPUTER GAMEPLAY FUNCTIONS ===============*/



/* Function controlling computer gameplay */
void Boggle::letComputerPlay(){
    cout << "It's my turn!"<<endl;
    BoggleGUI::clearHighlighting();
    computerWordSearch();

    // Check if the words found by computer can be built per boggle game rules
    for (Set<string>::iterator it = foundWordsComputer.begin(); it != foundWordsComputer.end(); ++it) {
        usedCubeGrid.fill(false);
        usedCubeStack.clear();
        if (IsWordBuildable(*it)){
            foundWordsComputerBuildable.add(*it);
        }
    }

    // Print words found by computer and display computer's score
    int computerScore = getScoreComputer();
    BoggleGUI::setScore(computerScore, BoggleGUI::COMPUTER);
    cout << "My words: " << foundWordsComputerBuildable.toString() << endl;
}



/* Recursive method that permutes through all the letters and finds all words
 * Although I meant it to only give buildable words, it somehow gives non-buildable words too
 * Hence we need to pick out only buildable words from the set by using isWordBuildable method */
void Boggle::findAllWordsComputer(int row, int col, string soFar){
    string letter =charToString( boggleGrid.get(row, col) );
    string current = soFar + letter;

    if (!lex->containsPrefix(soFar)){
        return;
    }

    if (checkWord(current)){
        foundWordsComputer.add(current);
        return;
    }

    for (int i=0; i<SIZE*SIZE; i++){
        if (isPositionOK(i/SIZE, i%SIZE)){
            pickPositionComputer(i/SIZE, i%SIZE);
            findAllWordsComputer(i/SIZE, i%SIZE, current);
            unPickPositionComputer(i/SIZE, i%SIZE);
        }
    }
}



/* Wrapper function for the findAllWordsComputer method */
void Boggle::computerWordSearch(){
    string soFar;
    usedCubeStack.clear(); // clear the usedLetters instance stack before starting a new word
    usedCubeGrid.fill(false); // clear the used cube set before starting a new word
    for (int i=0; i<16; i++){
        findAllWordsComputer(i/SIZE, i%SIZE, soFar);
    }
}


/* Recursive method that takes in a string and returns a bool representing whether a word can be build
 * with a given grid of cubes. Same as the humanWordSearch function but without animations */
bool Boggle::IsWordBuildable(string word){
    word = toUpperCase(word);
    if(word.empty()) return true; // base case, if no more letters left  - success
    for (int i=0; i<16; i++){
        if(boggleGrid.get(i/SIZE, i%SIZE)==word[0]){ // search for the first letter in the grid
            if (isPositionOK(i/SIZE, i%SIZE)){ // check if position is suitable
                pickPositionComputer(i/SIZE, i%SIZE); // if position is suitable, optimistically pick the position and recur
                if(IsWordBuildable(word.substr(1))) return true; // continue and if you finish - success
                unPickPositionComputer(i/SIZE, i%SIZE); // otherwise make a step back and try another option
            }
        }
    }
    return false; // if nothing above worked, return false
}



/* Support function for isWordBuildable
 * If position is suitable create a pointT object with the row and col coordinates of the letter and place it in the stack
 * to use for checking whether the position of the next letter is allowable. Same as pickPosition (which is the same
 * function for humanWordSearch but without animation effects */
void Boggle::pickPositionComputer(int row, int col){
    pointT usedPoint;
    usedPoint.col = col;
    usedPoint.row = row;
    usedCubeStack.push(usedPoint);
    usedCubeGrid.set(row, col, true);
}



/* Support function for isWordBuildable
 * When the isWordBuildable algorithm backtracks, this function pops the pointT object representing the used letter
 * row and column coordinates from the stack. Same as unPickPosition (which is the same
 * function for humanWordSearch) but without animation effects */
void Boggle::unPickPositionComputer(int row, int col){
    usedCubeStack.pop();
    usedCubeGrid.set(row, col, false);
}



/* Returns an int representing computer's score */
int Boggle::getScoreComputer() {
    int computerScore = 0;
    for (Set<string>::iterator it = foundWordsComputerBuildable.begin(); it != foundWordsComputerBuildable.end(); ++it) {
        BoggleGUI::recordWord( *it, BoggleGUI::COMPUTER);
        computerScore+=(*it).length()-WORD_SCORE_ADJUSTER;
    }
    return computerScore;
}




/* =============== FUNCTIONS USED IN BOTH HUMAN AND COMPUTER GAMEPLAY =============== */



/* Checks if an entered word exists, if it hasnt already been used and if it satisfies min. length requirements */
bool Boggle::checkWord(string word) {
    return lex->contains(word) && !foundWordsHuman.contains(word) && word.length()>=MIN_WORD_LEN;
}



/* Checks if position is ok (i.e. suitable or allowable) to use for bulding a word per the boggle game rules
 * i.e. it is immediately adjacent to the previously used letter cube and no letter cube is used twice */
bool Boggle::isPositionOK(int row, int col){

    // If the usedCube grid shows that the cube has already been used, return false
    if (usedCubeGrid.get(row, col) == true) return false;

    //if the stack is empty, then we are checking the first letter in the word, so any position is ok
    if ( usedCubeStack.isEmpty() /*&& usedCubeGrid.get(row, col)==false */ ) return true;

    //otherwise, check if the letter position just picked is immediately adjacent to the position of the previous letter
    else{
        pointT prevPoint = usedCubeStack.peek();
        if ( prevPoint.col == col && prevPoint.row ==row ) return false;
        if ( prevPoint.col-col==0 || prevPoint.col-col==1 || prevPoint.col-col==-1 ) { // check adjacency
            if( prevPoint.row-row==0 || prevPoint.row-row==1 || prevPoint.row-row==-1 ){ // check adjacency
                return true;
            }
        }
    }
    return false;
}



/* Did not use this function */
char Boggle::getLetter(int row, int col) {
    if (!boggleGrid.inBounds(row, col)) return -1;
    else{
        return boggleGrid.get(row, col);
    }
}



/* Do not know how to make this function. Did not use it */
/*ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}*/

