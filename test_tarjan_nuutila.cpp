#include <iostream>
#include <string>
#include <vector>
#include "SCC.hpp"
using namespace std;

void print(const DiGraph& g, vector<DiGraph>& scc){
    // Print out the graph
    print_graph(g, cout);

    cout << "Components: " << scc.size() << endl << endl;

    // Print found components
    vector<DiGraph>::iterator it;
    int i;

    for(i = 1, it = scc.begin(); it != scc.end(); ++it, ++i) {
        cout << "Component: " << i << endl;
        print_graph(*it, cout);
        cout << endl << endl;
    }
}

void test_tarjan(const DiGraph& g, bool verbose){
    vector<DiGraph> scc = tarjan_scc(g);
    if(verbose) print(g, scc);
}

void test_nuutila1(const DiGraph& g, bool verbose){
    vector<DiGraph> scc = nuutila1_scc(g);
    if(verbose) print(g, scc);
}

void test_nuutila2(const DiGraph& g, bool verbose){
    vector<int> scc = nuutila2_scc(g);
    if(verbose) cout << "Components: " << scc.size() << endl << endl;
}

void test_pearce1(const DiGraph& g, bool verbose){
    vector<int> scc = pearce1_scc(g);
    std::set<int> components(scc.begin(), scc.end());
    if(verbose) cout << "Components: " << components.size() << endl << endl;
}

void test_pearce2(const DiGraph& g, bool verbose){
    vector<int> scc = pearce2_scc(g);
    std::set<int> components(scc.begin(), scc.end());
    if(verbose) cout << "Components: " << components.size() << endl << endl;
}

int main(int argc, char** argv){
    // Generated random graph
    DiGraph g = rand_graph(20, 20, 151);

    test_pearce2(g, true);
}

