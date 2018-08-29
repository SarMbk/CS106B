#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include <cmath>
using namespace std;


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
    cout << "hello" <<endl;

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


    /*
    while (true){
        string auth = getLine("Enter author: ");
        if (auth=="") break;
        if (byAuthor.containsKey(auth)){
            for (int i=0; i<byAuthor.get(auth).size(); i++){
                cout << auth << ", title: " <<  byAuthor.get(auth).get(i)->title << ", publisher: " <<byAuthor.get(auth).get(i)->publisher << endl;
            }
        }
    }
    */






    double annGrth = 1.10;
    double wkGrth = pow(annGrth, 1.0/52);
    cout << wkGrth <<endl;
    double weeklyContribution = 200;
    double sum = 100;
    int yrs = 20;

    for (int i=0; i<yrs; i++){
        for (int j=0; j<52; j++){
            cout << sum << " year:" << i << " week: " << j << endl;
            sum*=wkGrth;
            sum+=weeklyContribution;
            cout << sum<< " year:" << i << endl;
        }
    }

    cout << sum << endl;
    cout << weeklyContribution*yrs*52 <<endl;
    return 0;
}
