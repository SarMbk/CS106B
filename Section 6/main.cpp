#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include "rectangle.h"
#include "car.h"
#include "queue.h"
using namespace std;

struct carT{
    string name;
    int weight;
    int numAirBags;
};


struct recordingT
{
    string title;
    string genre;
    int rating;
};


int cmpCarAirbags(carT one, carT two){
    if (one.numAirBags > two.numAirBags) return 1;
    else if (one.numAirBags < two.numAirBags) return -1;
    return 0;
}


template <typename Type>
int cmpOperator(Type one, Type two ){
    if (one > two) return 1;
    else if (one < two) return -1;
    return 0;
}


template <typename Type>
Type findMax(Vector<Type> &v, int (cmp)(Type one, Type two)= cmpOperator){
    Type max = v[0];
    for (int i=1; i<v.size(); i++){
        if ( cmp(v[i], max)== 1 ) max = v[i];
    }
    return max;
}


bool isBadAnimation(recordingT show){
    return (show.genre=="animation" && show.rating<7);
}

template <typename Type>
void Filter(Queue<Type> &q, bool (predFn)(Type) ){
    int size = q.size();
    for (int i=0; i<size; i++){
        Type current = q.dequeue();
        if (!predFn(current)) {q.enqueue(current);}
    }
}


template <typename Type>
void removeDuplicates(Vector<Type> &v, int (cmp)(Type one, Type two) = cmpOperator){
    int size = v.size();
    for (int i=0; i<v.size()-1; i++){
        for (int j=i+1; j<v.size(); j++){
            if ( cmp(v[i], v[j]) == 0 ) v.remove(j);
        }
    }
}


int cmpAbsolute(int one, int two){
    int absOne = abs(one);
    int absTwo = abs(two);
    if (absOne > absTwo) return 1;
    else if (absOne < absTwo) return -1;
    return 0;
}


int main() {

    Rectangle R (100, 100, 10, 10);
    cout << R.toString() << endl;

    Vector<int> vec {100, 2, 3, 4, 5, 6, 7};
    cout << findMax(vec) << endl;

    carT t; t.name = "toyota"; t.weight = 1000; t.numAirBags = 2;
    carT h; h.name = "honda"; h.weight = 1000; h.numAirBags = 4;
    carT n; n.name = "nissan"; n.weight = 1000; n.numAirBags = 3;
    Vector<carT> allCars {t, h, n};
    cout << "Car with most airbags: " << findMax(allCars, cmpCarAirbags).numAirBags <<  endl;

    recordingT a; a.genre = "animation"; a.rating = 7; a.title = "a";
    recordingT b; b.genre = "animation"; b.rating = 6; b.title = "b";
    recordingT c; c.genre = "animation"; c.rating = 8; c.title = "c";
    Queue<recordingT> myCollection;
    myCollection.enqueue(a); myCollection.enqueue(b); myCollection.enqueue(c);
    Filter(myCollection,isBadAnimation);
    cout << myCollection.dequeue().title << " " << myCollection.dequeue().title << endl;

    Vector<int> problem5a {1, 1, 2, 1, 2, 3, 4, 5, 6, 7, 5, 6, 7, 3, 4};
    removeDuplicates(problem5a);
    cout << problem5a.toString() << endl;

    Vector<int> problem5b {1, -1, -2, -1, -2, -3, 4, 5, 6, 7, -5, -6, -7, -3, -4};
    removeDuplicates(problem5b, cmpAbsolute);
    cout << problem5b.toString() << endl;


    return 0;
}
