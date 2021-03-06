// Module for class definition
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
  
using namespace std;


// class for edges
class Edge{

  public:
  
  int n1;       // first node of the edge
  int n2;       // second node of the edge
  int cost;     // cost of the edge
  int benef;    // benefit of the edge
  bool crossed; // say if the edge was crossed

  // constructor of the class
  Edge(int n1, int n2, int c, int b){

    this->n1 = n1;
    this->n2 = n2;
    this->cost = c;
    this->benef = b;
    this->crossed =false;
  }

  // defintion of comparator operator
  bool operator==(const Edge &e1) const {
    return n1 == e1.n1 && n2 == e1.n2 &&
        cost == e1.cost && benef == e1.benef
        && crossed == e1.crossed;
  }

  // return the benefit of an edge depending
  // if the edge was already crossed
  int getBenefit(){
    if(!crossed){
      return benef-cost;
    }
    return benef-2*cost;
  }

};


// class for graph
class Graph{

  public:

  int vertex;           // num of vertices
  int edges;            // num of edges 
  vector<bool> visited; // store if a vertex was visited 
  vector<Edge> a_list;  // lists of edges

  // class constructor
  Graph(int vertex, int edges, vector<Edge> &eds) { 
    this-> vertex = vertex; 
    this-> edges = edges;
    this-> a_list = eds;
  }

  // return the benefit of an edge composse for the nodes
  // u and v
  int getTotalBenefit(int u, int v){
    for(int i =0; i < a_list.size(); i++){
      if(a_list[i].n1 == u && a_list[i].n2 == v){
        return a_list[i].getBenefit();
      }
    }
  }

  // verify if an edge (u,v) exist on the graph
  bool edgeExist(int u, int v){
    for (int i=0; i< a_list.size(); i++){
      if(a_list[i].n1 == u && a_list[i].n2 == v){
        return true;
      }
    }
    return false;
  }

  // mark and edge as crossed
  void setCrossed(int u, int v){
    for (int i=0; i< a_list.size(); i++){
      if((a_list[i].n1 == u && a_list[i].n2) == v ||
      (a_list[i].n1 == v && a_list[i].n2 == u)){
        a_list[i].crossed = true;
      }
    }
  }

  // return the edge composse by the nodes u,v
  Edge getEdge(int u, int v){
    for (int i=0; i< a_list.size(); i++){
      if(a_list[i].n1 == u && a_list[i].n2 == v){
        return a_list[i];
      }
    }
  }

};


Graph * buildGraph(string filename) {

  // Auxiliar variables to ease file reading
  stringstream sstream;
  string line; 
  string tmp;

  int vertex, edges, n_edges;
  int src, dst;
  int cost, benef;
  char c;

  vector<Edge> eds;           // edges vector

  ifstream file(filename.c_str());   // file stream

  if ( file.is_open() ) {

    getline(file, line);
    
    sstream.str(line);
    sstream >> tmp >> tmp >> tmp >> c >> vertex;
    
    getline(file, line);

    sstream.clear();  
    sstream.str(line);
    sstream >> tmp >> tmp >> tmp >> tmp >> edges;

    for ( int i = 0 ; i < edges ; ++i ) {
      getline(file, line);

      sstream.clear();
      sstream.str(line);

      sstream >> src;
      sstream >> dst;
      sstream >> cost;
      sstream >> benef;

      Edge edge(src, dst, cost, benef);
      Edge edge2(dst, src, cost, benef);
      eds.push_back(edge);
      eds.push_back(edge2);
    }

    getline(file, line);
    sstream.clear();  
    sstream.str(line);
    sstream >> tmp >> tmp >> tmp >> tmp >> tmp >> n_edges;

    edges += n_edges;

    for ( int i = 0 ; i < n_edges ; ++i ) {
      getline(file, line);

      sstream.clear();
      sstream.str(line);

      sstream >> src;
      sstream >> dst;
      sstream >> cost;
      sstream >> benef;

      Edge edge(src, dst, cost, benef);
      Edge edge2(dst,src, cost, benef);
      eds.push_back(edge);
      eds.push_back(edge2);
    }

    static Graph graph(vertex, edges*2,eds);

    return &graph;

    }  else cout << "Unable to open file"; 

    return NULL;

}