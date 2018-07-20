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
#include <algorithm>

/* Print one row for each vertex_t in the format v --> u1 u2 u3 */
void print_graph(const DiGraph& g, std::ostream& os=std::cout){
	DiGraph::vertex_iterator v, vend;
	DiGraph::out_edge_iterator e, eend;

	// Go over each vertex_t
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v){
		os << g[*v].index << " --> ";
		for(boost::tie(e, eend) = out_edges(*v, g); e != eend; ++e) {
			vertex_t w = boost::target(*e, g);
			os << g[w].index << " ";
		}
		os << std::endl;
	}
}

/* Creates vecor of components subgraphs SCC from the component identifiers given by Pearce's algorithms. */
std::vector<DiGraph> create_scc (std::vector<int> component_ids, DiGraph g) {

    std::set<int> components(component_ids.begin(), component_ids.end());

    std::vector<DiGraph> scc(components.size());

    std::vector<std::set<int>> component_vertices(components.size());

    std::vector<vertex_t> vertices(component_ids.size());

    //Go over each component
    int comp_id = 0;
    std::set<int>::iterator it_c;
    for (it_c = components.begin(); it_c != components.end(); ++it_c, comp_id++){

        //Insert vertices into respective component
        for (int j = 0; j < component_ids.size(); j++) {

            if (component_ids[j] == *it_c) {
                Vertex u = {j, false};
                vertices[j] = boost::add_vertex(u, scc[comp_id]);
                component_vertices[comp_id].insert(j);
            }
        }

        //Go over vertices of a component
        std::set<int>::iterator it;
        for (it = component_vertices[comp_id].begin(); it != component_vertices[comp_id].end(); ++it){

            int u_idx = *it;
            vertex_t u_g = boost::vertex(u_idx, g);
            vertex_t u = vertices[u_idx];

            //Copy the edges of the main graph whose both vertices are in the same component
            DiGraph::out_edge_iterator e, eend;
            for(boost::tie(e, eend) = out_edges(u_g, g); e != eend; ++e) {
                vertex_t w_g = boost::target(*e, g);
                int w_idx = g[w_g].index;

                if (component_vertices[comp_id].find(w_idx) != component_vertices[comp_id].end()) {
                    vertex_t w = vertices[w_idx];
                    boost::add_edge(u, w, scc[comp_id]);
                }
            }
        }
    }
    return scc;
}

DiGraph rand_graph(int n_vertices, float edge_prob, int seed){
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
		vertex_t u = boost::vertex(i, g);
		for(int j = 0; j < n_vertices; j++){
			vertex_t v = boost::vertex(j, g);
			if(distribution(eng) < edge_prob)
				boost::add_edge(u, v, g);
		}
	}

	return g;
}

DiGraph rand_graph(int n_vertices, int m_edges, int seed){
    // Initialize seed for reproducibility
    std::mt19937 eng(seed);

    // Initialize uniform distribution number generator
    std::uniform_int_distribution<int> distribution(0, n_vertices-1);

    // Initialize DiGraph object
    DiGraph g;

    // Insert the vertices in the graph
    for(int i = 0; i < n_vertices; i++){
        Vertex u = {i, false};
        boost::add_vertex(u, g);
    }

    int inserted_edges = 0;

    // Insert edges by sampling their endpoints
    while(inserted_edges < m_edges){
        // Sample source & target vertices
        int u_idx = distribution(eng);
        int v_idx = distribution(eng);

        vertex_t u = boost::vertex(u_idx, g);
        vertex_t v = boost::vertex(v_idx, g);

        // If the edge is not already in the graph -- do not allow parallel edges
        if(!boost::edge(u, v, g).second){
            boost::add_edge(u, v, g);
            inserted_edges++;
        }
    }

    return g;
}

/* Starting from another graph, we construct a random graph by adding non-parallel edges following Erdős-Rényi model */
DiGraph g_rand_graph(int n_vertices, float edge_prob, int seed, DiGraph& g){
    // If n_vertices is less than the number of vertices g already has, then return g
	int current_vertices = boost::num_vertices(g);
	int residual_vertices = n_vertices - current_vertices;
	if(residual_vertices < 0)
		return g;

	// Initialize seed for reproducibility
	std::mt19937 eng(seed);

	// Initialize uniform distribution number generator
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	// Insert the vertices in the graph
	for(int i = 0; i < residual_vertices; i++){
		Vertex u = {i + current_vertices, false};
		boost::add_vertex(u, g);
	}

	// For each pair of vertices, add edge with probability edge_prob if it does not exist
	for(int i = 0; i < current_vertices + residual_vertices; i++){
		vertex_t u = boost::vertex(i, g);
		for(int j = 0; j < current_vertices + residual_vertices; j++){
			vertex_t v = boost::vertex(j, g);
			if(distribution(eng) < edge_prob && !boost::edge(u, v, g).second)
				boost::add_edge(u, v, g);
		}
	}

	return g;
}

