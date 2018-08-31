#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "tokenscanner.h"
#include "strlib.h"
#include "random.h"
using namespace std;



/*========== PRIVATE VARIABLES ========== */

/* This map will store the track the number of occurences of a certain character given a certain initial string.
 * occurences of the repeated character are simply recorded as additional characters appended to the nested vector.
 * e.g. if the source text has "hello my name is ...." and " "hello my friend"
 * if the seed key is "hello ", then the next character 'm' will be recorded in the vector as two separate occurences
 * like so {m , m} and the occurData map will have a pair: "hello " :: {m, m}.
 * this simplifies the recording procedure. */
map <string, Vector<char> > occurData;

/* Use ifstream type object as an instance variable, using private variables helps make methods with fewer arguments*/
ifstream file;

/* Use the string object to keep track of the seed. This is the "intake seed". It is not used as a seed for generating
 * random text. It is used when the program makes a pass through the text and populates the occurData map. This string is
 * used for creating keys for the map. It keeps changing as the program make a pass through the text */
string seed;

/* Integer to keep count of the total number of strings/seeds in the input text, used later for probabilities */
int totNumStrings=0;

/* Vector to collect most frequent strings/seeds/keys in the text. E.g. if a seed "hello" and "talk" are used
 * 10 times each. We want them to have equal probalility of occuring as the first word */
Vector<string> mostFreqWords;


/* ========== CONSTANTS ========== */

/* Define a constant for the order of the Markov's model. To change the order of the whole program only this
 * varivable needs to be changed */
const int ORDER = 6;

/* Define number of words to generate in a text */
const int MAX_CHARS = 2000;



/* ========== FUNCTION DEFINITIONS ========== */

/* Open file method */
ifstream openFile(string fileName){
    ifstream ifstr;
    while (true){
        ifstr.open(fileName.c_str());
        if(!ifstr.fail()) break;
        cout << "Unable to open file " << fileName << " try another file name: " << endl;
        string fileName = getLine("Enter file name: ");
        ifstr.clear();
    }
    ifstr >> std::noskipws;
    return ifstr;
}

/* Get next character from the filestream method, used to increase readability of code */
char getNextChar(){
    char ch;
    file >> ch;
    return ch;
}

/* Get the intake seed and populate the map */
void buildOccurences(char nextChar){

    // if map contains the seed
    if(occurData.count(seed)){
        occurData.at(seed).add(nextChar);
        //cout << seed << ":" << nextChar << endl;
    }

    // if map does not contain the seed
    if(!occurData.count(seed)){
        Vector<char> v;
        v.add(nextChar);
        occurData.emplace(seed, v);
        //cout << seed << ":" << nextChar << endl;
    }
    totNumStrings++;
}

/* Make the very first seed to populate the map with */
void buildFirstSeed(){
    for (int i=0; i<ORDER; i++){
        char ch;
        file >> ch;
        if(file.fail()) break;
        seed+=ch;
    }
}

/* Make next seed, by adding one char to the end an erasing one char from the start */
void buildNextSeeds(char ch){
    seed.erase(0,1);
    seed+=ch;
}


/* Build occurData map by passing throug the text file */
void buildData(){
    buildFirstSeed();
    while (true){
        char ch = getNextChar();
        if (file.fail()) break;
        buildOccurences(ch);
        buildNextSeeds(ch);
    }
}

/* Iterate through the map that we've already built and record what is the highest number of occurences of a seed */
int findHighestNumOccur(){
    int num = 0;
    for ( map<string, Vector<char> >::iterator it = occurData.begin(); it!=occurData.end(); ++it){
        if( it->second.size() > num ){
            num = it->second.size();
        }
    }
    return num;
}

/* For cases when there are several most frequent seeds, construct a vector that will have them all,
 * e.g. when seeds hi and my happen 100 times each. There will be a vector of strings {hi, my} */
void makeVecFreqWords(int maxWordOccur){
    for ( map<string, Vector<char> >::iterator it = occurData.begin(); it!=occurData.end(); ++it){
        if( it->second.size() == maxWordOccur ){
            maxWordOccur = it->second.size();
            mostFreqWords.add(it->first);
        }
    }
}

/* Not needed for the program, used for engineer to illustrate if things are working, prints vector of
 * strings item by item on each line */
void printvec( Vector <string> & vec){
    for (int i=0; i<vec.size(); i++){
        cout << vec[i] << endl;
    }
}

/* Pick most frequent word as the first word in random text or when the random text creates a seed that
 * did not occur in the original text */
string pickMostFreqWord(){
    int random = randomInteger(0, mostFreqWords.size()-1);
    return mostFreqWords[random];
}


/* Find the most frequently used word */
string findMostFreqWord(){
    string word;
    int maxWordOccur = findHighestNumOccur();
    makeVecFreqWords(maxWordOccur);
    word = pickMostFreqWord();
    return word;
}


/* Put next characters in the output random text based on the genSeed i.e. seed used for generating text */
void putNextChars(string &genSeed){

    // If such seed exists in the map, use the next char from the map based on probability
    if (occurData.count(genSeed)){
        int rangeOfNextChar = occurData.at(genSeed).size();
        int choice = randomInteger(0, rangeOfNextChar-1);
        char ch = occurData.at(genSeed)[choice];
        cout << ch;
        //cout << "character: " <<ch << endl;

        // Update the generation seed.
        genSeed.erase(0,1);
        genSeed+=ch;
        //cout << "seed:" << genSeed << "!!!!!";

    }

    // If seed does not exist in the map, use one of the most frequent words, and the
    // next character based on the chosen most frequent word from the map
    if (!occurData.count(genSeed)){
        genSeed = findMostFreqWord();
        int rangeOfNextChar = occurData.at(genSeed).size();
        int choice = randomInteger(0, rangeOfNextChar-1);
        char ch = occurData.at(genSeed)[choice];
        cout << ch;
        //cout << "character: " <<ch << endl;

        genSeed.erase(0,1);
        genSeed+=ch;
        //cout << "seed:" << genSeed << "!!!!!";
    }

}


/* Generate random text */
void genRandomText(string &genSeed){
    int count =0;
    while (count < MAX_CHARS){
        putNextChars(genSeed);
        count ++;
    }
}

/* ========== MAIN METHOD ========== */
int main(){

    // Open the file;
    file = openFile("input.txt");

    //Read file and build occurence data; i.e. record seeds and occurences in the map
    buildData();

    //Find on of the most frequent words and use it as the first string
    string genSeed = findMostFreqWord();
    cout << genSeed;

    //Generate rest of the text
    genRandomText(genSeed);

    return 0;
}



