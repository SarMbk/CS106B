#ifndef PATHFINDERGRAPHICS_H
#define PATHFINDERGRAPHICS_H

#include <iostream>
#include "gwindow.h"
#include "gbufferedimage.h"
#include "PFGraph.h"
using namespace std;


class PFVisuals
{
public:
    /* Constructor and Destructor */
    PFVisuals();
    ~PFVisuals();

    /* Public Methods */
    void loadImage(string filename);
    void plotAllNodes(PFGraph &pfg);
    void plotAllArcs(PFGraph &pfg);
    void highlightPath(Vector<arcT*> &path);
    void reset();
    void removeRedLines();


private:
    /* Constants */
    const double CIRCLE_RADIUS = 3;
    const int LABEL_FONT_SIZE = 9;
    const int SCALE_FACTOR = 120;   // Change the scale factor and if you want the scale of plot to be larger/smaller
    const double LINE_WIDTH = 0.2;  // Width for plotted arcs in the graph
    const int CANVAS_WIDTH = 900;   // Change the canvas height and width and the plot doesn't fit inside the graphics window.
    const int CANVAS_HEIGHT = 600;

    /* Instance Variable for Graphics Window */
    GWindow gw;

    /* Private Set storing highlighted red lines of paths. It is used to quickly remove highlighted red lines without having to redraw
     * all the arcs of a graph each time we are searching a path or an MST tree */
    Set<GLine*> redLines;

    /* Private helper methods */
    void drawFilledCircleLabel(double x, double y, string color, string label = "");
    void drawLine(double x1, double y1, double x2, double y2, string color, int thicknessFactor = 1);
};

#endif // PATHFINDERGRAPHICS_H
