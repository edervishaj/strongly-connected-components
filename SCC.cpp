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
#include <ostream>

void print_stack(std::stack<int> &s){
    if(s.empty())
    {
        std::cout << std::endl;
        return;
    }
    int x = s.top();
    s.pop();
    print_stack(s);
    s.push(x);
    std::cout << x << " ";
}

/* Print one row for each vertex in the format v --> u1 u2 u3 */
void print_graph(const DiGraph& g, std::ostream& os=std::cout){
	DiGraph::vertex_iterator v, vend;
	DiGraph::out_edge_iterator e, eend;

	// Go over each vertex
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v){
		os << g[*v].index << " --> ";
		for(boost::tie(e, eend) = out_edges(*v, g); e != eend; ++e) {
			vertex w = boost::target(*e, g);
			os << g[w].index << " ";
		}
		os << std::endl;
	}
}

/* Print the graph in json format to be used by sigmajs */
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
		Vertex u = {i, false};
		boost::add_vertex(u, g);
	}

	// For each pair of vertices, add edge with probability edge_prob
	for(int i = 0; i < n_vertices; i++){
		vertex u = boost::vertex(i, g);
		for(int j = 0; j < n_vertices; j++){
			vertex v = boost::vertex(j, g);
			if(distribution(eng) < edge_prob)
				boost::add_edge(u, v, g);
		}
	}

	return g;
}

/* Main loop of Tarjan Algorithm */
void visit(std::vector<DiGraph>& scc, std::stack<vertex>& stack, std::vector<bool>& inComponent, std::vector<int>& root, DiGraph& g, vertex v){
	g[v].visited = true;

	// Auxiliary edge_iterator variables
	DiGraph::out_edge_iterator e, eend;

	int v_idx = g[v].index;

	root[v_idx] = v_idx;
	stack.push(v);

	// Go over all neighbors of v
	for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
		vertex w = boost::target(*e, g);
		int w_idx = g[w].index;

		if(!g[w].visited)
			visit(scc, stack, inComponent, root, g, w);

		if(!inComponent[w_idx])
			root[v_idx] = (root[v_idx] <= root[w_idx]) ? root[v_idx] : root[w_idx];
	}

	// Component identified, store in vector scc
	if(root[v_idx] == v_idx){
		DiGraph h;
		int w_id = -1;
		while(w_id != g[v].index){
			vertex w = stack.top();
			stack.pop();
			w_id = g[w].index;
			inComponent[w_id] = true;
			root[w_id] = v_idx;
			boost::add_vertex({g[w].index, g[w].visited}, h);
		}

		// Construct the graph of the component
		scc.push_back(h);
	}
}

std::vector<DiGraph> tarjan_scc(DiGraph g){
	// Number of vertices in g
	int num_vertices = boost::num_vertices(g);

	// Vector of SCC to be returned by the algorithm
	std::vector<DiGraph> scc;

	// DS used by Tarjan
	std::stack<vertex> stack;
	std::vector<bool> inComponent(num_vertices, false);
	std::vector<int> root(num_vertices, num_vertices + 1);

	DiGraph::vertex_iterator v, vend;

	// Go over all vertices
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
		if(!g[*v].visited) {
			visit(scc, stack, inComponent, root, g, *v);
		}
	}

	return scc;
}

/* Main loop of Nuutila first improvement */
void visit1(std::vector<DiGraph>& scc, std::stack<vertex>& stack, std::vector<bool>& inComponent, std::vector<int>& root, DiGraph& g, vertex v){
    g[v].visited = true;

    // Auxiliary edge_iterator variables
    DiGraph::out_edge_iterator e, eend;

    int v_idx = g[v].index;

    root[v_idx] = v_idx;

    // Go over all neighbors of v
    for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
        vertex w = boost::target(*e, g);
        int w_idx = g[w].index;

        if(!g[w].visited)
            visit1(scc, stack, inComponent, root, g, w);

        if(!inComponent[w_idx])
			root[v_idx] = (root[v_idx] <= root[w_idx]) ? root[v_idx] : root[w_idx];
    }

    // Component identified, store in vector scc
    if(root[v_idx] == v_idx){
        DiGraph h;

        inComponent[v_idx] = true;

        boost::add_vertex({v_idx, g[v].visited}, h);

        while(stack.size() > 0 && g[stack.top()].index > v_idx){
            vertex w = stack.top();
            int w_idx = g[w].index;
            stack.pop();
            inComponent[w_idx] = true;
            boost::add_vertex({w_idx, g[w].visited}, h);
        }

        // Construct the graph of the component
        scc.push_back(h);

    } else stack.push(v);
}

std::vector<DiGraph> nuutila1_scc(DiGraph g){
	// Number of vertices in g
	int num_vertices = boost::num_vertices(g);

	// Vector of SCC to be returned by the algorithm
	std::vector<DiGraph> scc;

	// DS used by Tarjan
	std::stack<vertex> stack;
	std::vector<bool> inComponent(num_vertices, false);
	std::vector<int> root(num_vertices, num_vertices + 1);

    DiGraph::vertex_iterator v, vend;

    // Go over all vertices
    for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
        if(!g[*v].visited) {
            visit1(scc, stack, inComponent, root, g, *v);
        }
    }

    return scc;
}

void visit2(std::vector<DiGraph>& scc, std::stack<vertex>& stack, DiGraph& g, vertex v){

}