//
// Created by Harman Dhunna on 10/27/15.
//

#include "graphm.h"

using namespace std;

/*------------------------------------------------------------------------------
 * Default Constructor Modified:
 * GraphM:
 * Sets the size to zero
 * sets the array to default values
 * sets initialize to true
------------------------------------------------------------------------------*/
GraphM::GraphM()
{
	size = 0;
	initialized=true;
	built =false;
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
			if(i==j)
			{
				C[i][j] = 0;
			}
			else
			{
				C[i][j]=INT_MAX;
			}
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
}

/*------------------------------------------------------------------------------
 * Default Destructor:
 * GraphM:
 * Does nothing since no memory is allocated dynamically
-------------------------------------------------------------------------------*/
GraphM::~GraphM()
{
}

/*------------------------------------------------------------------------------
 * buildGraph:
 * takes in a infile
 * checks if the graph has previously been built, if not then empty the table
 * to clear its data
 * check if the size is correct value, checks if the array is big enough,
 * check if the file is not at its end
 * runs thorough a loop to set the data array to to the string value from the
 * file.
 * Reads the first line
 * Then goes to while loop that checks if the node value's are zero or the
 * cost is zero
-------------------------------------------------------------------------------*/
void GraphM::buildGraph(ifstream &infile)
{

	if(built == false)
	{
		emptyTable();
	}
	built =true;

	int source = 0,destination=0,cost=0;
	infile>>size;

	if(size > MAXNODES || size <= 0 || infile.eof())
	{
		return;
	}
	string a;
	getline(infile,a);

	for(int i =1;i<=size;i++)
	{
		data[i].setData(infile);
	}
	initialized=true;

	infile>>source>>destination>>cost;
	while(source !=0||destination!=0||cost!=0)
	{
		insertEdge(source, destination,cost);
		infile>>source>>destination>>cost;
	}
	initialized=true;
}

/*-------------------------------------------------------------------------------
 * insertEdge:
 * has an if statement that checks if the source, destination, cost are all
 * the vaild. Then sets the cost to the correct cost passed in value form the
 * file, to be initialized.
-------------------------------------------------------------------------------*/
void GraphM::insertEdge(const int source, const int destination, const int cost)
{

	if (source >= 1
		&& source <= size
		&& destination >= 1
		&& destination <= size
		&& cost >= 0
		&& cost <= INT_MAX)
	{
		initialized=false;
		built =true;
		C[source][destination] = cost;
	}
}

/*-------------------------------------------------------------------------------
     * emptyTable:
     * sets the TableType and the Cost matrix to default values
     * set built to false
     * sets initialized to false
-------------------------------------------------------------------------------*/
void GraphM::emptyTable()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].dist = INT_MAX; //predefined c++ max integer
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
	initialized = false;
	built = false;
}

/*-------------------------------------------------------------------------------
 * RemoveEdge:
 * Takes two integers source and destination.
 * checks if the source and destination passed in are vaild values
 * Sets the Cost matrix indexed at source and destination to INT_MAX
 *-----------------------------------------------------------------------------*/
void GraphM::removeEdge(int source, int destination)
{
	if (source > 0 &&
			destination > 0 &&
		source < MAXNODES &&
		destination < MAXNODES)
	{
		C[source][destination] = INT_MAX;
		initialized = false;
	}
}

/*-------------------------------------------------------------------------------
 * If the TableType is not built then return and no print to the console.
 * check if the values passed are correct
 * Prints the Source then space then destination
 * then checks if the matrix at that index is not INT_MAX if it is, then it
 * prints blanks. Other wise it prints the out put using the helper function
 * displayLine.
 *-----------------------------------------------------------------------------*/
void GraphM::display(const int from, const int to)const
{
	if(built == false)
	{
		return;
	}
	if(from<=0||from>size||to<=0||to>size)
	{
		return;
	}
	else
	{
		cout << setw(5) << from << setw(5) << to << setw(5);
		if (T[from][to].dist == INT_MAX) //There is a path
		{
			cout << setw(10) << "----" << endl;
			return;
		}
		else
		{
			cout << T[from][to].dist << setw(5);
			stringstream a;
			displayLine(from, to, to, a);
			cout << a.str() << endl;
		}
		cout<<endl;
	}
}

/*-------------------------------------------------------------------------------
 * displayLine:
 * Recursive node to print the data of the node.
 *-----------------------------------------------------------------------------*/
