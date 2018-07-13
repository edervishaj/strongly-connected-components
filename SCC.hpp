/*
 * SCC.hpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */

#ifndef SCC_HPP_
#define SCC_HPP_

#include <boost/graph/adjacency_list.hpp>

struct Vertex { int index; bool visited; };
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Vertex> DiGraph;
typedef boost::graph_traits<DiGraph>::vertex_descriptor vertex_t;

/* Creates vecor of components subgraphs SCC from the component identifiers given by Pearce's algorithms. */
std::vector<DiGraph> create_scc (std::vector<int> component_ids, DiGraph g);

/* Generates random graph G(n_vertices, edge_prob) through Erdős-Rényi model */
DiGraph rand_graph(int n_vertices, float edge_prob, int seed);

/* Generates random graph G(n_vertices, edge_prob) through Erdős-Rényi model starting from g */
DiGraph g_rand_graph(int n_vertices, float edge_prob, int seed, DiGraph& g);

/* Generates a graph with n strongly connected components */
DiGraph n_rand_graph(const std::vector<int>& n_component, int n_vertices, float edge_prob, bool rand, int seed);

/* Tarjan algorithm -- returns vector containing the SCCs */
std::vector<DiGraph> tarjan_scc(DiGraph g);

/* Nuutila algorithm 1 -- returns vector containing the SCCs */
std::vector<DiGraph> nuutila1_scc(DiGraph g);

/* Nuutila algorithm 2 -- returns vector containing the roots of SCCs */
std::vector<int> nuutila2_scc(DiGraph g);

/* Pearce algorithm 1 -- returns vector containing the component identifier of each vertex */
std::vector<int> pearce1_scc(DiGraph g);

/* Pearce algorithm 2 -- returns vector containing the component identifier of each vertex */
std::vector<int> pearce2_scc(DiGraph g);


/* Prints a DiGraph */
void print_graph(const DiGraph& g, std::ostream& os);



#endif /* SCC_HPP_ */
