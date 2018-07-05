/*
 * Common.cpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 *
 */

#include "Common.hpp"
#include <iostream>
#include <random>
#include <boost/graph/random.hpp>
using namespace std;

DirectedGraph gen_rand_graph(int n_vertices, float edge_prob){
	mt19937 eng(124);
	uniform_real_distribution<float> distribution(0.0, 1.0);

	// Generate n nodes
	DirectedGraph g(n_vertices);
	for(int u = 0; u < n_vertices-1; u++)
		for(int v = 0; v < n_vertices; v++)
			if(distribution(eng) < edge_prob)
				boost::add_edge(u, v, g);

	return g;
}
