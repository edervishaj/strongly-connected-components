/*
 * test.cpp
 *
 * Author: Ervin Dervishaj
 * Email: vindervishaj@gmail.com
 */


#include "Common.hpp"
#include <ctime>
#include <iostream>
#include <boost/graph/graph_utility.hpp>
using namespace std;

int main(){
	clock_t start = clock();

	DirectedGraph g = gen_rand_graph(5, 0.5);

	clock_t end = clock();

	cout << "Time elapsed: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	boost::print_graph(g);
}
