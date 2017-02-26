#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;


class Edge{

	public:
	
	int n1;
	int n2;
	int cost;
	int benef;
	bool crossed;

	Edge(int n1, int n2, int c, int b){
		this->n1 = n1;
		this->n2 = n2;
		this->cost = c;
		this->benef = b;
		this->crossed =false;
	}

	bool operator==(const Edge &e1) const {
		return n1 == e1.n1 && n2 == e1.n2 &&
				cost == e1.cost && benef == e1.benef
				&& crossed == e1.crossed;
	}

	int getBenefit(){
		if(!crossed){
			return benef-cost;
		}
		return benef-2*cost;
	}

};

void printEd(std::vector<Edge> v);
bool minCost(Edge edge);
// class that represents the raph
class Graph {

	// methods of the class
	public:

	int vertex; 		// num of vertices
	int edges; 			// num of edges
	bool deposit;
	vector<Edge> a_list; 	// adjacency lists of the nodes
	vector<Edge> euler_t; // euler tour
	bool visited[];
		//constructor
		Graph(int vertex, int edges, vector<Edge> &es);

		// add a pair of edges
		void addEdges(Edge edge);

		// delete a pair of edges
		void deleteEdges(Edge edge);

		// methods of euler tour
		void eulerTour();

		// methods for save euler tour
		void saveTour(int n);

		// add edge on a tour
		void addTour(Edge edge);

		// delete edge of a tour
		void deleteTour(Edge edge);

		// sum a cross count
		void addCross(Edge edge);

		int countEdges(Edge edge);

		int countBenefit(vector<Edge> tour);

		// determinate if the nodes of the graphs have even degree
    	bool allEvenDegree();

		// counts the vertices reachable from a node sn
		int countVertex(int n, bool visited[]);

		// determinate if a edge can be in euler tour
		bool isValidEdge(Edge egde);

		bool minCost(Edge edge);

		void markVisited(Edge edge);

};

Graph::Graph(int vertex, int edges, vector<Edge> &eds) { 
		this-> vertex = vertex; 
		this-> edges = edges;
		this-> a_list = eds;
		this-> deposit = false;
	}

// add an edge
void Graph::addEdges(Edge edge) { 
	a_list.push_back(edge); 
}

// remove and edge
void Graph::deleteEdges(Edge edge){
	vector<Edge>::iterator it = find(a_list.begin(), a_list.end(), edge);
	a_list.erase(it);
}

// add an tour
void Graph::addTour(Edge edge) { 
	euler_t.push_back(edge);
}

// delete a tour
void Graph::deleteTour(Edge edge){
	vector<Edge>::iterator it = find(euler_t.begin(), euler_t.end(), edge);
	euler_t.erase(it);
}

// add an tour
void Graph::addCross(Edge edge){ 
	Edge aux = edge;
	aux.crossed = aux.crossed +1;
	vector<Edge>::iterator it = find(a_list.begin(), a_list.end(), edge);
	a_list.erase(it);
	a_list.insert(it, aux);
}

// calculate the euler tour
void Graph::eulerTour() {
  int n = 0;
  for (int i = 0; i < edges; i++){
	  	if (countEdges(a_list[i]) % 2 == 0){
	  	   n = i; 
	  	   break;  
  		}
	}
		saveTour(n);
	
}

// save the euler tour
void Graph::saveTour(int n){

	//cout<< n<< endl;
  int aux;
	for (int i=0; i< a_list.size(); i++){
		if (a_list[i].n1 == n 
			//&& isValidEdge(a_list[i])
			&& minCost(a_list[i]) 
			&& !deposit){
			aux = a_list[i].n2;
			addTour(a_list[i]);
			if(aux == 0){
				deposit = true;
			}
			markVisited(a_list[i]);
			deleteEdges(a_list[i]);
			saveTour(aux);
		}
	}
}

// determinates if all the nodes have a even degree
bool Graph::allEvenDegree(){
	bool ev = true;
	int i = 0;
    while (ev && i < vertex){
    	if (countEdges(a_list[i]) % 2 == 0){
            ev = true;
            i++;
        } else{
        	ev = false;
        }
    }
        
    return ev;
}

