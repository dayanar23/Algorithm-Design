#include <list>
#include <std>

// data struct for the graph's edges
struct Edge {

	int node _1; 		// first node
	int node _2; 		// second node
	int be;				// benefit of cross
	int ce;				// cost of cross
	boolean crossed; 	// true if the edge was already crossed

	// calculate the benefit of cross an edge
	int get_benefit(){

		if (crossed){
			return (be-2*ce) 
		}
		else{
			return be-ce		
		}
	}
};

// data struct for the graph
struct Graph {

	list<Edge> list_E; 	// list of graph's edges

};

// data struct for the instance
struct Instance {

	Graph graph;			// graph of the instance
	string name;			// name of the instance
	int vertices;			// numb of vertices	
	int required_edges		// numb of required edges
	int n_required_edges 	// numb of non required edges
	// R Q y esas cosas?
};


// calculate the std percent
float calculate_std(vo, vh,){
	return 100*(vo-vh)/vo
}

// TO DO:
/*
algoritmo greedy que puede ser basado en

- optimizacion por colonia de hormigas
- intercambio par a par (2-opt)
- algoritmo del vecino mas proximo (acm)
- MTS

*/