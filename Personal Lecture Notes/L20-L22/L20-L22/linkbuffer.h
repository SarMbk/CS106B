#ifndef LINKBUFFER_H
#define LINKBUFFER_H

#include <iostream>
using namespace std;

class linkbuffer
{
public:
    linkbuffer();
    ~linkbuffer();

    void moveCursorForward();
    void moveCursorBackward();

    void moveCursorToStart();
    void moveCursorToEnd();

    void insertCharacter(char ch);
    void deleteCharacter();

    void moveToWordBegin();

    void display();

private:
    struct cellT
    {
        char ch;
        cellT *next;
    };
    cellT *head, *cursor;

    bool isspace(char ch);

};

#endif //LINKBUFFER_H
