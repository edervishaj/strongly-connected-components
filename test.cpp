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

//	DiGraph g = gen_rand_graph(5, 0.5, 150);

    DiGraph g;
	vertex _0 = add_vertex({0, false}, g);
	vertex _1 = add_vertex({1, false}, g);
	vertex _2 = add_vertex({2, false}, g);
	vertex _3 = add_vertex({3, false}, g);

	//add_edge(_0, _1, g);
	add_edge(_1, _2, g);
	add_edge(_2, _3, g);
	add_edge(_3, _1, g);

	clock_t end = clock();

	print_graph(g, cout);

	cout << "Time to create random graph: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	start = clock();

	vector<DiGraph> scc = nuutila1_scc(g);

	end = clock();

	cout << "Components: " << scc.size() << ". Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	vector<DiGraph>::iterator it;
	int i;

	for(i = 0, it = scc.begin(); it != scc.end(); ++it, ++i) {
		cout << "Component: " << i << endl;
		print_graph(*it, cout);
		cout << endl;
	}

	f.close();

	return 0;
}
