#ifndef PATHFINDERGRAPHTYPES_H
#define PATHFINDERGRAPHTYPES_H

#include <string>
#include "map.h"
#include "set.h"
using namespace std;

struct  nodeT;   /* Forward references to these two types */
struct arcT;     /* that the compiler can recognize them */


/* Type: Node
 * This type represents an individual node and consists of the name of the node
 * and the set of arcs from this node */
struct nodeT{
    std::string name;
    double x, y;
    Set<arcT*> arcs;

    // This function is used by set to order elements of cityT.
    bool operator<(const nodeT *node) const{
        return (this->name < node->name);
    }
};


/* Type: Arc
 * This type represents an individual arc and consists of pointers to the endpoints,
 * along with the cost of traversing the arc */
struct arcT{
    nodeT *start;
    nodeT *finish;
    double cost;

    // This function is used by set to order elements of flightT.
    bool operator<(const arcT *arc) const{
        return (this->cost < arc->cost);
    }
};




#endif // PATHFINDERGRAPHTYPES_H
