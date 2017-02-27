// Module for calculate max benefit path
#include <stdio.h>
#include <limits.h>
#include <vector>
#include "graph.cpp"

using namespace std;

  
// return the node who has the minimun distance
int minDistance(int dist[], vector<bool> sptSet, Graph g){
  // Initialize min value
  int min = INT_MIN, min_index;
  
  // find the node with min distance
  for (int v = 0; v < g.vertex; v++)
    if (sptSet[v] == false && dist[v] >= min){
      min = dist[v], min_index = v;
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
  }
}

// get the edges that belong to the shortest path
vector<Edge> filterEdges(vector<Edge> old, Graph g){

  // says if the vertex already was on the new solution
  bool ver[g.vertex];
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
int firstPath(Graph g, int deposit){

  int dist[g.vertex]; // distance from deposit  to i

  // vetor with the shortest path.
  vector<Edge> vec;
  
  // initialize distances with the min value
  // and the vector visited of the graph with false
  for (int i = 0; i < g.vertex; i++)
        dist[i] = INT_MIN, g.visited[i] = false;
  
  // distance of deposit from itself is always 0
  dist[deposit] = 0;
  
  // find shortest path
  for (int count = 0; count < g.vertex; count++){

    // choose the vertex withminimum distance from the set 
    // of vertices not visited.
    int u = minDistance(dist, g.visited, g);

    // Mark the vertex as visited
    g.visited[u] = true;
  
    // update dist value of the adjacent vertices of the u vertex
    for (int v = 0; v < g.vertex; v++){
  
         // Update dist[v] only if is not visited
      if (!g.visited[v] && g.edgeExist(u,v) && dist[u] != INT_MIN
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
  return getDistance(dist, g.vertex-1);
}
 
// Funtion that based on dijkstra algorithm for search
// the min cost path from the last vertex to the others
// and return the max benefit
int secondPath(Graph g, int last_v){

    int dist[g.vertex];  // distance from deposit  to i

    // vetor with the shortest path.
    std::vector<Edge> vec;

    // array who say if a vertex was visited.
    bool stpSet[g.vertex];

    // initialize distances with the min value
    // and the vector vec with false
    for (int i = 0; i < g.vertex; i++)
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
      for (int v = 0; v < g.vertex; v++){
  
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
    return getDistance(dist, 0);
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

  // graph construction from input file specification
  graph = buildGraph(filename);

  printEdges(graph->a_list);

  // optimum value for the execution
  voHeur = firstPath(*graph,0) + secondPath(*graph,5);

  // Standard deviation calculation
  sdHeur = dHeur(vo, voHeur);

  cout << voHeur << endl;
  cout << sdHeur << endl;

 /* 
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

  Graph g1(6,20,v);

  cout << firstPath(g1,0) + secondPath(g1,5) << endl;*/
  
  return 0;
}