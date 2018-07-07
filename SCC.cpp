/*
 * SCC.cpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 *
 */

#include "SCC.hpp"
#include <random>
#include <vector>
#include <stack>
#include <iostream>

void print(std::stack<int> &s){
    if(s.empty())
    {
        std::cout << std::endl;
        return;
    }
    int x = s.top();
    s.pop();
    print(s);
    s.push(x);
    std::cout << x << " ";
}

void print_graph(const DiGraph& g){
	DiGraph::vertex_iterator v, vend;
	DiGraph::out_edge_iterator e, eend;

	// Go over each vertex
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v){
		std::cout << g[*v].index << " --> ";
		for(boost::tie(e, eend) = out_edges(*v, g); e != eend; ++e) {
			vertex_t w = boost::target(*e, g);
			std::cout << g[w].index << " ";
		}
		std::cout << std::endl;
	}
}

void print_graph_json(const DiGraph& g, std::string filename){

}

DiGraph gen_rand_graph(int n_vertices, float edge_prob, int seed){
	// Initialize seed for reproducibility
	std::mt19937 eng(seed);

	// Initialize uniform distribution number generator
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	// Initialize DiGraph object
	DiGraph g;

	// Insert the vertices in the graph
	for(int i = 0; i < n_vertices; i++){
		Vertex u = {i, false, n_vertices + 1, false};
		boost::add_vertex(u, g);
	}

	// For each pair of vertices, add edge with probability edge_prob
	for(int i = 0; i < n_vertices; i++){
		vertex_t u = boost::vertex(i, g);
		for(int j = 0; j < n_vertices; j++){
			vertex_t v = boost::vertex(j, g);
			if(distribution(eng) < edge_prob)
				boost::add_edge(u, v, g);
		}
	}

	return g;
}

/* Main loop of Tarjan Algorithm */
void visit(std::vector<DiGraph>& scc, std::stack<vertex_t>& stack, DiGraph& g, vertex_t v){
	g[v].visited = true;

//	std::vector<vertex_t> root;
//	std::vector<bool> inComponent(num_vertices(g), false);

	// Auxiliary edge_iterator variables
	DiGraph::out_edge_iterator e, eend;

//	int v_id = g[v].index;

	g[v].root = g[v].index;
	g[v].inComponent = false;
	stack.push(v);

	// Go over all neighbors of v
	for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
		vertex_t w = boost::target(*e, g);
//		int w_id = g[w].index;

		if(!g[w].visited)
			visit(scc, stack, g, w);

		if(!g[w].inComponent)
			g[v].root = (g[v].root <= g[w].root) ? g[v].root : g[w].root;
	}

	// Component identified, store in vector scc
	if(g[v].root == g[v].index){
		DiGraph h;
		int w_id = -1;
		while(w_id != g[v].index){
			vertex_t w = stack.top();
			stack.pop();
			g[w].inComponent = true;
			g[w].root = g[v].index;
			boost::add_vertex({g[w].index, g[w].visited, g[w].root, g[w].inComponent}, h);
			w_id = g[w].index;
		}

		// Construct the graph of the component
		scc.push_back(h);
	}
}

std::vector<DiGraph> tarjan_scc(DiGraph g){
	// Vector of SCC to be returned by the algorithm
	std::vector<DiGraph> scc;
	std::stack<vertex_t> stack;

	DiGraph::vertex_iterator v, vend;

	// Go over all vertices
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
		if(!g[*v].visited) {
			visit(scc, stack, g, *v);
		}
	}

	return scc;
}
