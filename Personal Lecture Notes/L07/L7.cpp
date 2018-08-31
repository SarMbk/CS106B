#include <iostream>
#include "fstream"
#include "console.h"
#include "gobjects.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"     // for Set
#include <math.h>
using namespace std;


/* Plot a function example, passing a function as an argument
// CONSTANTS
const double increment = 0.1;
const int scaleF = 30;
GWindow gw(800, 600);

// FUNCTION DEFINITIONS

// This is how to define a function that has a function inside it as a parameter
void plotFunction(int startX, int endX, double(function)(double)){
    double centerY = gw.getCanvasHeight()/2.0;
    double centerX = gw.getCanvasWidth()/2.0;
    for (double x = startX; x<=endX; x+=increment){
        GLine *line;
        line = new GLine(scaleF*x, -scaleF*fn(x), scaleF*(x+increment), -scaleF*fn(x+increment));
        line->move(centerX, centerY);
        gw.add(line);
    }
}


int main(){
    plotFunction(0, 100, sqrt);
    return 0;
}

*/


/* This is how to place data structures into a set;
 * without <code> compareStudents </code> function the program will not compile
 * because the set does not know how to compare two data structures

struct studentT {
    string first, last;
    int idNum;
};

/* Define a function that will tell the computer how to compare the
 * <code> studentT </code> data structures

int compareStudents(studentT a, studentT b){
    if(a.idNum==b.idNum) return 0;
    if(a.idNum < b.idNum) return -1;
    else return 1;
}


int main(){
    // Now when you initiate a set, pass the function as a parameter
    // This is called "supplying a callback function"
    Set<studentT> myClass(compareStudents);
    return 0;
}
*/

void Swap (char &ch1, char &ch2){
    char tmp = ch1;
    ch1 = ch2;
    ch2 = tmp;
}


string Signature(string s){
    for(int i=0; i<s.length(); i++){
        int minIndex = i;
        for (int j= i+1; j<s.length(); j++){
            if (s[j]<s[minIndex]){
                minIndex = j;
                Swap (s[i], s[minIndex]);
            }
        }
    }
    return s;
}




void ReadFile(ifstream &in, map< string, Set<string> > &m){
    while(true){
        string word;
        in >> word;
        if(in.fail()) break;
        // key is signature of word, set of strings contains anagrams
        m[Signature(word)].add(word);
    }
    cout << "num words: " << m.size() << endl;


    int maxSize = 0;
    string maxKey;
    for ( map<string, Set<string> >::iterator it = m.begin(); it!=m.end(); ++it){
        if(it->second.size() > maxSize){
            maxSize = it->second.size();
            maxKey = it->first;
        }
    }
    cout << "max cluster: " << maxKey << " : " << maxSize << endl;


    for ( Set<string>::iterator it = m[maxKey].begin(); it!=m[maxKey].end(); ++it){
        cout << *it << endl;
    }
}



int main(){
    ifstream in("readme.txt");
    map< string, Set<string> > m;
    ReadFile(in, m);
    return 0;
}


