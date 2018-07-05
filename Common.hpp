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
using namespace boost;

/**
 * n_nodes: number of nodes of the graph
 * edge_prob: probability of an edge being present between any pair of nodes
 *
 * return: adjacency_list object representing a graph
 */
void gen_graph(int n_nodes, float edge_prob);

#endif /* COMMON_HPP_ */
