// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
using namespace std;

/* Please see source files for comments to these functions */
class Boggle {
public: 

    Boggle(Lexicon& dictionary, string boardText = "");

    int getScoreHuman();
    int getScoreComputer();

    void letHumanPlay();
    void letComputerPlay();



private:

    /* Recursive functions */
    bool humanWordSearch(string word);
    void computerWordSearch();
    bool IsWordBuildable(string word);
    void findAllWordsComputer(int row, int col, string soFar);


    /* Support subfunctions for recursive functions */
    bool isPositionOK(int row, int col);
    void pickPosition(int row, int col);
    void unPickPosition(int row, int col);

    void pickPositionComputer(int row, int col);
    void unPickPositionComputer(int row, int col);

    char getLetter(int row, int col);
    bool checkWord(string word);

    bool isFirstPosition();
    void markUsedPositions();


    /* Board setup functions */
    void generateManualBoard(string boardText);
    void generateRandomBoard();

    /* Did not use this */
    friend ostream& operator<<(ostream& out, Boggle& boggle);

};

#endif // _boggle_h