void GraphM::displayLine(int from, int v, int to, stringstream& s) const
{
	int vertex = 0;
	if (v == from)
	{
		cout << v << setw(2);
		s << endl;
		s << data[v];
		return;
	}
	else
	{
		vertex = T[from][v].path;
		displayLine(from, vertex, to, s);
		cout << v << setw(2);
		s << endl;
		s << data[v];
	}
}

/*-------------------------------------------------------------------------------
 * getPath:
 * recursive functions
 * returns the path info using three integers
 *-----------------------------------------------------------------------------*/
void GraphM::getPath( int from, int v,int to ) const
{
	if(built == false)
	{ return;}
	int vertext =0;
	if(v == from)
	{
		cout<<v;
		return;
	} else
	{
		vertext = T[from][v].path;
		getPath(from,vertext,to);
		cout<<setw(2)<<v;
	}

}

/*-------------------------------------------------------------------------------
 * Runs through two loop of the data for all nodes.
 * Prints the header of teh data
 * Prints the data at the first node, the name of the node
 * second loop:
 *
 * goes through the TableType matrix, then checks if the data is not INT_MAX
 * if it is INT_MAX then it prints ---
 * if it is not INT_MAX then it checks the path, if it is zero then print ths
 * node info. which is just the first node
 * else it prints the through a helper functions getPath.
 *-----------------------------------------------------------------------------*/
void GraphM::displayAll() const
{
	if (built==false)
	{
		return;
	}
	//Header
	cout << "Description              From Node    To Node    Dijikstra's    ";
	cout << "Path" << endl;
	for (int i = 1; i <= size; i++) {
		cout << data[i] << endl;
		for (int j = 1; j <= size; j++) {
			if (i != j) {
				cout << setw(33) << i;
				cout << setw(10) << j;
				if (T[i][j].dist == INT_MAX) {
					cout << setw(12) << "----";
					cout << endl;
				}
				else
				{
					if (T[i][j].path == 0) {
						cout << T[i][j].path;
					}
					else
					{
						cout << setw(12) << T[i][j].dist << setw(10);
						getPath(i, j, j);
						cout << endl;
					}
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------------
 * findShortestPath:
 * finds the shortest path to get to all node
 * uses two to helper functions.
 * initialzTable and dijkstras
 *-----------------------------------------------------------------------------*/
void GraphM::findShortestPath()
{
	if(!built)
	{
		return;
	}
	if(!initialized && built)
	{
		initializTable();
		dijkstras();
	}
	if(initialized && built)
	{dijkstras();}

}
/*-------------------------------------------------------------------------------
 * initializTable:
 * sets the table to default values and sets the boolean initialize to true
 *-----------------------------------------------------------------------------*/
void GraphM::initializTable()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		//col loop controls the column loop of the T matrix
		for (int j = 0; j < MAXNODES; j++)
		{
			T[i][j].dist = INT_MAX;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
	initialized = true;
}

/*-------------------------------------------------------------------------------
 * dikstras:
 * three loops:
 * starting with inner most loop
 * checks if the adjacent node is visited and if there cost value is INT_MAX
 * then checks if the value of the sum of cost matrix and tableType matrix.
 * When visited the node in the TableType matrix is turned to visited.
 * middle loop runs and getsMinDistance
 * last loop is responsible for setting all values of that from source to
 * source to zero
 *-----------------------------------------------------------------------------*/
void GraphM::dijkstras()
{
	for(int source =1; source <=size;source++)
	{
		T[source][source].dist=0;
		for(int i = 1; i<size;i++)
		{
			int v= getMinDistance(source);
			if(v!=-1)
			{
				T[source][v].visited=true;
				for(int w=1;w<=size;w++)
				{
					if(T[source][w].visited== false&&C[v][w] !=INT_MAX)
					{
						if(T[source][v].dist+C[v][w]<T[source][w].dist)
						{
							T[source][w].dist = T[source][v].dist + C[v][w];
							T[source][w].path = v;
						}
					}
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------------
 * getMinDistance:
 * runs through the loop getting the path of each adjacent node and finding
 * the smallest node value
 *-----------------------------------------------------------------------------*/
int GraphM::getMinDistance(const int source) const
{
	int v=-1;
	int min= INT_MAX;
	for(int i = 1;i<=size;i++)
	{
		if (T[source][i].dist < min && T[source][i].visited == false)
		{
			min = T[source][i].dist;
			v = i;
		}
	}
	return v;
}


