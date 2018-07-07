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

	clock_t start = clock();

	DiGraph g = gen_rand_graph(5, 0.5, 150);

	clock_t end = clock();

	boost::print_graph(g);

	cout << "Time to create random graph: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	start = clock();

	vector<DiGraph> scc = tarjan_scc(g);

	end = clock();

	cout << "Components: " << scc.size() << ". Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

	vector<DiGraph>::iterator it;

	for(it = scc.begin(); it != scc.end(); ++it)
		boost::print_graph(*it);
}
