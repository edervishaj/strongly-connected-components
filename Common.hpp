/*
 * Common.hpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <string>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS> DirectedGraph;

/**
 * Generates random graph G(n,p) through Erdős-Rényi model
 */
DirectedGraph gen_rand_graph(int n_vertices, float edge_prob);

#endif /* COMMON_HPP_ */
