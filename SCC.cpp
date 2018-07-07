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

DirectedGraph gen_rand_graph(int n_vertices, float edge_prob, int seed){
	// Initialize seed for reproducibility
	std::mt19937 eng(seed);

	// Initialize uniform distribution number generator
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	// Initialize DirectedGraph object
	DirectedGraph g;

	// Insert the vertices in the graph
	for(int i = 0; i < n_vertices; i++){
		Vertex u = {i, false};
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
void visit(std::vector<DirectedGraph>& scc, std::stack<int>& stack, DirectedGraph& g, vertex_t v){
	g[v].visited = true;

	// Auxiliary edge_iterator variables
	DirectedGraph::out_edge_iterator e, eend;

	std::vector<vertex_t> root(num_vertices(g));
	std::vector<bool> inComponent(num_vertices(g));

	int v_id = g[v].index;

	root[v_id] = v_id;
	inComponent[v_id] = false;
	stack.push(v_id);

	// Go over all neighbors of v
	for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
		vertex_t w = boost::target(*e, g);
		if(!g[w].visited)
			visit(scc, stack, g, w);
		int w_id = g[w].index;
		if(!inComponent[w_id])
			root[v_id] = (root[v_id] <= root[w_id]) ? root[v_id] : root[w_id];
	}

	// Component identified, store in vector scc
	if(root[v_id] == v_id){
		DirectedGraph h;
		int w_id;
		do{
			w_id = stack.top();
			stack.pop();
			inComponent[w_id] = true;
			Vertex w = {w_id, false};
			boost::add_vertex(w, h);
		}while(w_id != v_id);

		// Construct the graph of the compo

		scc.push_back(h);
	}
}

std::vector<DirectedGraph> tarjan_scc(DirectedGraph g){
	// Vector of SCC to be returned by the algorithm
	std::vector<DirectedGraph> scc;
	std::stack<int> stack;

	boost::adjacency_list<>::vertex_iterator v, vend;

	// Go over all vertices
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
		if (g[*v].visited == false) {
			visit(scc, stack, g, *v);
		}
	}

	return scc;
}
