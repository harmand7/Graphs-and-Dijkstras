//
// Created by Harman Dhunna on 10/27/15.
//

/*---------------------------------------------------------------------------

---------------------------------------------------------------------------*/


#ifndef ASSIGNMENT_3_GRAPHM_H
#define ASSIGNMENT_3_GRAPHM_H


#include "nodedata.h"
#include <iomanip>
#include <sstream>
#include "nodedata.h"
#include <climits>


using namespace std;

static const int MAXNODES = 101;

class GraphM {
public:
    /*---------------------------------------------------------------------------
    Constructors and Destructor
    ---------------------------------------------------------------------------*/
    GraphM();

    ~GraphM();

    void buildGraph(ifstream &infile);

    void findShortestPath();

    void displayAll() const;

    void display(int, int) const;

    void insertEdge(const int, const int, const int);

    /*---------------------------------------------------------------------------
    removeEdge:

    takes in two int, one is the source and the other is destination
    sets the cost matrix to the INT_MAX

    ---------------------------------------------------------------------------*/

    void removeEdge(int, int);

    /*---------------------------------------------------------------------------
    getPathData:

     Takes the source and destination and prints the path data.
    Used for testing.
    ---------------------------------------------------------------------------*/

private:
    struct TableType {
        bool visited;            //whether node is visited or not
        int dist;                //total distance
        int path;                //min distance from the previous node
    };
    NodeData data[MAXNODES];          //data for the graph node
    int C[MAXNODES][MAXNODES];        //Cost Array and adjacency matrix
    int size;                         //Number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];  //Stores visited, total distance, min
                                      // distance from the previous node

    //Used to check if the graph has been built and initialized correctly.
    bool initialized = false;
    //if the graph has been built previously. if true and then it will be
    // reintialized and set to the default values
    bool built = false;


    /*---------------------------------------------------------------------------
     * getPath:
     * gets the path info. which node it is on. Used three integers.
     * int from, int vector, int to.

    ---------------------------------------------------------------------------*/
    void getPath(int, int, int) const;

    /*---------------------------------------------------------------------------
     * displayLine:
     * takes in three integers and one stream objects
     * the stream object is passed by reference so it can update itself
     * int from is the source, int v is the vertex i want to get to, int to is
     * vertex that i want to reach.
    ---------------------------------------------------------------------------*/
    void displayLine(int, int, int, stringstream &) const;

    /*---------------------------------------------------------------------------
     * initializTable: I know its spelled wrong
     * sets the tabeltype matrix to default value
    ---------------------------------------------------------------------------*/
    void initializTable();

    /*---------------------------------------------------------------------------
     * dijkstras:
     * findShortestPath helper
     * three loops
     * the most inner loop sets the dist to each of the node in addition to the
     * previous cost.
     * the loop before gets the shortest distance vertex node sets that edge
     * to true.
    ---------------------------------------------------------------------------*/
    void dijkstras();


    /*---------------------------------------------------------------------------
     * getMinDistance:
     * helper function for dijkstra
     * takes one int, loops thorough all the possible values the source node can
     * have its edges to and then returns teh shortest distance as min
     * and return the node that is the shortest
    ---------------------------------------------------------------------------*/
    int getMinDistance(const int) const;

    /*---------------------------------------------------------------------------
     * emptyTable:
     * sets the TableType and the Cost matrix to default values
     * set built to false
     * sets initialized to false
    ---------------------------------------------------------------------------*/
    void emptyTable();


};


#endif //ASSIGNMENT_3_GRAPHM_H
