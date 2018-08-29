#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <string>
#include "map.h"
#include "set.h"
#include "graphtypes.h"
#include "foreach.h"
#include "queue.h"
#include "mymap.h"
#include "priorityqueue.h"
using namespace std;

/* Function Prototypes */
void printAdjacencyLists(simpleGraph &g);
void initAirlineGraph(simpleGraph &airline);
void addFlight(simpleGraph &airline, string city1, string city2, int miles);
void addNode(simpleGraph &g, string name);
void addArc(simpleGraph &g, cityT *n1, cityT *n2, double cost);
void visitUsingDFS(cityT *node, Set<cityT *> &visited);
void depthFirstSearch(cityT *node);
void breadthFirstSearch(cityT *node);
string pathToString(Vector<flightT *> &path);
double getPathCost(const Vector<flightT *> & path);
Vector<flightT*> findShorterstPath(cityT *start, cityT *finish);




/* Main program */
int main() {
    /* This is the trial of the graph strucutre from the book ch 19 and L23 */
    simpleGraph airline;
    initAirlineGraph(airline);
    printAdjacencyLists(airline);
    depthFirstSearch(airline.nodeMap["San Francisco"]);
    breadthFirstSearch(airline.nodeMap["San Francisco"]);
    cout << endl << endl;

    /* This is the trial of Dijkstra's algorithm from ch19 */
    Vector <flightT*> shortestPath = findShorterstPath(airline.nodeMap["San Francisco"], airline.nodeMap["Boston"]);
    cout << pathToString(shortestPath) << endl << endl;

    /* This is the trial of the myMap class from L24 */
    myMap<int> m;
    m.add("car", 3);
    m.add("car", 4);
    m.add("cat", 5);
    cout << m.getValue("car") <<endl;
    cout << m.getValue("cat") << endl;
    //cout << m.getValue("dog") << endl;

    return 0;
}


/* Function: printAdjacencyLists
 * Usage: printAdjacencyLists(g);
 * Prints out the adjacency list for each city in the graph */
void printAdjacencyLists(simpleGraph &g){
    foreach (cityT *node in g.nodes) {
        cout << node->name << "->";
        bool first = true;
        foreach (flightT *arc in node->arcs) {
            if(!first) cout << ", ";
            cout << arc->finish->name;
            first = false;
        }
        cout << endl;
    }
}


/* Function: initAirlineGraph
 * Usage: initAirlineGraph(airline);
 * Initializes the airline graph to hold the airline data */
void initAirlineGraph(simpleGraph & airline) {
    addNode(airline, "Atlanta");
    addNode(airline, "Boston");
    addNode(airline, "Chicago");
    addNode(airline, "Dallas");
    addNode(airline, "Denver");
    addNode(airline, "Los Angeles");
    addNode(airline, "New York");
    addNode(airline, "Portland");
    addNode(airline, "San Francisco");
    addNode(airline, "Seattle");
    addFlight(airline, "Atlanta", "Chicago", 599);
    addFlight(airline, "Atlanta", "Dallas", 725);
    addFlight(airline, "Atlanta", "New York", 756);
    addFlight(airline, "Boston", "New York", 191);
    addFlight(airline, "Boston", "Seattle", 2489);
    addFlight(airline, "Chicago", "Denver", 907);
    addFlight(airline, "Dallas", "Denver", 650);
    addFlight(airline, "Dallas", "Los Angeles", 1240);
    addFlight(airline, "Dallas", "San Francisco", 1468);
    addFlight(airline, "Denver", "San Francisco", 954);
    addFlight(airline, "Portland", "San Francisco", 550);
    addFlight(airline, "Portland", "Seattle", 130);
}


/* Function: addFlight()
 * Usage: addFlight(airline, city1, city2, miles)
 * Adds an arc in each direction between the cities c1 and c2.
 */
void addFlight(simpleGraph &airline, string city1, string city2, int miles){
    cityT *n1 = airline.nodeMap[city1];
    cityT *n2 = airline.nodeMap[city2];
    addArc(airline, n1, n2, miles);
    addArc(airline, n2, n1, miles);
}


