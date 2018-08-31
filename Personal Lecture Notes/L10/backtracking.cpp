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


// Can't use lexicon.h header for some reason so I'll make my own set of words which I will read from a text file
Set<string> EnglishWords;
ifstream file;


void recPermute(string soFar, string rest){
    if (rest ==""){
        cout << soFar << endl;
    }
    else {
        for(int i=0; i<rest.length(); i++){
            string next = soFar + rest[i];
            string remaining = rest.substr(0,i) + rest.substr(i+1);
            recPermute(next, remaining);
        }
    }
}
void ListPermute (string s){
    recPermute("", s);
}


bool isAnagram(string soFar, string rest, Set<string> &lex){
    if (rest ==""){
        if(lex.contains(soFar)) cout << soFar << endl;
        return lex.contains(soFar);
    }
    else {
        for(int i=0; i<rest.length(); i++){
            string next = soFar + rest[i];
            string remaining = rest.substr(0,i) + rest.substr(i+1);
            if( isAnagram(next, remaining, lex) ) return true;
        }
    }
    return false;
}
bool Anagram(string s){
    return isAnagram("",s,EnglishWords);
}



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


/* Method to print a set, just iterates over a set and uses cout to show what's in it */
void printSet(Set<string> &possibleWords){
    for (Set<string>::iterator it = possibleWords.begin(); it!=possibleWords.end(); ++it){
        cout << *it << endl;
    }
}


int main(){
    // Open the file;
    file = openFile("englishwords.txt");

    // Build a set of words;
    BuildLexicon(file);

    cout << boolToString( Anagram("tca") ) << endl;





    return 0;
}

