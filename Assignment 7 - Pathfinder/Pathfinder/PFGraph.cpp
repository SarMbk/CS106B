#include "PFGraph.h"

/* Constructor */
PFGraph::PFGraph(){
}

/* Destructor */
PFGraph::~PFGraph(){ 
}


/* PRIVATE METHODS */

void PFGraph::addNode(string nodeName, double xCoord, double yCoord){
    nodeT *node = new nodeT;
    node->name = nodeName;
    node->x = xCoord;
    node->y = yCoord;
    networkGraph.nodes.add(node);
    networkGraph.nodeMap.add(node->name, node);
}


void PFGraph :: addArc(nodeT *n1, nodeT *n2, double distance){
    arcT *arc_n1_n2 = new arcT;
    arc_n1_n2->start = n1;
    arc_n1_n2->finish = n2;
    arc_n1_n2->cost = distance;
    networkGraph.arcs.add(arc_n1_n2);
    n1->arcs.add(arc_n1_n2);
}


void PFGraph::addArcForGraphics(nodeT *n1, nodeT *n2, double distance){
    arcT *arc_n1_n2 = new arcT;
    arc_n1_n2->start = n1;
    arc_n1_n2->finish = n2;
    arc_n1_n2->cost = distance;
    networkGraph.arcSetForGraphics.add(arc_n1_n2);
}


double PFGraph::getPathCost(Vector<arcT*> &path){
    double cost = 0;
    for (int i=0; i<path.size(); i++){
        cost+= path[i]->cost;
    }
    return cost;
}


/* PUBLIC METHODS USED ONLY FOR DEBUGGING AND MAINTENANCE */

void PFGraph::printAllNodes(){
    for (nodeT* node : networkGraph.nodes){
        cout << node->name << " x=" << node->x << " y=" << node->y << endl;
    }
}

void PFGraph::printAllArcs(){
    for (arcT* arc : networkGraph.arcs){
        cout << arc->start->name << " - " << arc->finish->name << " cost: "
             << arc->cost << endl;
    }
}

void PFGraph::printAllArcsFrom(string nodeName){
    if (networkGraph.nodeMap.containsKey(nodeName)){
        Set<struct arcT*> :: iterator it;
        for (arcT* arc : networkGraph.nodeMap[nodeName]->arcs){
            cout << arc->start->name << " - " << arc->finish->name << " cost: "
                 << arc->cost << endl;
        }
    }
    else {
        cout << "No such city name in database." <<endl;
    }
}


/* PUBLIC METHODS */

/* Getter method, network graph is a private instance of the classes internal data strucure.
 * This method provides access to it outside the class */
PFGraph:: networkGraphT* PFGraph::getNetWorkGraph(){
    networkGraphT* result = &networkGraph;
    return result;
}


/* Read the names and coordinates of nodes from the text file */
void PFGraph::loadNodesFromFile(ifstream &file){
    string s;

    // Find the keyword "NODES" in text file
    while(s!="NODES"){
        file >> s;
    }
    // Read cities and coordinates into the PFGraph
    file >> s;
    while (s!="ARCS"){
        double xCoord, yCoord;
        file >> xCoord;
        file >> yCoord;
        addNode(s, xCoord, yCoord);
        file >>s;
    }
}


/* Read the arcs and weights from the text file */
void PFGraph::loadArcsFromFile(ifstream &file){
    while (true){
        string node1;
        file >> node1;
        if (file.fail()) break;
        nodeT *n1 = networkGraph.nodeMap[node1]; //Access the pointer to the already loaded node by using the nodeMap

        string node2;
        file >> node2;
        nodeT *n2 = networkGraph.nodeMap[node2];

        double distance;
        file >> distance;

        //cout << n1->name << " - " << n2->name << endl;

        addArc(n1, n2, distance);
        addArc(n2, n1, distance);
        addArcForGraphics(n1, n2, distance);
        /*We add only a one way arc for graphics. When we plot we just pass through the set
         * called arcSetForGraphics inside the networkGraphT structure and plot the arcs without
         * having to write extra code to check arc equality and avoid plotting duplicate arcs */
    }
}


