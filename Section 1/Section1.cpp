#include <iostream>
#include <fstream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector

using namespace std;


/* Define a data structure needed to keep score stats */
struct scoreTracker{
    int highScore;
    int lowScore;
    double average;
};



/* FUNCTION PROTOTYPES */
string CensorStringValue(string text, string remove);
void CensorStringRef(string &text, string remove);
ifstream openFile(string fileName);
void countLetters(string fileName);



/* MAIN METHOD */
int main(){
    // Problem 1
    string s = getLine("Enter string");
    string remove = getLine("Enter remove string");
    cout << "Censored string by value: " << endl << CensorStringValue(s,remove) << endl;
    CensorStringRef(s,remove);
    cout << "Censored string by reference: " << endl << s << endl << endl;;


    // Problem 3
    countLetters("test.txt");
    cout << endl << endl;


    // Problem 2
    ifstream scoresFile = openFile("scores.txt");
    double sum = 0;
    int count = 0;
    scoreTracker scoreStats;
    scoreStats.highScore=0;
    scoreStats.lowScore=100;

    while (true){
        // This is how you read ints from a text file
        int score;
        scoresFile >> score;
        if(scoresFile.fail()) break;

        count++;
        sum+=(double)score;
        if(score>scoreStats.highScore){scoreStats.highScore = score;}
        if(score<scoreStats.lowScore){scoreStats.lowScore = score;}

    }
    scoresFile.close();
    cout << endl << endl << endl;
    cout << "Highest score: " << scoreStats.highScore << endl;
    cout << "Lowest score: " << scoreStats.lowScore << endl;
    cout << "Average: " << sum/count << endl;
    cout << "Total scores recorded: " << count << endl;


    return 0;
}


/* FUNCTION DEFINITIONS */


int countLines(ifstream &in){
    int count = 0;
    while(true){
        string s;
        getline(in, s); // read the line from the file, store it in the s variable; s in this function is passed by ref
        if(in.fail()) break;    // if no more lines, the in.fail will return true
        count ++;
    }
    return count;
}



// Removes all characters from string text that are present in string remove
// arguments are passed by value, original string text is unchanged
// returns modified copy of the string
string CensorStringValue(string text, string remove){
    string result = "";
    int pos = 0;

    for (int i=0; i<text.length(); i++){
        //if the current caracter in the text string is not found in the remove string
        if(remove.find(text[i]) == string::npos){
            result+=text[i];
        }
    }
    return result;
}



/* Removes all characters from string text that are present in string remove
 * arguments text is passed by reference so it modifies the original sting */
void CensorStringRef(string &text, string remove){
    int pos = 0;
    for (int i=0; i<remove.length(); i++){
        while(    (pos = text.find(remove[i]))  !=   string::npos      ) {
            text.erase(pos, 1);
        }
    }
}



/* This function counts the number of each letter in a textfile */
void countLetters(string fileName){
    ifstream file = openFile(fileName);

    //Letter count will be inside a vector
    Vector <int> letterCount(26);

    while(true){
        int ch = file.get();
        if (ch == EOF) break;
        if(isalpha(ch)){
            letterCount[toupper(ch) - 'A']++;
        }
    }
    file.close();
    for (char ch = 'A'; ch<='Z'; ch++){
        cout << ch << "  " << letterCount[ch-'A'] << endl;
    }

}



// Function to open a textfile; returns an object of class ifstream representing an opened file
ifstream openFile(string fileName){
    ifstream file;
    while (true){
        file.open(fileName.c_str());
        if(!file.fail()) break;
        cout << "Unable to open file " << fileName << " try another file name: " << endl;
        string fileName = getLine("Enter file name: ");
        file.clear();
    }
    return file;
}




