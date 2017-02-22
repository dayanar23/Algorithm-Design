#include <vector>
#include <cstdio>
#include <utility>
//#include <iostream.h>

using namespace std;

struct Node;
struct Edge;
struct Graph;
struct Instance;
Graph removeEdge(Graph g, Node n);
Graph addNode(Graph g, Node n);
Node addEdge(Node n, Edge e);
Node removeEdge( Node n, Edge e);
bool evenDegree(Node n);
bool isEulerian(Graph g);

// data struct for nodes
struct Node{
	int node;
	vector<Edge> edges; // list of edges
};

// data struct for the graph's edges
struct Edge{
	Node s_node;	// secon node of the edge
	int be;			// benefit of cross
	int ce;			// cost of cross
	bool crossed; 	// true if the edge was already crossed

	// calculate the benefit of cross an edge
	int get_benefit(){

		if (crossed){
			return (be-2*ce); 
		}
		else{
			return be-ce;		
		}
	}
};



// data struct for the graph
struct Graph {

	vector<Node> nodes; 	// list of graph's edges
};

// data struct for the instance
struct Instance {

	Graph graph;			// graph of the instance
	//string name;			// name of the instance
	int vertices;			// numb of vertices	
	int required_edges;		// numb of required edges
	int n_required_edges; 	// numb of non required edges
	// R Q y esas cosas?
};


// add a node 
Graph addNode(Graph graph, Node node){
	graph.nodes.push_back(node);
	return graph;
}

// remove a node of the graph and all the
// edges associate
Graph removeNode(Graph graph, Node node){
	for (int i =0; i<graph.nodes.size(); i++){
		for (int j=0; j<graph.nodes[i].edges.size(); i++){
			if(graph.nodes[i].edges[j].s_node == node){
				removeEdge(graph.nodes[i], graph.nodes[i].edges[j]);
			}
		}
	}
	graph.nodes.erase(std::remove(node));
	return graph;
}

// add an edge
Node addEdge(Node node, Edge edge){
	node.edges.push_back(edge);

	return node;
}

// remove an edge
Node removeEdge(Node node, Edge edge){
	Node aux = edge.s_node;
	node.edges.remove(edge);
	for(int i=0; i<aux.edges.size(); i++){
		if(aux.edges[i].s_node == node){
			removeEdge(aux,aux.edges[i]);
		}
	}
	return node;
}

// determinate if the node has a even degree
bool evenDegree(Node node){
	int sz = node.edges.size();
	if(sz%2 == 0){
		return true;
	}
	else{
		return false;
	}
}

// determinate if a graph is Eulerian
// all the nodes have even degree != 0
bool isEulerian(Graph graph){
	bool cn = true;
	int i = 0;
	while (cn or i<graph.nodes.size()){
		cn = evenDegree(graph.nodes[i])
		i += 1;
	}
	return cn;

}

// calculate the std percent
float calculate_std(int vo, int vh){
	return 100*(vo-vh)/vo;
}

