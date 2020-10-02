#include <malloc.h>
#define NULL 0

class Graph{
	private:
		
		struct E_EDGE {
			int v_origin;
			int v_destination;
			E_EDGE* next;
		};	
		struct LIST {
			int id;
			bool isVisited;
			LIST* next;
		};
		//Edeges and Vertices List
		E_EDGE*   edges   = NULL;
		LIST* vertices    = NULL;
		//output list for our BFS and DFS
		LIST* BFS_VISITED = NULL;
		LIST* DFS_VISITED = NULL;
		//Utility List for stack and Queue
		LIST* stack       = NULL;
		LIST* frontQueue  = NULL;
		LIST* rearQueue   = NULL;
		//utility functions
		void pust_to_stack(int id);
		void pust_to_stack(LIST*& list, int id);
		int pop_from_stack();
		void enQueue(int id);
		void markVisited(LIST*& list, int id);
		void unmarkVisited(LIST*& list);
		int deQueue();
		bool isEdgeExist(int v_origin, int v_destination);
		bool isVertexExist(int node_id);
		bool isVisited(LIST* list, int id);
	public:

		void addVertex(int node_id);
		void addEdge(int v_origin, int v_destination);
		void doBFS(int vertex);
		void doDFS(int vertex);
		void printList(LIST* list);
		void printReverseList(LIST* list);
		void printReverseListE();
		//Test
		void test_STACK();
		void test_QUEUE();
		void test_addVertex();
		void test_addEdge();
};
