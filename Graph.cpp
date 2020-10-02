#include "Graph.h"
#include <iostream>
using namespace std;

/*This will add vertex to our tracking list of vertices that is point to vertices LIST
 *@node_id the id of vertex
 *@return void
*/ 
void Graph::addVertex(int node_id){
	if(vertices == NULL){
		vertices     = (struct LIST *)malloc(sizeof(struct LIST));
		vertices->id = node_id;
		vertices->next  = NULL;
	}else{
		if(isVertexExist(node_id))
			return;
			
		LIST* temp = (struct LIST *)malloc(sizeof(struct LIST));
		temp->id      = node_id;
		temp->next    = vertices;
		vertices      = temp;
	}
}
/*This will add edges to our graph taht is point to edges LIST
 *@v_origin the origin vertex
 *@v_destination the destination vertex
 *@return void
*/ 
void Graph::addEdge(int v_origin, int v_destination){
	if(edges == NULL){
		
		edges                = (struct E_EDGE *)malloc(sizeof(struct E_EDGE));
		edges->v_origin      = v_origin;
		edges->v_destination = v_destination;
		edges->next          = NULL;
	}else{

		if(isEdgeExist(v_origin, v_destination))
			return;
			
		E_EDGE* temp        = (struct E_EDGE *)malloc(sizeof(struct E_EDGE));
		temp->v_origin      = v_origin;
		temp->v_destination = v_destination;
		temp->next          = edges;
		edges               = temp;
	}
	
	//add reverse of the edges since we assume the graph is undirected graph. So, (X,Y) == (Y,X)
	//this is to guarantee that we will not miss to add the opposite direction edge
	E_EDGE* temp        = (struct E_EDGE *)malloc(sizeof(struct E_EDGE));
	temp->v_origin      = v_destination;
	temp->v_destination = v_origin;
	temp->next          = edges;
	edges               = temp;
	// this will add the vertices origin and destination to our tracking list of vertices pointing to vertices LIST
	if(!isVertexExist(v_origin)){
		addVertex(v_origin);
	}
	if(!isVertexExist(v_destination)){
		addVertex(v_destination);
	}
}
/*utility method to check element to our list if edges exist pointing to edges LIST
 *@node_id the vertex element to check
 *@return void
*/ 
bool Graph::isEdgeExist(int v_origin, int v_destination){
	E_EDGE* temp = edges;
	while(temp){
		if(temp->v_origin == v_origin && temp->v_destination == v_destination)
			return true;
		temp = temp->next;
	}	
	return false;
}
/*utility method to check element to our list if vertex exist pointing to vertices LIST
 *@node_id the vertex element to check
 *@return void
*/ 
bool Graph::isVertexExist(int node_id){
	LIST* temp = vertices;
	while(temp){
		if(temp->id == node_id)
			return true;
		temp = temp->next;
	}
	return false;
}
/*Push method our utility method to push element to our list pointing to stack LIST
 *@id the id element to push
 *@return void
*/ 
void Graph::pust_to_stack(int id){
	if(stack == NULL){
		stack        = (struct LIST *)malloc(sizeof(struct LIST));
		stack->id    = id;
		stack->next  = NULL;
	}else{
		LIST* temp   = (struct LIST *)malloc(sizeof(struct LIST));
		temp->id     = id;
		temp->next   = stack;
		stack        = temp;
	}
}
/*Push overloaded method our utility method to push element to our list
 *@list the list where to push the id element
 *@id the id element to push
 *@return void
*/ 
void Graph::pust_to_stack(LIST*& list, int id){
	if(list == NULL){
		list        = (struct LIST *)malloc(sizeof(struct LIST));
		list->id    = id;
		list->next  = NULL;
	}else{
		LIST* temp  = (struct LIST *)malloc(sizeof(struct LIST));
		temp->id    = id;
		temp->next  = list;
		list        = temp;
	}
}
/*Pop method our utility method to pop element to our list in the stack pointing to stack LIST
 *@return int, the id element
*/ 
int Graph::pop_from_stack(){
	int toReturn = NULL;
	
	if(stack == NULL){
		return toReturn;
	}else{
	    toReturn = stack->id;
	    LIST* temp = stack->next;
	    free(stack);
	    stack = temp;
	}
	return toReturn;
}
/*Enqueue method our utility method to Enqueue element to our list pointing to frontQueue and rearQueue LIST
 *@return void
*/ 
void  Graph::Graph::enQueue(int id){
	if(frontQueue == NULL){
		frontQueue       = (struct LIST *)malloc(sizeof(struct LIST));
      	frontQueue->next = NULL;
      	frontQueue->id   = id;
      	rearQueue        = frontQueue;
	}else{
		LIST* temp       = (struct LIST *)malloc(sizeof(struct LIST));
		rearQueue->next  = temp;
		temp -> id       = id;
		temp -> next     = NULL;
		rearQueue        = temp;
	}
}
/*Dequeue method our utility method to dequeue element to our list pointing to frontQueue LIST
 *@return int, the id element
*/ 
int Graph::deQueue(){
	int toReturn = NULL;
	
	if(frontQueue == NULL){
		return toReturn;
	}else{
		if(frontQueue->next == NULL){
			toReturn = frontQueue->id;
			free(frontQueue);
			frontQueue = NULL;
		}else{
			LIST* temp = frontQueue->next;
			toReturn = frontQueue->id;
			free(frontQueue);
			frontQueue = temp;
		}
	}
	return toReturn;
}
/*This method will set the isVisited data element of our List to true
 *@list the LIST data structure to be set
 *@id the id of the element to be set
 *@return void
*/ 
void Graph::markVisited(LIST*& list, int id){
	LIST* temp = list;
	if(temp == NULL)
		return;
	while(temp){
		if(temp->id == id)
			temp->isVisited = true;
		temp = temp->next;	
	}
}
/*This method will reset and mark the isVisited data element of our List to false
 *@list the LIST to clear out isVisisted element
 *@return void
*/ 
void Graph::unmarkVisited(LIST*& list){
	LIST* temp = list;
	if(temp == NULL)
		return;
	while(temp){
		temp->isVisited = false;
		temp = temp->next;	
	}
}
/*This method will search and check if the isVisited data element of our List is true
 *@list the LIST data structure to be check
 *@id the id of the element to be search
 *@return true if visisted false otherwise
*/ 
bool Graph::isVisited(LIST* list, int id){
	LIST* temp = list;
	if(temp == NULL)
		return false;
	while(temp){
		if(temp->id == id && temp->isVisited == true)
			return true;
		temp = temp->next;		
	}
	return false;
}
/*The main method to traverse our graph  in BREADTH-FIRST-SEARCH algorithm
 * and print out the DFS result list
 *@vertex the vertex to be set as starting point
 *@return void
*/ 
void Graph::doBFS(int vertex){
	//we need to set our vertices to unvisited just to sanitized from previous usage of the LIST
	unmarkVisited(vertices);
	//mark the starting vertex as visited
	markVisited(vertices, vertex);
	//Enqueue the vertex to our stack
	enQueue(vertex);
	
	while(frontQueue){
		//dequeue
		int s = deQueue();
		//push the s to our visited list or result list DFS_VISITED
		pust_to_stack(BFS_VISITED, s);
		//let's find all the adjacent vertices using our edges list
		E_EDGE* temp = edges;
		while(temp){
			//edge = (X,Y)=(Y,X), if X == s and Y = the adjacent vertex is not visited
			//mark as visited and enqueue the vertex 
			if(temp->v_origin == s && !isVisited(vertices, temp->v_destination)){
				markVisited(vertices, temp->v_destination);
				enQueue(temp->v_destination);
			}
			temp = temp->next;
		}
	}
	//print the result list
	cout<<"BFS = ";
	printReverseList(BFS_VISITED);
	cout<<endl;
}
/*The main method to traverse our graph  in DEPTH-FIRST-SEARCH algorithm
 * and print out the DFS result list
 *@vertex the vertex to be set as starting point
 *@return void
*/ 
void Graph::doDFS(int vertex){
	//we need to set our vertices to unvisited just to sanitized from previous usage of the LIST
	unmarkVisited(vertices);
	//mark the starting vertex as visited
	markVisited(vertices, vertex);
	//push the vertex to our stack
	pust_to_stack(vertex);
	
	while(stack){
		//pop the from the stack
		int s = pop_from_stack();
		//push the s to our visited list or result list DFS_VISITED
		pust_to_stack(DFS_VISITED, s);
		//let's find all the adjacent vertices using our edges list
		E_EDGE* temp = edges;
		while(temp){
			//edge = (X,Y)=(Y,X), if X == s and Y = the adjacent vertex is not visited
			//mark as visited and push to our stack the vertex
			if(temp->v_origin == s && !isVisited(vertices, temp->v_destination)){
				markVisited(vertices, temp->v_destination);
				pust_to_stack(temp->v_destination);
			}
			temp = temp->next;
		}
	}
	//print the result list
	cout<<"DFS = ";
	printReverseList(DFS_VISITED);
	cout<<endl;
}
/*Print linkedList in LILO beahavior to be printed
 *@list LIST to be printed out
 *@return void
*/
void  Graph::printList(LIST* list){
	if(list == NULL)
		return;
    cout<<"("<< list->id<<"),";
    printList(list->next);
}
/*overloaded method for PrintList that will take a LIST argument to print
 *@list LIST data structure that will be printed
  *@return void
*/
void  Graph::printReverseList(LIST* list){
	if(list == NULL)
		return;
	printReverseList(list->next);
    cout<<"("<< list->id<<"),";
}
/*Print LinkedList in reverse by default the edges LISt will be printed out
 *@return void
*/
void  Graph::printReverseListE(){
	E_EDGE* temp = edges;
	if(temp == NULL)
		return;
	while(temp){
		cout<<"("<<temp->v_origin<<","<<temp->v_destination<<"),";
		temp = temp-> next;
	}
}
//Test for Stack
void Graph::test_STACK(){
	pust_to_stack(1);
	pust_to_stack(2);
	pust_to_stack(3);
	pust_to_stack(4);
	pust_to_stack(5);
    pust_to_stack(6);
	
	cout<<"i pop ="<<pop_from_stack()<<endl;
	cout<<"i pop ="<<pop_from_stack()<<endl;
	cout<<"i pop ="<<pop_from_stack()<<endl;
	cout<<"i pop ="<<pop_from_stack()<<endl;
	cout<<"i pop ="<<pop_from_stack()<<endl;
	
	pust_to_stack(7);
	pust_to_stack(8);
	cout<<"i pop ="<<pop_from_stack()<<endl;
	cout<<"i pop ="<<pop_from_stack()<<endl;
	cout<<"i pop ="<<pop_from_stack()<<endl;
}
//test for Queue
void Graph::test_QUEUE(){
	enQueue(1);
	enQueue(2);
	enQueue(3);
	enQueue(4);
	enQueue(5);
    enQueue(6);
	
	cout<<"i deQueue ="<<deQueue()<<endl;
	cout<<"i deQueuep ="<<deQueue()<<endl;
	cout<<"i deQueue ="<<deQueue()<<endl;
	cout<<"i deQueue ="<<deQueue()<<endl;
	cout<<"i deQueue ="<<deQueue()<<endl;
	
	enQueue(7);
	enQueue(8);
	cout<<"i deQueue ="<<deQueue()<<endl;
	cout<<"i deQueue ="<<deQueue()<<endl;
	cout<<"i deQueue ="<<deQueue()<<endl;
}
//test for adding vertex
void Graph::test_addVertex(){
	addVertex(1);
	addVertex(2);
	addVertex(3);
	addVertex(4);
	addVertex(5);
	addVertex(6);
	addVertex(7);
	addVertex(8);
	addVertex(9);
	addVertex(10);
	cout<<"Vertices = {";
	printReverseList(vertices);
	cout<<"}"<<endl;
}
//Test for adding Edges
void Graph::test_addEdge(){
	addEdge(1,4);
	addEdge(1,2);
	addEdge(4,3);
	addEdge(3,2);
	addEdge(3,10);
	addEdge(3,9);
	addEdge(2,5);
	addEdge(2,8);
	addEdge(2,7);
	addEdge(5,6);
	addEdge(5,7);
	addEdge(5,8);
	addEdge(7,8);
	cout<<"Edges = {";
	printReverseListE();
	cout<<"}"<<endl;
}
