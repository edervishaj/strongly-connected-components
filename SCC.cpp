/*
 * Common.cpp
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
		g.vertices.push_back(i);
		boost::add_vertex(u, g.g);
	}

	// For each pair of vertices, add edge with probability edge_prob
	for(int i = 0; i < n_vertices; i++){
		vertex_t u = boost::vertex(i, g.g);
		for(int j = 0; j < n_vertices; j++){
			vertex_t v = boost::vertex(j, g.g);
			if(distribution(eng) < edge_prob)
				boost::add_edge(u, v, g.g);
		}
	}

	return g;
}

std::vector<DirectedGraph> tarjan_scc(DirectedGraph g){
	// Vector of SCC to be returned by the algorithm
	std::vector<DirectedGraph> scc;

	boost::adjacency_list<>::vertex_iterator v, vend;

	// Go over all vertices
	for(int i = 0, boost::tie(v, vend) = vertices(g.g); v != vend; ++v, ++i){
////		std::cout << g[*v].index << "\t" << g[*v].visited << std::endl;
//		if(g.g[*v].visited == false){
//			visit(g, i);
//		}
	}
	return scc;
}

void visit(DirectedGraph g, int idx){
	std::vector<vertex_t> root(g.vertices.size());
	std::stack<vertex_t> stack;

}
