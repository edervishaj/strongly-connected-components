/*
 * SCC.hpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */

#ifndef SCC_HPP_
#define SCC_HPP_

#include <boost/graph/adjacency_list.hpp>

struct Vertex { int index; bool visited; int root; bool inComponent; };
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, Vertex> DiGraph;
typedef boost::graph_traits<DiGraph>::vertex_descriptor vertex_t;



/* Generates random graph G(n,p) through Erdős-Rényi model */
DiGraph gen_rand_graph(int n_vertices, float edge_prob, int seed);

/* Tarjan algorithm -- returns vector containing the SCCs */
std::vector<DiGraph> tarjan_scc(DiGraph g);

/* Nuutila algorithm 1 -- returns vector containing the SCCs */
std::vector<DiGraph> nuutila1_scc(DiGraph g);

/* Nuutila algorithm 2 -- returns vector containing the SCCs */
std::vector<DiGraph> nuutila2_scc(DiGraph g);

/* Prints a DiGraph */
void print_graph(const DiGraph& g, std::ostream& os);



#endif /* SCC_HPP_ */
