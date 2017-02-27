// Module for calculate max benefit path
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>
#include "graph.cpp"

using namespace std;

#define Ma 1200000000
#define Mi -1200000000

// return the node who has the minimun distance
int minDistance(int dist[], bool sptSet[], Graph g){
  // Initialize min value
  int min = INT_MIN, min_index;
  
  // find the node with min distance
  for (int v = 0; v < g.vertex; v++){
    if (sptSet[v] == false && dist[v] >= min){
      min = dist[v], min_index = v;
    }
  }
  return min_index;
}

// return the node who has the minimun distance
int minDistance2(int dist[], bool sptSet[],Graph g){
  // Initialize min value
  int min = INT_MIN, min_index;

  // find the node with minimun distance
  for (int v = 0; v < g.vertex; v++){
    if (sptSet[v] == false && dist[v] >= min){
      min = dist[v], min_index = v;
    }
  }
  
   return min_index;
}

// print all the edges of a vector
void printEdges(vector<Edge> edges){
  for(int i =0; i<edges.size(); i++){
    cout << endl << edges[i].n1 << "-" << edges[i].n2 << endl;
    cout << "c: " << edges[i].cost << " b: " << edges[i].benef << endl;
  }
}

// get the edges that belong to the shortest path
vector<Edge> filterEdges(vector<Edge> old, Graph g){

  // says if the vertex already was on the new solution
  bool ver[g.vertex+1];
  // initialize
  for (int i = 0; i < g.vertex; i++){
    ver[i] = false;
  }
  
  vector<Edge> news; // new path

  // find the shortest path on the solution
  while(old.size() !=0){
    // get the last element on the path
    Edge e = old.back();

    // if not in the new solution add it
    if(!ver[e.n2]){
      news.push_back(e);
      ver[e.n2] = true;
    }
    // delete the old path
    old.pop_back();
  }
  
  return news;
}
  
// print the distance between the deposit and the rest nodes
void printSolution(int dist[], vector<Edge> edge, Graph g) {
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < g.vertex; i++)
      printf("%d \t\t %d\n", i, dist[i]);

    printEdges(filterEdges(edge, g));
}

int getDistance(int dist[], int node){
  return dist[node];
}

// Funtion that based on dijkstra algorithm for search
// the min cost path from deposit vertex to the others
// and return the max benefit
int *firstPath(Graph g, int deposit){

  int dist[g.vertex+1]; // distance from deposit  to i

  // vetor with the shortest path.
  vector<Edge> vec;
  
  bool stpSet[g.vertex+1];
  // initialize distances with the min value
  // and the vector visited of the graph with false
  for (int i = 0; i < g.vertex+1; i++){
    dist[i] = INT_MIN, stpSet[i] = false;
  }
  
  // distance of deposit from itself is always 0
  dist[deposit] = 0;
  
  // find shortest path
  for (int count = 0; count < g.vertex; count++){

    // choose the vertex withminimum distance from the set 
    // of vertices not visited.
    int u = minDistance(dist, stpSet, g);
    // Mark the vertex as visited
    stpSet[u]= true;
    // update dist value of the adjacent vertices of the u vertex
    for (int v = 2; v < g.vertex+1; v++){

         // Update dist[v] only if is not visited
      if (!stpSet[v] && g.edgeExist(u,v) && dist[u] != INT_MIN
              && dist[u]+ g.getTotalBenefit(u,v) > dist[v]){
        // update distance and mark de edge as crossed
        dist[v] = dist[u] + g.getTotalBenefit(u,v);
        g.setCrossed(u,v);
        // insert value into the solution vector
        vec.push_back(g.getEdge(u,v));
      }
    }
  }
  
  // return the cost of the min path
  return dist;
}
 
// Funtion that based on dijkstra algorithm for search
// the min cost path from the last vertex to the others
// and return the max benefit
int secondPath(Graph g, int last_v){

    int dist[g.vertex+1];  // distance from deposit  to i

    // vetor with the shortest path.
    std::vector<Edge> vec;

    // array who say if a vertex was visited.
    bool stpSet[g.vertex+1];

    // initialize distances with the min value
    // and the vector vec with false
    for (int i = 0; i < g.vertex+1; i++)
      dist[i] = INT_MIN, stpSet[i] = false;
  
    // distance of a vertex from itself is always 0
    dist[last_v] = 0;
  
    // find shortest path
    for (int count = 0; count < g.vertex; count++){

      // choose the vertex withminimum distance from the set 
      // of vertices not visited.
      int u = minDistance2(dist, stpSet, g);
      // mark u as visited
      stpSet[u] = true;
  
       // update dist value of the adjacent vertices of the u vertex
      for (int v = 1; v< g.vertex+1; v++){
  
        // Update dist[v] only if is not visited
        if (!stpSet[v] && g.edgeExist(u,v) && dist[u] != INT_MIN
                && dist[u]+ g.getTotalBenefit(u,v) > dist[v]){

          // update distance and mark de edge as crossed
          dist[v] = dist[u] + g.getTotalBenefit(u,v);
          g.setCrossed(u,v);
          // insert value into the solution vector
          vec.push_back(g.getEdge(u,v));
        }
      }
    }
  
    // return the cost of the min path
    return getDistance(dist, 1);
}

// return the farthest vertex
int minVertex(int dist[], int v){
  for (int i=v; i > 0; i--){
    if(dist[i] < Ma && dist[i] > Mi){
      return i;
    }
  }
}
// standard deviation calculation
// given the optimum value for an instance
int dHeur(int vo, int voHeur) {
    int sd = 100 * ((vo - voHeur) / vo);
    return sd;
}

int main(int argc, char **argv) {

  Graph *graph;       // instance graph structure
  string filename;    // input file name 

  int vo, voHeur;     // optimum values
  int sdHeur;         // standard deviation against given optimum value


  filename = argv[1];
  vo = atoi(argv[2]);

  // build the graph with the instance info
  graph = buildGraph(filename);

  //calculate the max benefit path
  int *a = firstPath(*graph,1);
  int v = minVertex(a, graph->vertex);
  int b = secondPath(*graph,v);

  // optimum value for the execution
  voHeur = v+b;

  // Standard deviation calculation
  sdHeur = dHeur(vo, voHeur);

  cout << voHeur << endl;
  cout << sdHeur << endl;


  ofstream file((filename+"-salida.txt").c_str());
  file << voHeur << endl;
  file.close();
  
  return 0;
}