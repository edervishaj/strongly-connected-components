/*
 * test.cpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */


#include <ctime>
#include <iostream>
#include <fstream>
#include "SCC.hpp"
using namespace std;

int main(){

	fstream f;

	f.open("../graph.txt", ios_base::out);

	clock_t start = clock();

//	DiGraph g = rand_graph(20, 0.2, 151);
    vector<int> cc;
    cc.push_back(3);
    cc.push_back(4);
//    DiGraph g = n_rand_graph(cc, 20, 0.1, true, 150);

//  DiGraph g;
//	vertex_t _0 = add_vertex({0, false}, g);
//	vertex_t _1 = add_vertex({1, false}, g);
//	vertex_t _2 = add_vertex({2, false}, g);
//	vertex_t _3 = add_vertex({3, false}, g);
//
//	//add_edge(_0, _1, g);
//	add_edge(_1, _2, g);
//	add_edge(_2, _3, g);
//	add_edge(_3, _1, g);

//    As seen in the interactive tool at http://www.timl.id.au/SCC
    DiGraph g;
    vertex_t _0 = add_vertex({0, false}, g);
    vertex_t _1 = add_vertex({1, false}, g);
    vertex_t _2 = add_vertex({2, false}, g);
    vertex_t _3 = add_vertex({3, false}, g);
    vertex_t _4 = add_vertex({4, false}, g);
    vertex_t _5 = add_vertex({5, false}, g);
    vertex_t _6 = add_vertex({6, false}, g);
    vertex_t _7 = add_vertex({7, false}, g);
    vertex_t _8 = add_vertex({8, false}, g);
    vertex_t _9 = add_vertex({9, false}, g);

    add_edge(_0, _1, g);
    add_edge(_1, _2, g);
    add_edge(_2, _3, g);
    add_edge(_3, _1, g);
    add_edge(_2, _7, g);
    add_edge(_0, _4, g);
    add_edge(_4, _0, g);
    add_edge(_4, _5, g);
    add_edge(_5, _6, g);
    add_edge(_6, _4, g);
    add_edge(_4, _1, g);
    add_edge(_8, _9, g);
    add_edge(_9, _8, g);



    clock_t end = clock();

	print_graph(g, cout);

	cout << "Time to create random graph: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	start = clock();

	vector<DiGraph> scc = create_scc( pearce2_scc(g), g);
//	vector<DiGraph> scc = nuutila1_scc(g);

	end = clock();

	cout << "Components: " << scc.size() << ". Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	vector<DiGraph>::iterator it;
	int i;

	for(i = 0, it = scc.begin(); it != scc.end(); ++it, ++i) {
		cout << "Component: " << (i+1) << endl;
		print_graph(*it, cout);
		cout << endl;
	}

	f.close();

	return 0;
}
