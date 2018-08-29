#include "buffer.h"

buffer::buffer(){
    cursor = 0;
}

buffer::~buffer(){
}


void buffer::moveCursorForward(){
    if (cursor < chars.size())
        cursor++;
}


void buffer::moveCursorBackward(){
    if (cursor > 0)
        cursor--;
}


void buffer::moveCursorToStart(){
    cursor = 0;
}


void buffer::moveCursorToEnd(){
    cursor = chars.size();
}


void buffer::insertCharacter(char ch){
    chars.insert(cursor, ch);
    cursor++;
}


void buffer::deleteCharacter(){
    chars.remove(cursor);
}


void buffer::display(){
    for (int i=0; i<chars.size(); i++){
        cout << chars[i];
    } cout << endl;
    for (int i=0; i<cursor; i++){
        cout << " ";
    }
    cout <<'^'<<endl;
}


void buffer::moveToWordBegin(){
    // if the character to the left of the cursor is a space
    // move back until it no longer is to skip over any
    // spaces that appear after the word
    while ( cursor - 1 >= 0 && (chars[cursor - 1] == ' ') ) {
        moveCursorBackward();
    }
    // now move to the front of the word we are currently at -
    // meaning the letter to the left of the cursor is a space or
    // the cursor is at the beginning of the buffer
    while ( cursor - 1 >= 0 && (chars[cursor - 1] != ' ') ) {
        moveCursorBackward();
    }
}

