#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "tokenscanner.h"
#include "strlib.h"
#include "random.h"
using namespace std;



/* DATA STRUCTURES */
struct freqData{
    string word;
    int freq;
};


/* CONSTANTS */

/* Define a constant for the order of the Markov's model. To change the order of the whole program only this
 * varivable needs to be changed */
const int ORDER = 2;

/* Define number of words to generate in a text */
const int LENGTH = 100;


/* INSTANCE VARIABLES */

/* This map track the number of occurences of a certain letter given the certain initial string */
map <string, Vector<freqData> > markovModel;

/* This map tracks frequencies of strings by themselves */
map <string, int> frequencies;

/* Use ifstream type object as an instance variable */
ifstream file;

/* Use this int to count the total number of words in the input text file */
int totalTokens = 0;


/* FUNCTION DEFINITIONS */

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
    return ifstr;
}


// Build map of absolute word frequencies
void buildFrequencies(){
    TokenScanner scanner (file);
    scanner.ignoreWhitespace();
    while(scanner.hasMoreTokens()){
        string word = scanner.nextToken();
        word = toLowerCase(word);
        if(file.fail()) break;
        if(frequencies[word]==0){
            frequencies[word]=1;
        } else {
            frequencies[word]+=1;
        }
        // Count total number of tokens
        totalTokens ++;
    }
}







//Build map of conditional frequencies
void buildCondFreq(){

    TokenScanner scanner (file);

    // This vecor will store pairs of next tokens and their frequencies for a given token sequence


    // This vector will store temporary tokens for easier token manipulation
    Vector<string> tokenSeqVec;

    while(scanner.hasMoreTokens()){
        string tokenSequence;
        for (int i=0; i<ORDER; i++){
            string word = scanner.nextToken();
            tokenSequence+=word;
            tokenSeqVec.add(word);
        }

        string nextWord = scanner.nextToken();
        tokenSeqVec.remove(0);
        tokenSeqVec.add(nextWord);


        // If the word sequence doesn't yet exist in the markov map
        if(  markovModel.find(tokenSequence)==markovModel.end()  ){
            Vector<freqData> v;
            freqData wordFreqPair;
            wordFreqPair.word = nextWord;
            wordFreqPair.freq = 1;
            v.add(wordFreqPair);
            markovModel.emplace(tokenSequence, v);
        }


        // If the word sequence already exists in the markov map
        if(  markovModel.find((tokenSequence))!=markovModel.end()  ){

            int entriesSize = markovModel.at(tokenSequence).size()-1;
            // Go through all members of the vector mapped for a given word sequence in a map

            int i=0;
            while(i < entriesSize){
                if(nextWord == markovModel.at(tokenSequence).get(i).word){

                    freqData wordData = markovModel.at(tokenSequence).get(i);
                    wordData.freq++;
                    markovModel.at(tokenSequence).insert(i, wordData);
                    break;
                }
                i++;
            }

            if (i==entriesSize){
                cout << "true" << endl;
                freqData wordFreqPair;
                wordFreqPair.word = nextWord;
                wordFreqPair.freq = 1;
                markovModel.at(tokenSequence).add(wordFreqPair);
            }
        }
    }
}


// Method to print a map
void printMap (map<string, int> &m){
    for ( map<string,int>::iterator it = m.begin(); it!=m.end(); ++it){
        cout << it->first << ": " << it->second <<endl;
    }
}


// Generate random word
string genRandomWord(){

    bool flag = false;
    string word;
    while (!flag){
        for ( map<string, int>::iterator it = frequencies.begin(); it!=frequencies.end(); ++it){
            double wordFreq = (it->second);
            double probability = wordFreq/totalTokens;
            bool wordPicked = randomChance(probability);
            if (wordPicked){
                word = it->first;
                flag = true;
            }
            //std::cout << std::fixed;
            //std::cout << std::setprecision(5);
            //cout << prob << endl;
        }
    }


    return word;
}



// Generate a randomized text
void genTextAbsolute(){
    int count = LENGTH;

    while (count > 0){
        string word = genRandomWord();
        if (word[0]=='.' || word[0]==',' || word[0]==':' || word[0]==';' || word[0]=='\''){
            cout << word;
        } else {
            cout << " " << word;
        }
        count--;
    }
}


/*
string genRelativeWord(string seed){

    bool flag = false;
    string word;
    while (!flag){
        for ( map<string, int>::iterator it = frequencies.begin(); it!=frequencies.end(); ++it){
            double wordFreq = (it->second);
            double probability = wordFreq/totalTokens;
            bool wordPicked = randomChance(probability);
            if (wordPicked){
                word = it->first;
                flag = true;
            }
            //std::cout << std::fixed;
            //std::cout << std::setprecision(5);
            //cout << prob << endl;
        }
    }


    return word;

} */


// Generate text relative to previous tokens
void genTextRelative(){
    int count = LENGTH;
    string word = genRandomWord();
    cout << word;
    while(count >0){
        //word = genRelativeWord();
        cout << word;
    }
}









/* MAIN METHOD */
int main(){
    // Open the file
    file = openFile("short.txt");
    buildFrequencies();
    buildCondFreq();
    //printMap(frequencies);
    cout << totalTokens << endl;
    genTextAbsolute();
    cout << endl << endl;

    for ( map<string, Vector<freqData> >::iterator it = markovModel.begin(); it!=markovModel.end(); ++it){
        cout << it->first << endl;
    }


    return 0;
}



/* FUNCTION DEFINITIONS */



