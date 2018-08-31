#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
using namespace std;

struct pointT {
    int lattitude, longitude;
};

struct cityT{
    string name;
    pointT coordinates;
};

int main(){

    //lets populate the vector with some cities
    pointT ny; ny.lattitude = 41; ny.longitude =71;
    pointT sf; sf.lattitude = 38; sf.longitude = 122;
    pointT dc; dc.lattitude = 39; dc.longitude = 77;

    cityT NY; NY.name = "New York"; NY.coordinates = ny;
    cityT SF; SF.name = "San Francisco"; SF.coordinates = sf;
    cityT DC; DC.name = "Washington DC"; DC.coordinates = dc;

    Vector<cityT> cities;
    cities.add(NY); cities.add(SF); cities.add(DC);


    // Now lets create the map of cities and copy data from vector to map
    map<string, cityT> cityCoords;
    for (Vector<cityT>::iterator it = cities.begin(); it != cities.end(); it++) {
        cityCoords.emplace( (*it).name, *it);
    }

    // Now lets print the map to see if all is good
    for (map<string, cityT>::iterator it = cityCoords.begin(); it!=cityCoords.end(); it++){
        cout << "City Name: " << it->first << "; lattitude: " << it->second.coordinates.lattitude
             << "; longitude: " << it->second.coordinates.longitude << endl;

    }

    return 0;
}

