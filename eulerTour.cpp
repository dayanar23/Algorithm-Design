#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

// class that represents the raph
class Graph {

	int vertex; 		// num of vertices
	int edges; 			// num of edges
	list<int> *a_list; 	// adjacency lists of the nodes
	list<int> *euler_t; // euler tour
	list<int> *crossed;	// count the number of cross 
	list<int> *cost;	// cost of the edges
	list<int> *benefit; // benefits of the edges

	// methods of the class
	public:
		
		//constructor
		Graph(int vertex, int edges);

		// add a pair of edges
		void addEdges(int fn, int sn);

		// delete a pair of edges
		void deleteEdges(int fn, int sn);

		// methods of euler tour
		void eulerTour();

		// methods for save euler tour
		void saveTour(int n);

		// add edge on a tour
		void addTour(int fn, int sn);

		// delete edge of a tour
		void deleteTour(int sn, int fn);

		// sum a cross count
		void addCross(int fn);

		// add an edge cost
		void addCost(int ed, int cost);

		// add an edge benefit
		void addBenefit(int ed, int benef);

		// initialize crossed with zeros
		void fillCross();

		// determinate if the nodes of the graphs have even degree
    	bool allEvenDegree();

		// counts the vertices reachable from a node sn
		int countVertex(int sn, bool visited[]);

		// determinate if a edge can be in euler tour
		bool isValidEdge(int fn, int sn);

};

Graph::Graph(int vertex, int edges) { 
		this-> vertex = vertex; 
		this-> edges = edges;
		a_list = new list<int>[vertex];
		euler_t = new list<int>[vertex];
		crossed = new list<int>[1];
		cost = new list<int>[edges];
		benefit = new list<int>[edges];

	}

void Graph::fillCross(){
	for (int i = 0; i < vertex; ++i){
		list<int>::iterator it = crossed[i].begin();
		*it=0;
	}
}

// add an edge
void Graph::addEdges(int fn, int sn) { 
	a_list[fn].push_back(sn);
	a_list[sn].push_back(fn); 
}

// remove and edge (puts value -1)
void Graph::deleteEdges(int fn, int sn){
	list<int>::iterator it1= find( a_list[fn].begin(), a_list[fn].end(), sn);
	*it1 = -1;
	list<int>::iterator it2= find( a_list[sn].begin(), a_list[sn].end(), fn);
	*it2 = -1;
}

// add an tour
void Graph::addTour(int fn, int sn) { 
	euler_t[fn].push_back(sn);
}

// delete a tour
void Graph::deleteTour(int fn, int sn){
	list<int>::iterator it = find(euler_t[fn].begin(), euler_t[fn].end(), sn);
	*it = -1;
}

// add an tour
void Graph::addCross(int fn) { 
	list<int>::iterator it = a_list[fn].begin();
	*it = *it +1;
}

void Graph::addCost(int edge, int ct){
	cost[edge].push_back(ct);
}

void Graph::addBenefit(int edge, int benef){
	benefit[edge].push_back(benef);
}

// calculate the euler tour
void Graph::eulerTour() {
  int n = 0;
  for (int i = 0; i < vertex; i++){
	  	if (a_list[i].size() & 1){
	  	   n = i; 
	  	   break;  
  		}
	}

	saveTour(n);
}

// save the euler tour
void Graph::saveTour(int n){
  list<int>::iterator it, aux;
	for (it = a_list[n].begin(); it != a_list[n].end(); ++it){
		int sn = *it;
		if (sn != -1 && isValidEdge(n, sn)){
			addTour(n,sn);
			aux = crossed[n].begin();
			if(*aux == 2){
				deleteEdges(n, sn);
			}
			else{
				addCross(n);
			}
			saveTour(sn);
		}
	}
}

// determinates if all the nodes have a even degree
bool Graph::allEvenDegree(){
	bool ev = true;
	int i = 0;
    while (ev && i < vertex){
    	if (a_list[i].size() % 2 == 0){
            ev = true;
            i++;
        } else{
        	ev = false;
        }
    }
        
    return ev;
}

// determinate if a vertex can be on euler tour
bool Graph::isValidEdge(int fn, int sn) {
	bool visited[vertex];
	int c = 0; 
	list<int>::iterator it;
	for (it = a_list[fn].begin(); it != a_list[fn].end(); ++it){
		if (*it != -1){
			c++;
		}
	}
	if (c == 1){
		return true;
	}
	
	memset(visited, false, vertex);
	int c1 = countVertex(fn, visited);
	deleteEdges(fn, sn);
	memset(visited, false, vertex);
	int c2 = countVertex(fn, visited);
	addEdges(fn, sn);
	
	return (c1 > c2)? false: true;
}

// count the vertex rechaeble from node n
int Graph::countVertex(int n, bool visited[]) {
	visited[n] = true;
	int c = 1;

	list<int>::iterator it;
	for (it = a_list[n].begin(); it != a_list[n].end(); ++it)
		if (*it != -1 && !visited[*it])
			c += countVertex(*it, visited);

	return c;
}

int main(){


	Graph g1(4,8);
	g1.addEdges(0, 1);
	g1.addEdges(0, 2);
	g1.addEdges(1, 2);
	g1.addEdges(1, 3);
	g1.addEdges(3, 5);
	g1.addEdges(1, 4);
	g1.addEdges(2, 4);
	g1.addEdges(2, 3);
	g1.addEdges(4, 3);
	g1.addEdges(4, 5);
	g1.fillCross();
	g1.eulerTour();


	return 0;

// TODO:
	/*

		hacer una clase Instancia con los nodos requeridos y los que no y lo que falte

	*/

}