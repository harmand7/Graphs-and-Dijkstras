#include "graphl.h"

/*-------------------------------------------------------------------------------
 * Default Constructor Modified:
 * GraphL:
 * sets size to 0
 * built to false
 * runs through the loop of adjacentArrayList and sets the edge to NULL
 *-----------------------------------------------------------------------------*/
GraphL::GraphL()
{
    size = 0;
    built = false;
    for (int i = 0; i < MAXNODES2; i++)
    {
        adjacentArrayList[i].edgeHead = NULL;
    }
}
/*-------------------------------------------------------------------------------
 * Default Destructor Modified:
 * calls the helper function makeEmpty
 *-----------------------------------------------------------------------------*/
GraphL::~GraphL()
{
    empty();
}
/*-------------------------------------------------------------------------------
 * empty:
 * deletes the EdgeNodes from the list
 *
 * checks if the size is zero
 * Runs through two loops.
 * Inner Loop, runs the loop in pre-order traversal
 * deletes the node and checks the next time if it not null
 *-----------------------------------------------------------------------------*/
void GraphL::empty()
{
    if (size == 0)
    {
        return;
    }
    for (int i = 1; i <= size; i++)
    {
        while (adjacentArrayList[i].edgeHead != NULL)
        {
            EdgeNode* current = adjacentArrayList[i].edgeHead;

            if (current != NULL)
            {
                EdgeNode* temp = current;
                current = current->nextEdge;
                delete temp;
                temp = NULL;
                adjacentArrayList[i].edgeHead = current;
            }
        }
        adjacentArrayList[i].data = NodeData("");
    }
    size = 0;
    return;
}

/*-------------------------------------------------------------------------------
 * buildGraph:
 * if the size is more than zero than clear out the array
 * if it is the end of the file then return and end the function
 * get line from the file
 * run through the adjacentArrayList and sets the data from the file
 *
 * loops through till it hits zero.
 * if those are vaild indexes then the insert the edge
 *-----------------------------------------------------------------------------*/
void GraphL::buildGraph(istream& infile)
{
    int fromNode, toNode;
    if (size > 0)
    {
        empty();
    }

    built = true;
    infile >> size;
    if (infile.eof()) return;

    string a;
    getline(infile, a);

    for (int i = 1; i <= size; i++)
    {
        adjacentArrayList[i].data.setData(infile);
    }

    infile >> fromNode >> toNode;
    while(fromNode != 0 && toNode != 0)
    {
        if (fromNode > 0 && fromNode <= size && toNode > 0 && toNode <= size)
        {
            insertEdge(fromNode, toNode);
        }
        infile >> fromNode >> toNode;
    }
}

/*-------------------------------------------------------------------------------
 * insertEdge:
 * takes in two integers; from and to
 * if the edgeHead is NULL then create an new node,
 * other wise create another insert edgenode using a pointer.
 *
 *-----------------------------------------------------------------------------*/
bool GraphL::insertEdge(const int from, const int to)
{
    if (adjacentArrayList[from].edgeHead == NULL)
    {
        adjacentArrayList[from].edgeHead = new EdgeNode;
        adjacentArrayList[from].edgeHead->adjGraphNode = to;
        adjacentArrayList[from].edgeHead->nextEdge = NULL;
        return true;
    }
    else
    {
        EdgeNode*insert = adjacentArrayList[from].edgeHead;
        adjacentArrayList[from].edgeHead = new EdgeNode;
        adjacentArrayList[from].edgeHead->adjGraphNode = to;
        adjacentArrayList[from].edgeHead->nextEdge = insert;
        insert = NULL;
        return true;
    }
}

/*-------------------------------------------------------------------------------
 * displayGraph:
 * header
 * loop to go through all nodes
 * Sub header
 * while current is not NULL
 * sub header
 * prints the source index to show which path it is following and the data
 * from that.
 * then moves current
 *-----------------------------------------------------------------------------*/
void GraphL::displayGraph() const
{
    cout << "Graph:"<<endl;
    for (int source = 1; source <= size; source++)
    {
        cout << "Node " << source << "        " << adjacentArrayList[source].data << endl;
        EdgeNode* current = adjacentArrayList[source].edgeHead;
        while (current != NULL)
        {
            cout << "    " << "edge " << source << setw(2)
            << current->adjGraphNode << endl;

            current = current->nextEdge;
        }
        current = NULL;
    }
}

/*-------------------------------------------------------------------------------
 * depthFirstSearch
 * resets the adjacentMatrix to false
 * header
 * loop
 * if the node is not visited then go and do the helper function
 *-----------------------------------------------------------------------------*/
void GraphL::depthFirstSearch()
{
    setFalse();
    cout << endl <<"Depth-first ordering:";

     for (int vertex = 1; vertex <= size; vertex++)
    {
        if (adjacentArrayList[vertex].visited == false)
        {
            dfsHelper(vertex);
        }
    }
    cout << endl;
}

/*-------------------------------------------------------------------------------
 * DFSHELPER:
 * sets the vertex.visited to true;
 * prints the vertex that it is on
 * sets the current node to adjacentArrayList[node passed in]
 * creates adjacentNode integers
 * while current is not null keep traversing through the array
 * sets teh adjacent Node to current value
 * if it is not visited then helper function with the new value passed in.
 *-----------------------------------------------------------------------------*/
void GraphL::dfsHelper(const int vertex)
{

    adjacentArrayList[vertex].visited = true;

    cout << " " << vertex;

    EdgeNode* current = adjacentArrayList[vertex].edgeHead;
    int adjacentNode;
    while (current != NULL)
    {
        adjacentNode = current->adjGraphNode;
        if (adjacentArrayList[adjacentNode].visited == false)
        {
            dfsHelper(adjacentNode);
        }
        current = current->nextEdge;
    }
}

/*-------------------------------------------------------------------------------
 * setFalse:
 * sets the AdjacentArrayList to all false.
 *-----------------------------------------------------------------------------*/
void GraphL::setFalse()
{
    for (int vertex = 1; vertex <= size; vertex++)
    {
        adjacentArrayList[vertex].visited = false;
    }
}

