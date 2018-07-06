/*
 * Common.hpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */

#ifndef SCC_HPP_
#define SCC_HPP_

#include <boost/graph/adjacency_list.hpp>



struct Vertex { int index; bool visited; int inComponent; };
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, Vertex> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

struct DirectedGraph{
	Graph g;
	std::vector<int> vertices;
};

/* Generates random graph G(n,p) through Erdős-Rényi model */
DirectedGraph gen_rand_graph(int n_vertices, float edge_prob, int seed);

/* Tarjan algorithm -- returns vector containing the SCCs */
std::vector<DirectedGraph> tarjan_scc(DirectedGraph g);




#endif /* SCC_HPP_ */
