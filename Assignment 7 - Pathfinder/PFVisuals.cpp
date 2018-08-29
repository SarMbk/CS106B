#include "PFVisuals.h"

/* Constructor */
PFVisuals::PFVisuals(){
    gw.setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
}

/* Destructor */
PFVisuals::~PFVisuals(){
}

/* Figure out how to load an image */
void PFVisuals::loadImage(string filename){
    //GBufferedImage *img = new GBufferedImage();
    //img->load(filename);
    //gw.setCanvasSize(1000, 1000);
    //gw.setCanvasSize(img->getWidth(), img->getHeight());
    //gw.add(img, 0, 0);
}


/* PRIVATE METHODS */

/* Helper Function, draws circle and label representing a node on the graphics window */
void PFVisuals::drawFilledCircleLabel(double x, double y, string color, string label){
    GOval *oval = new GOval(x- CIRCLE_RADIUS, y-CIRCLE_RADIUS, 2*CIRCLE_RADIUS, 2*CIRCLE_RADIUS);
    oval->setFilled(true);
    oval->setColor(color);
    oval->setFillColor(color);
    gw.add(oval);
    oval->sendToFront();

    GLabel *cityText = new GLabel(label);
    cityText->setFont("Helvetica");
    cityText->setFontSize(LABEL_FONT_SIZE);
    gw.add(cityText, x, y - CIRCLE_RADIUS);
}


/* Helper Function, draws a line representing an arc on the graphics window */
void PFVisuals::drawLine(double x1, double y1, double x2, double y2, string color, int thicknessFactor){
    GLine* gline = new GLine(x1, y1, x2, y2);
    gline->setColor(color);
    gline->setLineWidth(LINE_WIDTH*thicknessFactor);
    gw.add(gline);

    /* PFVisuals class has a private set of GLine objects called redlines. It is used to quickly remove highlighted paths
     * and trees from the screen. If we are drawing a "red" color line, then it is used for highlighting and we should
     * place that line in the Set<GLine*> redLines */
    if (color=="red") redLines.add(gline);
}


/* PUBLIC METHODS */

/* Pass through all the nodes stored inside an object of class PFGraph provided as an argument; and plot all of them
 * on the graphics window one by one */
void PFVisuals::plotAllNodes(PFGraph &pfg){
    for (nodeT *node : pfg.getNetWorkGraph()->nodes){
        double x = node->x * SCALE_FACTOR;
        double y = gw.getCanvasHeight() - node->y * (SCALE_FACTOR);
        string name = node->name;
        drawFilledCircleLabel(x,y,"BLACK",name);
    }
}


/* Pass through all the arcs stored inside an object of class PFGraph provided as an argument; and plot all of them
 * on the graphics window one by one */
void PFVisuals::plotAllArcs(PFGraph &pfg){
    for (arcT* arc : pfg.getNetWorkGraph()->arcSetForGraphics){
        double x1 = arc->start->x * SCALE_FACTOR;
        double y1 = gw.getCanvasHeight() - arc->start->y * SCALE_FACTOR;
        double x2 = arc->finish->x * SCALE_FACTOR;
        double y2 = gw.getCanvasHeight() - arc->finish->y * SCALE_FACTOR;
        drawLine(x1, y1, x2, y2, "black");
    }
}


/* Pass through all the arcs stored inside the path vector provided as an argument; and plot all of them
 * on the graphics window one by one. Method is used when we want to highlight a discovered shortest path or a minimum spanning tree */
void PFVisuals::highlightPath(Vector<arcT *> &path){
    for (int i=0; i<path.size(); i++){
        double x1 = path[i]->start->x * SCALE_FACTOR;
        double y1 = gw.getCanvasHeight() - path[i]->start->y * SCALE_FACTOR;
        double x2 = path[i]->finish->x * SCALE_FACTOR;
        double y2 = gw.getCanvasHeight() - path[i]->finish->y * SCALE_FACTOR;

        drawLine(x1, y1, x2, y2, "red", 8);
    }
}


/* Removes all redlines representing highlighted paths from the graphics window and from the set storing red lines,
 * Set<GLine*> redLines inside the PFVisuals object */
void PFVisuals::removeRedLines(){
    for (GLine* line : redLines){
        gw.remove(line);
    }
    redLines.clear();
}


/* Removes everithing from the screen and from internal memory of PFVisuals object */
void PFVisuals::reset(){
    gw.clear();
    redLines.clear();
}



