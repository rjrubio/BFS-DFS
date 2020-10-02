#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Graph.h"

using namespace std;

/*This program will take an input via text file
 *input format of edges is X Y per line in the text file
 *then it will ask to input on the screen the starting vertex to search
 *and do Breadth-first-search and Depth-First-Search traversal
 *then display the result of each traversal
*/
int main(int argc, char** argv) {
	
	Graph graph;
	//tests
	//graph.test_STACK();
	//graph.test_QUEUE();
	//graph.test_addVertex();
	//graph.test_addEdge();
	//graph.doBFS(1);
	//graph.doDFS(1);
	
	//Open our input file and load it to our edges
	//expected input format is X space Y per line
	//X1 Y1
	//X2 Y2
	//.. ..
	//.. ..
 	std::ifstream infile("input.txt");
	std::string line;
	cout<<"Edeges = { ";
	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    int a, b;
	    if (!(iss >> a >> b)) { 
	        cout<<"Error reading input"<<endl;
			break;
		}
		cout<<"("<<a<<","<<b<<"),";
		graph.addEdge(a, b);
	}
	cout<<"}"<<endl;
	
	int node;
	cout<<"Enter starting node : ";
	cin>>node;
	graph.doBFS(node);
	graph.doDFS(node);
	return 0;
}
