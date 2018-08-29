#ifndef BUFFER_H
#define BUFFER_H

#include "vector.h"
//#include <iostream>
using namespace std;

class buffer
{
public:
    buffer();
    ~buffer();

    void moveCursorForward();
    void moveCursorBackward();

    void moveCursorToStart();
    void moveCursorToEnd();

    void insertCharacter(char ch);
    void deleteCharacter();

    void moveToWordBegin();

    void display();

private:
    Vector<char> chars;
    int cursor;

};

#endif // BUFFER_H
