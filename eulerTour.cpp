#include <vector>
#include <cstdio>
#include <utility>
//#include <iostream.h>
#include "graph.cpp"

using namespace std;

int countNodes(Node n, bool v[]);
Graph eulerTour(Node n);

// determinate if a edge can be part of the euler tour
bool validEdge(Graph graph, Node node, Edge edge){
	if(node.edges.size() == 1){
		return true;
	}
	bool visited[graph.nodes.size()];
	int dfsc1 = countNodes(node, visited);
	node = removeEdge(node, edge);
	int dfsc2 = countNodes(node, visited);
	node = addEdge(node, edge);
	if(dfsc1 > dfsc2){
		return false;
	}
	return true;
}

// count the reachable nodes fron a node
int countNodes(Node node, bool visited[]){
	visited[node.node] = true;
	int r_nodes = 1;

	for(int i=0; i<node.edges.size(); i++){
		if(!visited[node.edges[i].s_node.node]){
			r_nodes += countNodes(node.edges[i].s_node, visited);
		}
	}
	return r_nodes;
}

Graph eulerTour(Graph graph, Node node){

	Node aux_node;

	for(int i=0; i<node.edges.size(); i++){
		Edge c_edge = node.edges[i];
		if(validEdge(graph, node, c_edge)){
			aux_node.node = node.node;
			aux_node.edges.push_back(c_edge);
			//new_graph = new_graph.nodes.push_back(aux_node);
			//cout << node << "-" << c_edge.s_node;
			eulerTour(graph, c_edge.s_node);
		}
	}
	return graph;
}