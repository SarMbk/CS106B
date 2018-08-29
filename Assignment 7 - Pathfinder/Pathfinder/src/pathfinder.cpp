/* pathfinder.cpp
 * ---------------
 * A starter file with some starting constants and handy utility routines.
 */
 
#include <iostream>
#include <cmath>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "string.h"
#include "map.h"
#include "set.h"
#include "foreach.h"
#include "queue.h"
#include "priorityqueue.h"
#include "PFVisuals.h"
#include "PFGraph.h"
#include <fstream>
#include "filelib.h"
using namespace std;


/* Wish list:
 * 1. Figure out how to place an image on the background
 * 2. Implement city inputs with mouse clicks. Implement buttons etc.
 * 3. Comment in more detail the Kruskal and Dijkstra methods
 */


/* Function Definitions */

/* Makes sure all the previous data is erased from the graph and visuals internal storage and loads new data from the text file
 * specified by user */
void initGraphAndVisuals(PFVisuals &pathVisuals, PFGraph &pathGraph){
    pathVisuals.reset();
    pathGraph.reset();
    string textFileName = getLine("Enter name of text file to read data from: ");
    ifstream file = pathGraph.openFile(textFileName);
    pathGraph.loadNodesFromFile(file);
    pathGraph.loadArcsFromFile(file);
    pathVisuals.plotAllNodes(pathGraph);
    pathVisuals.plotAllArcs(pathGraph);
}


/* Print introduction */
void printIntro(){
    cout << "This masterful piece of work is a graph extravaganza!" << endl
         << "The main attractions include a lovely visual presentation of the graph" << endl
         << "along with an implementation of Dijkstra's shortest path algorithm and" << endl
         << "the computation of a minimal spanning tree.  Enjoy!" << endl << endl;
}


/* Print user instructions to the console */
void printInstructions(){
    cout << endl << endl;
    cout << "Please enter an integer 1, 2, 3 or 4 for following options: " << endl;
    cout << "(1) Choose a new graph data file" << endl;
    cout << "(2) Find shortest path using Dijkstra's algorithm" << endl;
    cout << "(3) Compute the minimal spanning tree using Kruskal's algorithm" << endl;
    cout << "(4) Quit" << endl;
}


/* Main Method */
int main(){
    /* Declare instances of PFGraph and PFVisuals class */
    PFVisuals pathVisuals;
    PFGraph pathGraph;

    /*Print Introduction and load all data into the pathVisuals and pathGraph objects */
    printIntro();
    initGraphAndVisuals(pathVisuals, pathGraph);

    /* Continously request user input until user chooses to quit */
    int userInput;
    while (userInput!=4){
        printInstructions();
        userInput = getInteger("Enter your choice 1 to 4: ");

        /* 1. Reload all data again from another file */
        if (userInput==1){
            initGraphAndVisuals(pathVisuals, pathGraph);
        }

        /* 2. Run the Dijkstra's shortest path algorithm */
        if (userInput==2){
            cout << endl;

            /* Ensure there is no highlighted paths or trees on the screen and inside the pathVisuals object before beginning */
            pathVisuals.removeRedLines();

            /* Get input from user on what is the starting and destination point */
            nodeT *start = pathGraph.getNodeInput(true);    // for inputting the starting point, provide true as argument
            nodeT *finish = pathGraph.getNodeInput(false);  // for inputing the destination point, provide false as argument
            Vector<arcT*> route = pathGraph.findShortestPath(start, finish);

            /* Run the algorithm and display visually */
            pathGraph.printPathAndCost(route);
            pathVisuals.highlightPath(route);
        }

        /* 3. Run Kruskal's Minimum Spanning Tree algorithm */
        if (userInput==3){
            /* Get a vector of arcs representing the MST */
            Vector <arcT*> MST = pathGraph.findKruskalTree();
            pathGraph.printMSTWeight(MST);  // Print the path to the console

            /* Before displaying the MST tree visually, ensure there is no highlighted paths, or trees remaining on the screen
             * and inside the pathVisuals object, from previous operations. */
            pathVisuals.removeRedLines();
            pathVisuals.highlightPath(MST);
        }

        /* 4. Quit */
        if (userInput==4){
            pathVisuals.removeRedLines();
            pathVisuals.reset();
            pathGraph.reset();
            cout << endl << "Thank you, bye!" << endl;
        }
    }

    return (0);
}