/* A directed cycle is a scc, so we constract a graph with n cycles */
DiGraph n_rand_graph(const std::vector<int>& n_component, int n_vertices, float edge_prob, bool rand_components, bool rand_graph, int seed){
    // Initialize seed for reproducibility
    std::mt19937 eng(seed);

    // Auxiliary variables
	vertex_t v, v_prev, v_init;
	int next_idx = -1;
	int r_vertices;

	DiGraph g;

	for(int i = 0; i < n_component.size(); i++){
	    // Keep track of the first added vertex of the component
		v_init = boost::add_vertex({++next_idx, false}, g);
		v_prev = v_init;

		// If random_components is set, we sample different number of vertices per component
		if(rand_components) {
            std::uniform_int_distribution<int> distribution(1, 10);
            r_vertices = distribution(eng);
        }
        else r_vertices = n_component[i];   // otherwise use provided number of vertices per component

        // Add the vertices keeping track of the previous added vertex so to connect them together
		for(int j = 1; j < r_vertices; j++){
			v = boost::add_vertex({++next_idx, false}, g);
			boost::add_edge(v_prev, v, g);
			v_prev = v;
		}

		// Close the cycle to create the component
		boost::add_edge(v, v_init, g);
	}

	// Call g_rand_graph if you want to randomize starting from the n_components
	if(rand_graph) return g_rand_graph(n_vertices, edge_prob, seed, g);
    else return g;
}

/* Main loop of Tarjan Algorithm */
void visit(std::vector<DiGraph>& scc, std::stack<vertex_t>& stack, std::vector<bool>& inComponent, std::vector<int>& root, DiGraph& g, vertex_t v){
    // Auxiliary edge_iterator variables
    DiGraph::out_edge_iterator e, eend;

	g[v].visited = true;

	int v_idx = g[v].index;

	root[v_idx] = v_idx;
	stack.push(v);

	// Go over all neighbors of v
	for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
		vertex_t w = boost::target(*e, g);
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
			vertex_t w = stack.top();
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
	std::stack<vertex_t> stack;
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
void visit1(std::vector<DiGraph>& scc, std::stack<vertex_t>& stack, std::vector<bool>& inComponent, std::vector<int>& root, DiGraph& g, vertex_t v){
    // Auxiliary edge_iterator variables
    DiGraph::out_edge_iterator e, eend;

    g[v].visited = true;

    int v_idx = g[v].index;

    root[v_idx] = v_idx;

    // Go over all neighbors of v
    for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
        vertex_t w = boost::target(*e, g);
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
            vertex_t w = stack.top();
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

	// DS used by nuutila1
	std::stack<vertex_t> stack;
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

/* Main loop of Nuutila second improvement */
void visit2(std::vector<int>& scc, std::vector<int>& stack, std::vector<bool>& inComponent, std::vector<int>& root, DiGraph& g, vertex_t v){
    // Auxiliary edge_iterator variables
    DiGraph::out_edge_iterator e, eend;

	g[v].visited = true;

	int v_idx = g[v].index;

	root[v_idx] = v_idx;

    // Go over all neighbors of v
    for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
        vertex_t w = boost::target(*e, g);
        int w_idx = g[w].index;

        if(!g[w].visited)
            visit2(scc, stack, inComponent, root, g, w);

        if(!inComponent[root[w_idx]])
            root[v_idx] = (root[v_idx] <= root[w_idx]) ? root[v_idx] : root[w_idx];
    }

    // Component identified, store in vector scc
    if(root[v_idx] == v_idx){
        DiGraph h;

        if(stack.back() >= v_idx){
            while(!stack.empty() && stack.back() >= v_idx){
                int w_idx = stack.back();
                stack.pop_back();
                inComponent[w_idx] = true;
            }
        } else {
            inComponent[v_idx] = true;
	    //scc.push_back(v_idx);
        }
    } else {
        if(std::find(stack.begin(), stack.end(), root[v_idx]) == stack.end()) {
            stack.push_back(root[v_idx]);
            scc.push_back(v_idx);
        }
    }
}

std::vector<int> nuutila2_scc(DiGraph g){
	// Number of vertices in g
	int num_vertices = boost::num_vertices(g);

	// Vector of SCC to be returned by the algorithm
	std::vector<int> scc;

	// DS used by nuutila2
	std::vector<int> stack;
	std::vector<bool> inComponent(num_vertices, false);
	std::vector<int> root(num_vertices, num_vertices + 1);

	DiGraph::vertex_iterator v, vend;

	stack.push_back(-1);

	if(boost::num_vertices(g) != num_vertices)
		exit(1);

	// Go over all vertices
	for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
		if(!g[*v].visited) {
			visit2(scc, stack, inComponent, root, g, *v);
		}
	}

	return scc;
}



