#ifndef GRAPHL_H
#define GRAPHL_H

#include <iomanip>
#include "nodedata.h"
#include <climits>

static const int MAXNODES2 = 101;

class GraphL
{
public:
    /*---------------------------------------------------------------------------
     * Constructor and Destructor
    ---------------------------------------------------------------------------*/
    GraphL();
    ~GraphL();

    /*---------------------------------------------------------------------------
    * functions required for the program
    ---------------------------------------------------------------------------*/
    void buildGraph(istream&);
    void displayGraph() const;
    void depthFirstSearch();
private:

    //Node
    struct EdgeNode;

    //struct to define the GraphNode
    struct GraphNode {
        EdgeNode* edgeHead;
        NodeData data;
        bool visited;
    };
    //struct to define the EdgeNode
    struct EdgeNode {
        int adjGraphNode;
        EdgeNode* nextEdge;
    };

    GraphNode adjacentArrayList[MAXNODES2];

    //defines the size of the file
    int size;
    //if the graph has been build before
    bool built;
    /*---------------------------------------------------------------------------
     * InsertEdge:
     * inserts the a edgeNode into the graphNode array
     ---------------------------------------------------------------------------*/
    bool insertEdge(const int, const int);

    /*---------------------------------------------------------------------------
    * empties the array and deletes the edgeNode pointers effectively
    ---------------------------------------------------------------------------*/
    void empty();
    /*---------------------------------------------------------------------------
    *sets the graphNode.visited to false for all of the array up to size
    ---------------------------------------------------------------------------*/
    void setFalse();

    /*---------------------------------------------------------------------------
    * Helper function for DFS
    ---------------------------------------------------------------------------*/
    void dfsHelper(const int);

};
#endif