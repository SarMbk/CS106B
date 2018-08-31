#include <iostream>
#include <fstream>  //  for opening files
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "tokenscanner.h"
using namespace std;


/* Function Prototypes */
int countLines(ifstream &in);
ifstream openFile();
void countTokens();
void testVector();


/* Main method */
int main(){

    /*

    //This is the traditional method for inputs
    int x,y;
    cout << "Enter x and y: ";
    cin >> x >> y;
    cout << "You entered: " << x << " and " << y << endl << endl;
    
    // Better simpio inpit method
    int i = getInteger("Enter an integer, this is the simpio library method: ");
    cout << "You entered: " << i << endl << endl;

    //for strings
    string s1 = getLine("This is the simpio method for string inputs: ");
    cout << "You entered: " << s1 << endl << endl;

    //for double floats
    double d = getReal("This is the simpio method for double inputs: ");
    cout << "You entered: " << d << endl << endl;

    */

    // Opening files. String representing the file name should be a C string!
    // suppose you have a C++ string s
    // to convert it to a C string you do this: s.c_str()

    /*

    ifstream in;            // Create an object of type input file stream
    while (true){
        cout << "Enter file name: ";
        string s = getLine();
        in.open(s.c_str());     // need to convert a C++ string into a C string (lagacy issue)
        if (!in.fail()) break;
        cout << "Couldn't open file try another file name.";
        in.clear(); // this clears the error state from the ifstream object; if you don't do this you'll get errors dow
                    // the road
    }

    */

    ifstream file = openFile();

    cout << "Trying out the function to count lines: " << endl;
    cout << "Number of lines: " << countLines(file) << endl << endl;


    cout << "Counting tokens" << endl;
    countTokens();


    //testVector();

    return 0;
}

/* Function Definitions */

// This function counts lines in a text file
// You pass the object of class ifstream as an argument
// You typically want to pass it by reference (because files can be big, passing by name can eat a lot of memory
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


// This function opens a text file and returns an ifstream object
ifstream openFile(){
    ifstream file;
    while (true){
        string fileName = getLine("Enter file name: ");
        file.open(fileName.c_str());
        if(!file.fail()) break;
        cout << "Unable to open file " << fileName << " try another file name: " << endl;
        file.clear();
    }
    return file;
}


// This function allows to enter a string and prints number of tokens
void countTokens(){
    // Create object of type scanner
    TokenScanner scanner;
    cout << "Enter a sentence: ";
    scanner.setInput(getLine());
    int count = 0;
    while (scanner.hasMoreTokens()){
        scanner.nextToken();
        count++;
    }
    cout << "You entered " << count << " tokens." << endl;
}


/*
void testVector(){
    Vector<int> nums;
    nums.add(7);

    Vector<string> words;
    words.add("apple");

    nums.add("banana");         //compile error
    words.add(1)                //compile error
    char c = words.get(0);      //compile error
    Vector<double> s = nums;    //compile error
}
*/











