#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"
#include "lexicon.h"
#include "dawglexicon.h"
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "tokenscanner.h"
#include "strlib.h"
#include "random.h"

using namespace std;

/* ========== GLOBAL VARIABLES ========== */

// Can't use lexicon.h header for some reason so I'll make my own set of words which I will read from a text file
Set<string> EnglishWords;
ifstream file;


/* ========== FUNCTION DEFINITIONS ========== */

/* Open file method */
ifstream openFile(string fileName){
    ifstream ifstr;
    while (true){
        ifstr.open(fileName.c_str());
        if(!ifstr.fail()) break;
        cout << "Unable to open file " << fileName << " try another file name: " << endl;
        fileName = getLine("Enter file name: ");
        ifstr.clear();
    }
    return ifstr;
}


/* Method that takes in an opened ifstream files containing 10,000 english words,
 * Passes through it and puts them in the words set global variable */
void BuildLexicon(ifstream &in){
    while(true){
        string word;
        in >> word;
        if(in.fail()) break;
        // key is signature of word, set of strings contains anagrams
        EnglishWords.add(word);
    }
    cout << "number of words loaded: " << EnglishWords.size() << endl;
}


/* Method takes a digit character as input and returns a string containing three letters assigned to that
 * digit on a telephone keyboard */
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


/* Recursive method that finds all possible combinations of letters given a string of digits,
 * and adds them to the possibleLetters set */
void RecBuildPossibleLetters(string lettersSoFar, string remDigits, Set<string> &possibleLetters){
    if (remDigits==""){
        possibleLetters.add(lettersSoFar);
    }
    else{
        string nextLetters = digitToLetters(remDigits[0]);
        for (int i=0; i<nextLetters.length(); i++){
            RecBuildPossibleLetters(lettersSoFar+nextLetters[i], remDigits.substr(1), possibleLetters);
        }
    }
}


/* Wrapper function that returns the possible letters set */
Set<string> ListPossibleLetters(string digits){
    Set<string> possibleLetters;
    RecBuildPossibleLetters("", digits, possibleLetters);
    return possibleLetters;
}


/* Method to print a set, just iterates over a set and uses cout to show what's in it */
void printSet(Set<string> &possibleWords){
    for (Set<string>::iterator it = possibleWords.begin(); it!=possibleWords.end(); ++it){
        cout << *it << endl;
    }
}


/* Accepts a set of possibleLetters, a wordlist lexicon set, and a digitSequence string and returns
 * a set of possible words that can be typed in by the digit sequence */
Set<string> findPossibleWords(Set<string> &possibleLetters, Set<string> &wordList, string digitSequence){
    Set<string> possibleWords;
    int strLength = digitSequence.length();
    for (Set<string>::iterator itWords = wordList.begin(); itWords!=wordList.end(); ++itWords){
        string beginning = toUpperCase((*itWords).substr(0,strLength));
        //cout << beginning << endl;
        if( possibleLetters.contains(beginning) ){
            possibleWords.add(*itWords);
        }
    }
    return possibleWords;
}


/* Function that accepts a digit sequence string and a reference to the a set containing english words
 * and returns a set of possible words that these digits may start */
void listCompletions (string digitSequence, Set<string> &wordList){
    // Get a set of possible letters
    Set<string> possibleLetters = ListPossibleLetters(digitSequence);

    // See if possible letters start any words in our lexicon
    Set<string> possibleWords = findPossibleWords(possibleLetters, wordList, digitSequence);

    //Print possible words
    printSet(possibleWords);

}


/* ========== MAIN METHOD ========== */

int main(){
    // Open the file;
    file = openFile("englishwords.txt");

    // Build a set of words;
    BuildLexicon(file);


    // Test the program
    listCompletions("72547", EnglishWords);

    return 0;
}
