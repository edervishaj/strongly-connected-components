/*
 * test.cpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */


#include <ctime>
#include <iostream>
#include <fstream>
#include <boost/graph/graph_utility.hpp>
#include "SCC.hpp"
using namespace std;

int main(){
//	ofstream outfile;
//	outfile.open("graph.txt", ofstream::out);

	clock_t start = clock();

	DirectedGraph g = gen_rand_graph(5, 0.5, 150);

	clock_t end = clock();

	cout << "Time elapsed: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	boost::print_graph(g);

//	outfile.close();

	vector<DirectedGraph> scc = tarjan_scc(g);
	cout << scc.size() << endl;
//	boost::print_graph(scc[0]);
}
