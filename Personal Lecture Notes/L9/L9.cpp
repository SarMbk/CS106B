
#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gobjects.h"
using namespace std;

// More recursion


GWindow gw(800, 600);


void drawTriangle ( double x, double y, double w, double h ){
    GLine* line1 = new GLine(x, y, x+w/2, y-h);
    GLine* line2 = new GLine(x, y, x+w, y);
    GLine* line3 = new GLine(x+w/2, y-h, x+w, y);
    gw.add(line1);
    gw.add(line2);
    gw.add(line3);
}

// Serpinski triangle
void DrawFractal( double x, double y, double w, double h){
    //drawTriangle(x,y,w,h);
    if (w<2.5 || h<2.5) return;
    double halfH = h/2;
    double halfW = w/2;
    DrawFractal(x+halfW/2, y-halfH, halfW, halfH); // top
    DrawFractal(x, y, halfW, halfH); // bottom left
    DrawFractal(x+halfW, y, halfW, halfH); // bottom right
    drawTriangle(x,y,w,h);
}


void drawRectangle(double x, double y, double w, double h, int color){
    GRect *rect = new GRect(x, y, w, h);
    rect->setFillColor(color);
    rect->setFilled(randomBool());
    gw.add(rect);
}


void DrawBlackLine(double x1, double y1, double x2, double y2){
    GLine* line = new GLine(x1, y1, x2, y2);
    line->setLineWidth(8.0);
    gw.add(line);
}


// Mondrian art
void DrawMondrian(double x, double y, double w, double h){
    if (w<5 || h<5) return;

    drawRectangle(x,y,w,h, randomColor());

    switch ( randomInteger(0,2) ) {

        case 0: // do nothing
            break;
        case 1: // bisect verically
            {
            double midX = randomReal(0,w);
            DrawBlackLine(x+midX, y , x+midX, y+h);
            DrawMondrian(x,y,midX,h);
            DrawMondrian(x+midX, y , w-midX, h);
            break;
            }
        case 2: // bisect horizontaly
            {
            double midY = randomReal(0,h);
            DrawBlackLine(x, y+midY, x+w, y+midY);
            DrawMondrian(x, y, w, midY);
            DrawMondrian(x, y+midY, w, h+midY);
            break;
            }
        default:
            break;
    }
}



// Recursive permutation
/* initially the soFar string is empty, rest string is the whole string you want to permutate
 */
void RecPermute(string soFar, string rest){
    if (rest == ""){
        cout << soFar << endl;
    } else{
        for (int i=0; i<rest.length(); i++){
            string next = soFar+rest[i];
            string remaining = rest.substr(0,i)+rest.substr(i+1);
            RecPermute(next, remaining);
        }
    }
}



void recSubsets(string soFar, string rest){
    if(rest==""){
        cout << soFar << endl;
    }
    else {
        //add to subset, remove from rest, recur
        recSubsets(soFar+rest[0], rest.substr(1));

        // dont add to subset, remove from rest recur
        recSubsets(soFar, rest.substr(1));
    }
}





// RecPermute wrapper function
void ListPermutations (string s){
    RecPermute("",s);
}


vector<int> testFunction(){
    vector<int> vec {1,2,3};
    return vec;
}


int main(){
    //DrawFractal(10,590,700,500);
    //DrawMondrian(100,100,400,400);
    //drawRectangle(0,0,100,100,3);

    //ListPermutations("ABCD");

    vector <int> v = testFunction();
    cout << v[0] << v[1] << v[2] << endl;


    return 0;
}

