#include "linkbuffer.h"

linkbuffer::linkbuffer(){
    head = cursor = new cellT;
    head->next = nullptr;
}


linkbuffer::~linkbuffer(){
    cellT *cp = head;
    while (cp != nullptr){
        cellT *next = cp->next;
        delete cp;
        cp = next;
    }
}


void linkbuffer::moveCursorForward(){
    if (cursor->next != nullptr)
        cursor = cursor->next;
}


void linkbuffer::moveCursorBackward(){
    if (cursor != head){
        cellT *cp = head;
        while (cp->next != cursor)
            cp = cp->next;
        cursor = cp;
    }
}


void linkbuffer::moveCursorToStart(){
    cursor = head;
}


void linkbuffer::moveCursorToEnd(){
    while (cursor->next != nullptr)
        moveCursorForward();
}


void linkbuffer::insertCharacter(char ch){
    cellT *cp = new cellT;
    cp->ch = ch;
    cp->next = cursor->next;
    cursor->next = cp;
    cursor = cp;
}


void linkbuffer::deleteCharacter(){
    if (cursor->next != nullptr){
        cellT *old = cursor->next;
        cursor->next = old->next;
        delete old;
    }
}


void linkbuffer::display(){
    cellT *cp = head->next; // start at dummy cell
    while (cp != nullptr){
        cout << cp->ch;
        cp = cp->next;
    }
    cout << endl;

    cp = head->next; // start at dummy cell
    while (cp != cursor){
        cout << " ";
        cp = cp->next;
    }
    cout << "^" << endl;
}

/* moveToWordBegin
 * The function starts at the beginning of buffer and walks down the
 * list until it is pointing to the character just before the one the
 * cursor points to. As it walks down the list, it keeps track of the
 * last beginning of a word it saw. When it reaches the cursor, it
 * knows where the first word beginning to the left of the current word
 * is, and moves the cursor there. If there is no word beginning to the
 * left of the current word, the function moves the cursor to the
 * beginning of the buffer. If we had a doubly-linked list, we could
 * search backward from the cursor to find the first space. Given it is
 * singly-linked, we had to go from the head forward to find where we
 * were. */
void linkbuffer::moveToWordBegin() {
    cellT *wordStart, *curr, *prev;
    if (cursor != head) {
        curr = head->next;
        prev = head;
        while (curr != cursor){
            if (isspace(prev->ch) && !isspace(curr->ch)){
                wordStart = curr;
            }
            prev = curr;
            curr = curr->next;
        }
        cursor = wordStart;
    }
}


bool linkbuffer::isspace(char ch){
    if (ch==' ') return true;
    return false;
}
