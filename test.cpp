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

	DiGraph g = rand_graph(5, 0.5, 150);

//    DiGraph g;
//	vertex_t _0 = add_vertex({0, false}, g);
//	vertex_t _1 = add_vertex({1, false}, g);
//	vertex_t _2 = add_vertex({2, false}, g);
//	vertex_t _3 = add_vertex({3, false}, g);
//
//	//add_edge(_0, _1, g);
//	add_edge(_1, _2, g);
//	add_edge(_2, _3, g);
//	add_edge(_3, _1, g);

	clock_t end = clock();

	print_graph(g, cout);

	cout << "Time to create random graph: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	start = clock();

	vector<int> scc = nuutila2_scc(g);

	end = clock();

	cout << "Components: " << scc.size() << ". Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	vector<int>::iterator it;
	int i;

	for(i = 0, it = scc.begin(); it != scc.end(); ++it, ++i) {
		cout << "Root Component: " << (i+1) << endl;
//		print_graph(*it, cout);
        cout << *it << endl;
		cout << endl;
	}

	f.close();

	return 0;
}
