#ifndef MYPATHFINDERGRAPH_H
#define MYPATHFINDERGRAPH_H

#include <iostream>
#include "map.h"
#include "set.h"
#include "PFGraphTypes.h"
#include <fstream>
#include "simpio.h"
#include "priorityqueue.h"
#include "foreach.h"
using namespace std;



class PFGraph
{
    struct networkGraphT; // forward Declaration for the structure so the compiler recongnized it in the getNetWorkGraph() method

public:
    /* Constructor and Destructor */
    PFGraph();
    ~PFGraph();

    /* Public Methods */
    ifstream openFile(string fileName);
    void loadNodesFromFile(ifstream &file);
    void loadArcsFromFile(ifstream &file);
    nodeT *getNodeInput(bool isDeparturePoint); /* If you want to enter a start point provide true as argument,
                                                   for finish point provide false as argument */
    Vector<arcT*> findShortestPath(nodeT *start, nodeT *finish);
    Vector<arcT*> findKruskalTree();
    void printPathAndCost(Vector <arcT*> &path);
    void printMSTWeight(Vector<arcT *> &MST);
    networkGraphT* getNetWorkGraph();
    void reset();

    /* Methods used for debugging made public for ease of access. Not Used in the final implementation */
    void printAllArcsFrom(string nodeName);
    void printAllArcs();
    void printAllNodes();

private:

    /* Data structure representing the graph */
    struct networkGraphT{
        Set<nodeT*> nodes;
        Set<arcT*> arcs;
        Map<std::string, nodeT*> nodeMap;
        Set<arcT*> arcSetForGraphics;
    };

    /* Private instance of graph */
    networkGraphT networkGraph;

    /* Private helper methods */
    void addNode(string nodeName, double xCoord, double yCoord);
    void addArc(nodeT *n1, nodeT *n2, double distance);
    void addArcForGraphics(nodeT *n1, nodeT *n2, double distance);
    double getPathCost(Vector<arcT*> &path);
};


#endif // MYPATHFINDERGRAPH_H