int Graph::countEdges(Edge edge){
	int c = 0; 
	for (int i=0; i < edges; i++){
		if (a_list[i].n1 == edge.n1){
			c++;
		}
	}
	return c;
}


// determinate if a vertex can be on euler tour
bool Graph::isValidEdge(Edge edge) {

	if(edge.crossed > 1){
		return false;
	}

	int c = countEdges(edge);

	if (c == 1){
		return true;
	}
	
	memset(visited, false, vertex);
	int c1 = countVertex(edge.n1, visited);
	deleteEdges(edge);
	memset(visited, false, vertex);
	int c2 = countVertex(edge.n1, visited);
	addEdges(edge);
	
	if(c1 > c2){
		return false;
	} 
	return true;
}

int Graph::countBenefit(vector<Edge> tour){
	int be=0;
	for(int i =0; i<tour.size(); i++){
		be = tour[i].getBenefit();
	}
	return be;
}


// count the vertex rechaeble from node n
int Graph::countVertex(int n, bool visite[]) {
	visited[n] = true;
	int c = 1;

	vector<Edge> aux;
	for (int i=0; i<a_list.size(); i++){
		if(a_list[i].n1 == n){
			aux.push_back(a_list[i]);
		}
	}
	for (int i = 0; i < aux.size(); i++){
		if (!visited[aux[i].n2]){
			return c;
			c += countVertex(a_list[i].n2, visited);
		}
	}

	return c;
}

bool Graph::minCost(Edge edge){
	int cos = 0; //max int;
	vector<Edge> aux;
	for(int i=0; i< a_list.size(); i++){
		if(a_list[i].n1 == edge.n1){
			aux.push_back(a_list[i]);
		}
	}
	for(int i=0; i<aux.size(); i++){
		if(aux[i].benef > cos){
			cos = aux[i].benef;
		}
	}
	if(edge.cost == cos){
		return true;
	}
	return false;
}

void printEd(std::vector<Edge> v){
	for (int i=0; i< v.size(); i++){
		cout << v[i].n1 << "-" << v[i].n2 << endl;
	}
}

void Graph::markVisited(Edge edge){
	for (int i = 0; i < a_list.size(); ++i){
		if(a_list[i].n1 == edge.n2 && a_list[i].n2 == edge.n1){
			a_list[i].crossed = true;
		}
	}
	
}

int main(int argc, char **argv){

	Edge e1(0,1,2,10);
	Edge e2(0,2,10,0);
	Edge e3(1,2,3,2);
	Edge e4(1,3,20,5);
	Edge e5(3,5,9,1);
	Edge e6(1,4,1,3);
	Edge e7(2,4,5,4);
	Edge e8(2,3,3,4);
	Edge e9(4,3,2,8);
	Edge e10(4,5,8,1);

	Edge e11(1,0,2,10);
	Edge e12(2,0,10,0);
	Edge e13(2,1,3,2);
	Edge e14(3,1,20,5);
	Edge e15(5,3,9,1);
	Edge e16(4,1,1,3);
	Edge e17(4,2,5,4);
	Edge e18(3,2,3,4);
	Edge e19(3,4,2,8);
	Edge e20(5,4,8,1);

	std::vector<Edge> v;

	v.push_back(e1);
	v.push_back(e2);
	v.push_back(e3);
	v.push_back(e4);
	v.push_back(e5);
	v.push_back(e6);
	v.push_back(e7);
	v.push_back(e8);
	v.push_back(e9);
	v.push_back(e10);
	v.push_back(e11);
	v.push_back(e12);
	v.push_back(e13);
	v.push_back(e14);
	v.push_back(e15);
	v.push_back(e16);
	v.push_back(e17);
	v.push_back(e18);
	v.push_back(e19);
	v.push_back(e20);

	Graph g1(5,10,v);
	g1.eulerTour();

	// EULER_T ESTA VACIO
	for(int i =0; i<g1.euler_t.size(); i++){
		cout << g1.euler_t[i].n1 << "-" << g1.euler_t[i].n2 << endl;
	}


	return 0;

// TO DO:
	/*

	FALTA VERIFICAR QUE LOS VERTICES DEL CAMINO TENGAN SENTIDO

	*/

}