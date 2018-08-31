#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gobjects.h"
#include "ginteractors.h"
#include "grid.h"
#include "fstream"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "bogglegui.h"
#include "Boggle.h"

using namespace std;


void playOneGame(Lexicon& dictionary) {

    // Initialize graphics interphase
    BoggleGUI::initialize(4,4);

    // Ask if user wants to generate a random or a manual board
    string genRandBoardYesNo = getLine("Do you want to generate a random board?");

    // Enforce user input, proceed only if user enters "y" or "n"
    while (true){
        genRandBoardYesNo = toUpperCase(genRandBoardYesNo);
        if (genRandBoardYesNo=="Y" || genRandBoardYesNo=="N") break;
        else genRandBoardYesNo = getLine("Invalid input please enter y/n: ");
    }

    // Generate random board or make board from a manually entered string
    string boardText;
    if (genRandBoardYesNo=="Y"){
        boardText = "";
    }
    else if (genRandBoardYesNo == "N"){
        boardText = getLine("Enter a string of 16 characters without any spaces or punctuation: ");
    }
    Boggle boggle (dictionary, boardText);

    //Let the human play
    boggle.letHumanPlay();

    // Let the computer play
    boggle.letComputerPlay();

    // Humiliate the human in case of computer winning
    if (boggle.getScoreComputer()>boggle.getScoreHuman()){
        BoggleGUI::setStatusMessage("Hahaha! I destroyed you! Better luck next time, puny human!");
        cout << "Hahaha! I destroyed you! Better luck next time, puny human!" << endl;
    }

}
