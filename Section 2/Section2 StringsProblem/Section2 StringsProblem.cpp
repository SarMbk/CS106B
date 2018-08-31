#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "tokenscanner.h"
#include "stack.h"
#include "queue.h"
#include "strlib.h"
using namespace std;


// FUNCTION PROTOTYPES
bool isCorrectlyNested(string &htmlStr);
bool processTags(TokenScanner &scanner, Stack<string> &tagStack);
void collectOpenTags(Stack<string> &tagStack, string &token);
bool processClosingTag(Stack<string> &tagStack, string &token);


// MAIN METHOD
int main(){
    // Ask to input a string and print true if it is correctly nested per html syntax
    string htmlStr = getLine("Enter string: ");
    cout << boolToString( isCorrectlyNested(htmlStr) ) << endl;
    return 0;
}


// FUNCTION DEFINITIONS
bool isCorrectlyNested(string &htmlStr){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.setInput(htmlStr);
    Stack<string> tagStack;

    return processTags(scanner, tagStack);
}


/* The tokenscanner scans for tokens one by one,
 * if it detects a < it checks for the next token
 * if the next token is not / then it is an opening tag
 * it simply pushes the opening tag into a tag stack
 *
 * if the next token is / then it is a closing tag, this means
 * that the previous tag is an equivalent opening tag
 * and in case of correct nesting it should be in the tag stack
 * because we push all opening tags in the tag stack.
 * so we pop an element from the tag stack and if it is not
 * an equivalent opening tag or the stack is empty then the
 * string is definitely incorrectly nested
 *
 * Returns true if the scanner detects correcly nested tags
 * otherwise returns false */
bool processTags(TokenScanner &scanner, Stack<string> &tagStack){
    // Assume the stack is correctly nested
    bool correctlyNested = true;
    while(scanner.hasMoreTokens()){
        string token = scanner.nextToken();
        // if you find a tag sign, get next tokens and see if its an opening or a closing tag
        if (token == "<"){
            token = scanner.nextToken();
            // If you find a closing tag compare it to the one you just put in the stack
            // If they are different, change correctlyNested to false
            if(token =="/"){
                token = scanner.nextToken();
                correctlyNested = processClosingTag(tagStack, token);
            }
            // If it is not a closing tag, then its an opening tag, so just push it into the tag stack
            else {
                collectOpenTags(tagStack, token);
            }
        }

        // In the end all opening and closing tags should balance out.
        if (correctlyNested==false){
            return false;
        }
    }
    // it may be that the tags balanced out but the stack still has some tags in it
    // this also means that nesting is incorrect
    if(!tagStack.isEmpty()){
        return false;
    }

    return true;
}


/* When an opening tag is encountered it is simpy pushed into a tagstack */
void collectOpenTags(Stack<string> &tagStack, string &token){
    tagStack.push(token);
    //cout << tagStack.toString() << endl;
}


/* Once you encountered a closing tag,
 * you pop the topmost tag in the tagstack
 * you only have opening tags in the tagstack
 * then you compare the topmost tag in the tagstack vs the currenltly encountered closing tag
 * if the tagstack is empty then the nesting is incorrect
 * if the tagstack pops a different tag than the encountered closing tag
 * thenthe nesting is also incorrect
 *
 * returns true if the token is the same as the token popped from the tagstack
 * pops the element from the tagstack so it is modified */
bool processClosingTag(Stack<string> &tagStack, string &token){
    if(tagStack.isEmpty()){
        //cout << "cond 1" << endl;
        return false;
    }
    if(!tagStack.isEmpty() && token == tagStack.pop()){
        //cout << "cond 2" << endl;
        //cout << "stack: " << tagStack.toString() << " ; token: " << token << endl;
        return true;
    }
    if(!tagStack.isEmpty() && token!=tagStack.pop()){
        //cout << "cond 3" << endl;
        //cout << "stack: " << tagStack.pop() << endl;
        //cout << "token: " << token << endl;
        return false;
    }
    return false;
}




// <html><b><i> hello </i></b></html>    <html><i><b> hello world </b></i></html>
