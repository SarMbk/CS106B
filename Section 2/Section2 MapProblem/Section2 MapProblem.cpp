#include <iostream>
#include <map>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <math.h>
#include "fstream"
#include "tokenscanner.h"


using namespace std;

/* STRUCTURE DEFINITIONS */



/* FUNCTION PROTOTYPES */
char MostFrequentCharacter (ifstream &ifstr, int &numOccurences, map<char, int> &m);



/* MAIN METHOD */
int main(){


    int numOccurences = 0;
    map <char, int> letterFreq;

    //Create ifstream object acessing a text file
    ifstream file("hello.txt"); // this is how to quickly open a file

    cout << MostFrequentCharacter(file, numOccurences, letterFreq);

    return 0;
}



/* FUNCTION DEFINITIONS */


// This function gets an ifstream file and updates the number of occurrences of the most frequent character
char MostFrequentCharacter (ifstream &file, int &numOccurences, map<char, int> &m){
    // Reads a file and puts all characters in a map. Whitespace is not a character. Punctuation is characters.
    while (true){
        char ch;
        file >> ch;
        if (file.fail()) break;
        m[ch]++;
    }

    char mostFrequent;
    for ( map<char,int>::iterator it = m.begin(); it!=m.end(); ++it){
        if(it->second > numOccurences){
            numOccurences = it->second;
            mostFrequent = it->first;
        }
        // Print the entire map
        cout << it->first << ": " << it->second <<endl;
    }

    cout << "Most frequent character: " << mostFrequent << " ; " << numOccurences << " occurences." << endl;

    return mostFrequent;
}



