/* This file defines low level data structures that represent set based graphs */

#ifndef GRAPHTYPES_H
#define GRAPHTYPES_H
#include <string>
#include "map.h"
#include "set.h"
using namespace std;

struct  cityT;   /* Forward references to these two types */
struct flightT;     /* that the compiler can recognize them */



/* Type: setGraph
 * This type represents a graph and consists of a set of nodes,
 * a set of arcs, and a map that creates an association between
 * names and nodes */
struct simpleGraph{
    Set<cityT*> nodes;
    Set<flightT*> arcs;
    Map<std::string, cityT*> nodeMap;
};



/* Type: Node
 * This type represents an individual node and consists of the name of the node
 * and the set of arcs from this node */
struct cityT{
    std::string name;
    Set<flightT*> arcs;
};



/* Type: Arc
 * This type represents an individual arc and consists of pointers to the endpoints,
 * along with the cost of traversing the arc */
struct flightT{
    cityT *start;
    cityT *finish;
    double cost;
};



#endif // GRAPHTYPES_H