// This function opens a text file and returns an ifstream object
ifstream PFGraph::openFile(string fileName){
    ifstream file;
    while (true){
        file.open(fileName.c_str());
        if(!file.fail()) break;
        cout << "Unable to open file " << fileName << " try another file name: " << endl;
        file.clear();
        fileName = getLine("Enter file name again: ");
    }
    return file;
}


/* Promts user to to enter a string representing the node */
nodeT* PFGraph::getNodeInput(bool isDeparturePoint){
    string keyword = isDeparturePoint ? "departure" : "destination";
    string s = getLine("Please enter the " + keyword + " point name: ");
    while(!networkGraph.nodeMap.containsKey(s)){
        s = getLine("No location named " + s + " in the network. Please enter the "
                    + keyword + " point name again: ");
    }
    return networkGraph.nodeMap[s];
}


/* Implementation of Dujkstra's shortest path algorithm */
Vector<arcT*> PFGraph::findShortestPath(nodeT *start, nodeT *finish){
    Vector<arcT*> path;
    PriorityQueue < Vector<arcT*> > pq;
    Map<string, int> fixed;
    while (start != finish){
        if(!fixed.containsKey(start->name)){
            fixed.put(start->name, getPathCost(path));
            for (arcT *arc : start->arcs){
                if(!fixed.containsKey(arc->finish->name)){
                    path.add(arc);
                    pq.enqueue(path, getPathCost(path));
                    path.remove(path.size()-1);
                }
            }
        }
        if(pq.isEmpty()){
            path.clear();
            return path;
        }
        path = pq.dequeue();
        start = path[path.size()-1]->finish;
    }
    return path;
}


/* Prints the path to the console and the total cost */
void PFGraph::printPathAndCost(Vector<arcT *> &path){
    double cost = 0;
    for (int i=0; i<path.size(); i++){
        if (i==0){ cout << path[i]->start->name << " - "; }
        if (i==path.size()-1){ cout << path[i]->finish->name << endl; }
        else { cout << path[i]->finish->name << " - "; }
        cost+=path[i]->cost;
    }
    cout << "Total path mileage: " + doubleToString(cost) << endl;
}


/* Remove all entries from internal memory, and internal instance variables */
void PFGraph::reset(){
    networkGraph.arcs.clear();
    networkGraph.nodes.clear();
    networkGraph.nodeMap.clear();
    networkGraph.arcSetForGraphics.clear();
}


/* Implementation of Kruskal's MST algorithm */
Vector<arcT*> PFGraph::findKruskalTree(){
    PriorityQueue <arcT*> arcsPQ;
    Vector <arcT *> MST;

    /* Put all arcs into a priority queue */
    for (arcT *arc : networkGraph.arcs){
        arcsPQ.enqueue(arc, arc->cost);
    }


    Map <string, Set< nodeT* > > nodesAndConxMap;
    for (nodeT *node : networkGraph.nodes){
        Set <nodeT*> connectedNodes;
        connectedNodes.add(node);
        nodesAndConxMap.put(node->name, connectedNodes);
    }

    while(!arcsPQ.isEmpty()){
        arcT *arc = arcsPQ.dequeue();
        Set <nodeT*> arcStartConx = nodesAndConxMap.get(arc->start->name);
        Set <nodeT*> arcFinishConx = nodesAndConxMap.get(arc->finish->name);
        if(!arcStartConx.contains(arc->finish)){
            Set<nodeT*> mergedConx = arcStartConx + arcFinishConx;
            for (nodeT *node : mergedConx){
                Set<nodeT*> connectedNodes = nodesAndConxMap.get(node->name);
                connectedNodes+=mergedConx;
                nodesAndConxMap.put(node->name, connectedNodes);
            }
            MST.add(arc);
        }
    }
    return MST;
}


/* Prints the arcs of the MST and the resultant cost */
void PFGraph::printMSTWeight(Vector<arcT *> &MST){
    double cost = 0;
    cout << "Minimum Spanning Tree: " << endl;
    for (arcT *arc : MST){
        cout << arc->start->name << " - " << arc->finish->name << endl;
        cost+=arc->cost;
    }
    cout << "Total MST weight: " + doubleToString(cost) << endl;
}