/* Function: addNode
 * Usage: addNode(g, name);
 * Adds a new node with the specified name to the graph */
void addNode(simpleGraph &g, string name){
    cityT *node = new cityT;
    node->name = name;
    g.nodes.add(node);
    g.nodeMap[name] = node;
}


/* Function: addArc
 * Usage: addArc(g, n1, n2, cost);
 * Adds a directed arc to the graph connecting n1 to n2 */
void addArc(simpleGraph &g, cityT *n1, cityT *n2, double cost){
    flightT *arc = new flightT;
    arc->start = n1;
    arc->finish = n2;
    arc->cost = cost;
    g.arcs.add(arc);
    n1->arcs.add(arc);
}



/* Function: depthFirstSearch
 * Usage: depthFirstSearch(node);
 * Initiates a depth-first search beginning at the specified node. Wrapper function for visitUsingDFS */
void depthFirstSearch(cityT *node) {
    Set<cityT *> visited;
    visitUsingDFS(node, visited);
}


/* Function: visitUsingDFS
 * Usage: visitUsingDFS(node, visited);
 * Executes a depth-first search beginning at the specified node that
 * avoids revisiting any nodes in the visited set. */
void visitUsingDFS(cityT *node, Set<cityT*> & visited) {
    if (visited.contains(node)) return;
    visited.add(node);
    cout << node->name <<endl;
    foreach (flightT *arc in node->arcs) {
        visitUsingDFS(arc->finish, visited);
    }
}


/*
* Function: breadthFirstSearch
* Usage: breadthFirstSearch(node);
* --------------------------------
* Initiates a breadth-first search beginning at the specified node.
*/
void breadthFirstSearch(cityT *node) {
    Set<cityT *> visited;
    Queue<cityT *> q;
    q.enqueue(node);
    while (!q.isEmpty()) {
        node = q.dequeue();
        if (!visited.contains(node)) {
            cout << node->name << endl;
            visited.add(node);
            foreach (flightT *arc in node->arcs) {
                q.enqueue(arc->finish);
            }
        }
    }
}



/* Function: findShortestPath
 * Usage: Vector<Arc *> path = findShortestPath(start, finish);
 * ------------------------------------------------------------
 * Finds the shortest path between the nodes start and finish using
 * Dijkstra's algorithm, which keeps track of the shortest paths in
 * a priority queue. The function returns a vector of arcs, which is
 * empty if start and finish are the same node or if no path exists.*/
Vector<flightT*> findShorterstPath(cityT *start, cityT *finish){
    Vector<flightT*> path;
    PriorityQueue<Vector<flightT*> > q;
    Map<string, double> fixed;
    while(start != finish){
        if (!fixed.containsKey(start->name)){
            fixed.put(start->name, getPathCost(path));
            foreach(flightT *arc in start->arcs){
                if (!fixed.containsKey(arc->finish->name)){
                    path.add(arc);
                    q.enqueue(path, getPathCost(path));
                    path.remove(path.size()-1);
                }
            }
        }
        if(q.isEmpty()){
            path.clear();
            return path;
        }
        path = q.dequeue();
        start = path[path.size()-1]->finish;
    }
    return path;
}




/* Function: getPathCost
 * Usage: double cost = getPathCost(path);
 * ---------------------------------------
 * Returns the total cost of the path, which is just the sum of the
 * costs of the arcs.*/
double getPathCost(const Vector<flightT *> & path) {
    double cost = 0;
    foreach (flightT *arc in path) {
        cost += arc->cost;
    }
    return cost;
}


/* Function: pathToString
 * Usage string s = pathToString(path);
 * ---------------------------------------
 * Returns the string containing names of all nodes on the path */
string pathToString(Vector<flightT *> &path){
    string s = "";
    s+=path[0]->start->name;
    foreach (flightT *arc in path) {
        s+= " - " + arc->finish->name;
    }
    return s;
}