/* Main loop of Pearce's first improvement */
void visitpearce1(std::vector<int>& rindex, std::vector<int>& S, std::vector<bool>& inComponent, DiGraph& g, vertex_t v, int& c, int& index_p){
// Auxiliary edge_iterator variables
    DiGraph::out_edge_iterator e, eend;

    int root = true;

    g[v].visited = true;

    int v_idx = g[v].index;
    rindex[v_idx] = index_p;
    index_p++;


// Go over all neighbors of v
    for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
        vertex_t w = boost::target(*e, g);
        int w_idx = g[w].index;

        if(!g[w].visited)
            visitpearce1(rindex, S, inComponent, g, w, c, index_p);

        if(!inComponent[w_idx] && (rindex[w_idx] < rindex[v_idx])) {
            rindex[v_idx] = rindex[w_idx];
            root = false;
        }
    }

// Component identified, assign component identifiers to the corresponding vertices.
    if (root) {
        inComponent[v_idx] = true;

        while (!S.empty() && (rindex[v_idx] <= rindex[S.back()])){
            int w_idx = S.back();
            S.pop_back();
            rindex[w_idx] = c;
            inComponent[w_idx] = true;
        }
        rindex[v_idx] = c;
        c++;
    } else {
        S.push_back(v_idx);
    }
}

std::vector<int> nuutila2_scc(DiGraph g){
// Number of vertices in g
    int num_vertices = boost::num_vertices(g);

// Vector of component identifiers to be returned by the algorithm.
    std::vector<int> rindex(num_vertices);

    int c = 0;
    int index_p = 0;


// DS used by nuutila2
    std::vector<int> S;
    std::vector<bool> inComponent(num_vertices, false);

    DiGraph::vertex_iterator v, vend;

// Go over all vertices
    for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
        if(!g[*v].visited) {

            visitpearce1(rindex, S, inComponent, g, *v, c, index_p);
        }
    }

    return rindex;
}


/* Main loop of Pearce's second improvement */
void visitpearce2(std::vector<int>& rindex, std::vector<int>& S, DiGraph& g, vertex_t v, int& c, int& index_p){
// Auxiliary edge_iterator variables
    DiGraph::out_edge_iterator e, eend;

    int root = true;

    int v_idx = g[v].index;
    rindex[v_idx] = index_p;
    index_p++;

// Go over all neighbors of v
    for(boost::tie(e, eend) = out_edges(v, g); e != eend; ++e){
        vertex_t w = boost::target(*e, g);
        int w_idx = g[w].index;

        if(rindex[w_idx]==0)
            visitpearce2(rindex, S, g, w, c, index_p);

        if(rindex[w_idx] < rindex[v_idx]) {
            rindex[v_idx] = rindex[w_idx];
            root = false;
        }
    }

// Component identified, assign component identifiers to the corresponding vertices.
    if (root) {
        index_p--;
        while (!S.empty() && (rindex[v_idx] <= rindex[S.back()])){
            int w_idx = S.back();
            S.pop_back();
            rindex[w_idx] = c;
            index_p--;
        }
        rindex[v_idx] = c;
        c--;
    } else {
        S.push_back(v_idx);
    }
}

std::vector<int> pearce2_scc(DiGraph g){
//No need of .visited in vertex_t

// Number of vertices in g
    int num_vertices = boost::num_vertices(g);

// Vector of component identifiers to be returned by the algorithm.
    std::vector<int> rindex(num_vertices);
    int c = num_vertices-1;
    int index_p = 1;


// DS used by pearce2
    std::vector<int> S;

    DiGraph::vertex_iterator v, vend;

// Go over all vertices
    for(boost::tie(v, vend) = vertices(g); v != vend; ++v) {
        int v_idx = g[*v].index;
        if(rindex[v_idx]==0) {

            visitpearce2(rindex, S, g, *v, c, index_p);
        }
    }

    return rindex;
}
