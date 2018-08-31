#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

GWindow gw(1200, 600);

void DrawRuler (double x, double y, double w, double h){
    if (h<5) {
        GLine* bottLine = new GLine(x,y, x+w/2, y);
        gw.add(bottLine);
    }
    else{
        GLine* bottLine = new GLine(x,y, x+w/2, y);
        GLine* tick = new GLine (x+w/2, y, x+w/2, y-h);
        gw.add(tick); gw.add(bottLine);
        DrawRuler(x, y, w/2, h/2);
        DrawRuler(x+w/2, y, w/2, h/2);
    }
}

int main(){
    DrawRuler(50, 500, 1000, 400);
    return 0;
}

