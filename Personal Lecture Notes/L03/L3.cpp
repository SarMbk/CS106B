3 #include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <string>
using namespace std;


/* String example 1
int main(){

    // You can declare a string without initializing it. it constructs an empty string by default
    // C++ string IS MUTABLE!!! unlike the Java string
    string s;
    cout<<s.length() << endl;

    s = "hi my name is saruar i will be a great software engineer and computer scientist";
    for (int i=0; i<s.length(); i++){
        s[i] = toupper(s[i]);
    }
    cout<<s;
    return 0;
}
*/



/* String example 2 */

int countNum(char ch, string s){
    int count = 0;
    for (int i=0; i<s.length(); i++){
        if(s[i]==ch) count++;
    }
    return count;
}


// this method does not modify the original string
string removeOccur(char ch, string s){
    string result;
    for(int i=0; i<s.length(); i++){
        if(s[i]!=ch) result+=s[i];
    }
    return result;
}


// this method does modfy the original string
void removeOccurByRef(char ch, string &s){
    int pos=0;
    while(   (pos = s.find(ch,pos)) != string::npos   ){
        s.erase(pos, 1);
    }
}



int main(){

    string test;
    cout << "Enter srting: ";
    cin >> test;
    cout << countNum('a', test) << endl;



    string test2;
    cout << "enter string ";
    cin >> test2;
    cout << removeOccur('b', test2) << endl;



    string testByRef;
    cout << "enter string by ref: ";
    cin >> testByRef;
    removeOccurByRef('b', testByRef);
    cout << testByRef << endl;



    // you can do this to enter two inputs in one command
    int x, y;
    cout << "enter 2 ints :" << endl;
    cin >> x >> y;
    cout << "you entered " << x << " and " << y << endl;



/*  this stuff is buggy idk why.
    // simpio stanford libraries
    cout << "simpio libraries" << endl;
    cout << "enter an int: ";
    int myint = getInteger();

    cout << "enter a double";
    double mydouble = getReal();

    cout << "eter string";
    string mystring = getLine();

    cout << myint << endl;
    cout << mydouble << endl;
    cout << mystring << endl;
*/




    string s, t = "hello";
    s = t;
    t[0] = 'j';
    s = s + ' ';
    if (s != t){
        t+=" ";
        t+=t;
    }

    cout << s <<endl;
    cout << t <<endl;
    cout << s.length() << endl;



    // Find method is overloaded
    // second argument is the position where you want to start looking from
    // if character not in string gives a random big number
    cout << s.find('o',0) << endl;



    //look for a substring
    cout << s.find("llo",0) << endl;

    // extract a substring
    cout << s.substr(1,3) << endl;

    // insert a string or a character into a string, mutates the original string;
    cout << s.insert(4, ". inserted string .") << endl;
    cout << s << endl;

    // replace starting from position 4 the next 19 characters with a repalcement string,
    // also mutates the original string
    cout << s.replace(4, 19, ". replacement ." ) << endl;

    // Erase parts of string
    cout << s.erase(4,15) << endl;

    string hi = "hi";
    // Beware! this does not give you a bug, doesn't say index out of range!!!
    cout << hi.substr(2,3) << endl;

    // this will not compile, because they are c strings
    // gotta declare string s = "abc;" string s1 = "def"; s+s1;
    // its because indeclared string is a c string
    //cout << "abc" + "def";

    return 0;
}
