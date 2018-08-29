#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
using namespace std;

/* Problem 3

struct bookT{
    string title, author, publisher;
};

Map<string, Vector<bookT*> > byAuthor;
Map<string, Vector<bookT*> > byTitle;
Map<string, Vector<bookT*> > byPublisher;

Vector<bookT*> DickensBooks;
Vector<bookT*> TwainBooks;
Vector<bookT*> DostBooks;


int main() {

    bookT dCop;
    dCop.title = "David Copperfield";
    dCop.publisher = "London Press";
    dCop.author = "Charles Dickens";

    bookT gExp;
    gExp.title = "Great Expectations";
    gExp.publisher = "London Press";
    gExp.author = "Charles Dickens";

    bookT hFinn;
    hFinn.title = "The Adventures of Huckleberry Finn";
    hFinn.publisher = "New York Press";
    hFinn.author = "Mark Twain";

    bookT tSaw;
    tSaw.title = "The Adventures of Tom Sawyer";
    tSaw.publisher = "New York Press";
    tSaw.author = "Mark Twain";

    bookT bKar;
    bKar.title = "Brothers Karamazov";
    bKar.publisher = "Moscow Press";
    bKar.author = "Fyodor Dostoevsky";

    bookT cPun;
    cPun.title = "Crime and Punishment";
    cPun.publisher = "Moscow Press";
    cPun.author = "Fyodor Dostoevsky";

    DickensBooks.add(&dCop);
    DickensBooks.add(&gExp);
    TwainBooks.add(&hFinn);
    TwainBooks.add(&tSaw);
    DostBooks.add(&bKar);
    DostBooks.add(&cPun);


    //cout << &((DickensBooks.get(0))->author) <<endl;

    byAuthor.add( (DickensBooks.get(0))->author, DickensBooks );
    byAuthor.add( (TwainBooks.get(0))->author, TwainBooks );
    byAuthor.add( (DostBooks.get(0))->author, DostBooks );


    while (true){
        string auth = getLine("Enter author: ");
        if (auth=="") break;
        if (byAuthor.containsKey(auth)){
            for (int i=0; i<byAuthor.get(auth).size(); i++){
                cout << auth << ", title: " <<  byAuthor.get(auth).get(i)->title << ", publisher: " <<byAuthor.get(auth).get(i)->publisher << endl;
            }
        }
    }

    return 0;
}
*/


/* Problem 4 */
struct Cell{
    Cell *next;
    int value;
};


Cell *GetCell(Vector <int> vec, int index){
    Cell *newOne = new Cell;
    newOne->value = vec.get(index);
    newOne->next = NULL;
    return newOne;
}


Cell *ConvertToList(Vector <int> &vec){
    Cell *listHead = NULL;
    for (int i=vec.size()-1; i>=0; i--){
        Cell *newOne = GetCell(vec, i);
        newOne->next = listHead;
        listHead = newOne;
    }
    return listHead;
}


void PrintList (Cell *listhead){
    for (Cell *cur = listhead; cur != NULL; cur = cur->next){
        cout << cur->value << " ";
    }
    cout << endl;
}


int SumList (Cell *&listhead){
    int sum = 0;
    for (Cell *cur = listhead; cur != NULL; cur = cur->next){
        sum+=cur->value;
    }
    return sum;
}

void Append (Cell *&listA, Cell *&listB){
    if (listA==NULL || listB==NULL) return;
    if (listA->next==NULL){
        listA->next = listB;
    } else {
        Append(listA->next, listB);
    }
}


int main (){

    Vector<int> vecA {1, 2, 3, 4, 5};
    Vector<int> vecB {6, 7, 8, 9, 0};
    Cell *listA = ConvertToList(vecA);
    Cell *listB = ConvertToList(vecB);
    PrintList(listA);
    cout << SumList(listA) <<endl;
    PrintList(listB);

    Append(listA, listB);
    PrintList(listA);

    cout << SumList(listA) <<endl;

    return 0;
}
