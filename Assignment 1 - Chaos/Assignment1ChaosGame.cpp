#include <iostream>
#include "gwindow.h"
#include "gobjects.h"
#include "gevents.h"
#include "console.h"
#include "random.h"
#include "ranlib.h"
using namespace std;


/* GLOBAL VARIABLES */
const double dia = 3.0;



/* FUNCTION PROTOTYPES */




/* MAIN METHOD */
int main(){
    GWindow gw(800, 600);


    // Prompt user to click 3 points by adding a label
    GLabel *label = new GLabel("Please click on 3 random points");
    label->setFont("SansSerif-18");
    double x = (gw.getWidth() - label->getWidth()) / 2;
    double y = (gw.getHeight() - label->getFontAscent());
    gw.add(label, x, y);


    //When user clicks the points, record them into 3 pairs if x and y coordiantes
    int count = 0;
    double x1, x2, x3, y1, y2, y3;
    while (count < 3) {
        GMouseEvent e = waitForEvent(MOUSE_EVENT);
        if (e.getEventType() == MOUSE_CLICKED) {
            if (count == 0){
                x1 = e.getX();
                y1 = e.getY();
            }
            if (count == 1){
                x2 = e.getX();
                y2 = e.getY();
            }
            if (count ==2){
                x3 = e.getX();
                y3 = e.getY();
            }
            count++;
        }
    }
    // Remove the text from screen when the user clicked 3 points
    gw.clear();


    // Draw a triangle
    GLine *line;
    line = new GLine (x1, y1, x2, y2);
    gw.add(line);
    line = new GLine (x2, y2, x3, y3);
    gw.add(line);
    line = new GLine(x3, y3, x1, y1);
    gw.add(line);


    // Randomly choose 1 vertex as the current point and draw a small circle around it
    double xcurr =0.0;
    double ycurr=0.0;
    int current = randomInteger(1,4);
    if (current == 1){
        GOval *oval = new GOval(x1-dia/2, y1-dia/2, dia, dia);
        oval->setFilled(true);
        gw.add(oval);
        xcurr = x1;
        ycurr = y1;
    }
    if (current == 2){
        GOval *oval = new GOval(x2-dia/2, y2-dia/2, dia, dia);
        oval->setFilled(true);
        gw.add(oval);
        xcurr = x2;
        ycurr = y2;
    }
    if (current == 3){
        GOval *oval = new GOval(x3-dia/2, y3-dia/2, dia, dia);
        oval->setFilled(true);
        gw.add(oval);
        xcurr = x3;
        ycurr = y3;
    }


    while(true){

        //randomly choose another vertex and move current point half the distance toward that vertex
        int randomMove = randomInteger(1,4);

        if (randomMove==1){
            xcurr = (xcurr+x1)/2;
            ycurr = (ycurr+y1)/2;
        }
        if (randomMove==2){
            xcurr = (xcurr+x2)/2;
            ycurr = (ycurr+y2)/2;
        }
        if (randomMove==3){
            xcurr = (xcurr+x3)/2;
            ycurr = (ycurr+y3)/2;
        }

        //draw a circle around newly moved current point
        GOval *oval = new GOval(xcurr-dia/2, ycurr-dia/2, dia, dia);
        oval->setFilled(true);
        gw.add(oval);

    }
    return 0;
}



/* FUNCTION DFINITIONS */

