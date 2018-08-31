#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "queue.h"   // for queues
#include "random.h"
#include "ranlib.h"
#include "set.h"
#include "strlib.h"
#include "string.h"

using namespace std;


/* FUNCTION PROTOTYPES */
void findPerfectNum(int rangeLower, int rangeUpper);
bool isPerfect(int num);
Queue<int> findDivisors(int num);
void ElectionSimulation();
void examHistogram();
ifstream openFile(string filename);
void printSoundex();
string convertToCode(string name, Vector<string> &table);

/* MAIN METHOD */
int main(){
    //findPerfectNum(0, 10000); cout << endl << endl;
    //ElectionSimulation(); cout << endl << endl;
    //examHistogram();






    printSoundex();
    return 0;
}


/* FUNCTION DEFINITIONS */

void ElectionSimulation(){
    int numVoters =
        getInteger("Enter number of voters", "You must enter a positive integer, try again");
    int numSimulations =
        getInteger("Enter the number of election simulations: ","You must enter a positive integer, try again" );
    double voterSpread =
        getDoubleBetween("Enter percentage spread between candidates, e.g. for 10% enter 0.1 etc: ", 0.0, 1.0);
    double votingError =
        getDoubleBetween("Enter vote recording error chance, e.g. for 15% enter 0.15 etc: ", 0.0, 1.0);


    // Determine the correct number of votes for each candidate given the spread and numVotes
    int correctVotesLower = numVoters*(0.5 - 0.5*voterSpread);
    int correctVotesHigher = numVoters*(0.5 + 0.5*voterSpread);
    int invalidElections = 0;


    // Run simulations
    for (int i = 0 ; i<numSimulations; i++){
        // Before every simulation, set the correct number of votes for each candidate
        int votesLower = correctVotesLower;
        int votesHigher = correctVotesHigher;


        // Redistribute votes due to vote recording error
        for (int j = 0; j<correctVotesLower; j++){
            if (randomChance(votingError)){
                votesLower--;
                votesHigher++;
            }
        }

        for (int k = 0; k<correctVotesHigher; k++){
            if(randomChance(votingError)){
                votesLower++;
                votesHigher--;
            }
        }

        if(votesLower > votesHigher) {invalidElections++;}

    }

    cout << "After " << numSimulations << " simulations, elections were invalid "
         << (double)invalidElections*100.0/(double)numSimulations
         << " percent of times" << endl;
}


/* Prints the perfect numbers in the given range if integers
 * arguments lowest and highest number in the range */
void findPerfectNum (int rangeLower, int rangeUpper){
    for (int i=rangeLower; i<=rangeUpper; i++){
        if (isPerfect(i)){
            cout << i << " is a perfect number." << endl;
        }
    }
}


/* Returns true if the integer number entered as an argument is a prefect number
 * otherwise returns false */
bool isPerfect(int num){
    Queue <int> divisors= findDivisors(num);
    int sumDivisors=0;
    while(!divisors.isEmpty()){
        sumDivisors+=divisors.dequeue();
    }
    if (sumDivisors==num){
        return true;
    }
    return false;
}


/* Retuns a queue object containing all the integer divisors of a number;
 * argument: integer number you want to find divisors for */
Queue<int> findDivisors(int num){
    Queue<int> divisors;
    for (int i=1; i<num; i++){
        if(num % i ==0){
            divisors.enqueue(i);
        }
    }
    return divisors;
}


/* Opens a file, returns the ifstream object */
ifstream openFile(string filename){
    ifstream file;
    string lastFileName = filename;
    while(true){
        file.open(lastFileName.c_str());
        if (!file.fail()) break;
        cout << "Cannot open file " << lastFileName << ". Try another filename" << endl;
        lastFileName = getLine("Enter file name: ");
        file.clear();
    }
    return file;
}


/* Prompts user to enter a text file name. Opens a file of test scores;
 * prints a histogram of scores */
void examHistogram(){
    string filename = getLine("Enter file name: ");
    Vector <int> scores (10, 0);
    ifstream file = openFile(filename);

    // Read scores and place them in the vector
    while (true){
        int score;
        file >> score;
        if(file.fail()) break;
        if (score < 100){
            scores[score/10]++;
        }
        else {
            scores[9]++;
        }
    }
    file.close();


    // Print histogram
    for (int i=0; i<scores.size(); i++){

        /* If statements are used to control the alignment of text with the setw(int width) command
         * because text 0 to 9 has different width than text 90 to 100 which distorts the histogram alignment */
        if (i==0){
            cout << right << setw(5) << (i*10) << " to " << (i*10+9) << ":";
        }

        if (i<scores.size()-1){
            if (i>0){cout << right << setw(4) << (i*10) << " to " << (i*10+9) << ":";}
        }

        else {
            cout << right << setw(3) << (i*10) << " to " << (scores.size()*10) << ":";
        }

        for (int j=0; j<scores[i]; j++){
            cout << " * ";
        }
        cout << endl;
    }
}


void printSoundex(){

    // Create the conversion table for the soundex problem
    Vector<string> conversionTable(7, "");
    conversionTable[0] = "AEIOUHWY";
    conversionTable[1] = "BFPV";
    conversionTable[2] = "CGJKQSXZ";
    conversionTable[3] = "DT";
    conversionTable[4] = "MN";
    conversionTable[5] = "L";
    conversionTable[6] = "R";


    // Run prompt user to enter names; quit when he enters a blank line;
    // convert name to code
    while (true){
        string name = getLine("Enter a name to convet to soundex: ");
        if (name.empty()) break;
        cout << convertToCode(toUpperCase(name), conversionTable) << endl;
    }
}


string convertToCode(string name, Vector<string> &table){
    name = toUpperCase(name);

    // Keep the first letter
    string nameCode = name.substr(0, 1);

    // Convert all the letters to number codes
    for (int i = 1; i<name.length(); i++){
        for (int j = 0; j<table.size(); j++){
            string s = table.get(j);
            if (s.find(name[i]) != string::npos){
                nameCode+=integerToString(j);
            }
        }
    }

    // Remove consecutive duplicate digits
    for (int i=1; i<nameCode.length(); i++){
        if(nameCode[i] == nameCode[i-1]){
            nameCode.erase(i,1);
        }
    }

    // Remove zeros
    int pos = 0;
    while ( (pos = nameCode.find('0', pos) ) != string ::npos){
        nameCode.erase(pos, 1);
    }

    // Make code exactly 4 symbols long by truncating or padding with zeros
    if (nameCode.length() >4){
        while (nameCode.length() > 4) {
            nameCode.erase(nameCode.length()-1);
        }
    }

    if (nameCode.length() < 4){
        while(nameCode.length()<4){
            nameCode+="0";
        }
    }

    return nameCode;
}




