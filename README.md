# Identifying Strongly Connected Components

Link to the presentation in [Google Drive] (https://docs.google.com/presentation/d/1A-0Lla9cnaPZZLTLoLQ37v8f7kyeFIkkNRVAkbhhtSY/edit?usp=sharing)

This repository contains implementations for 3 different algorithms used to identify strongly connected components in directed graphs:

1. Tarjan, Robert. "Depth-first search and linear graph algorithms." SIAM journal on computing 1.2 (1972): 146-160.
2. Nuutila, Esko, and Eljas Soisalon-Soininen. "On finding the strongly connected components in a directed graph." Inf. Process. Lett. 49.1 (1994): 9-14.
3. Pearce, David J. "A space-efficient algorithm for finding strongly connected components." Information Processing Letters 116.1 (2016): 47-52.

To generate graphs to test the algorithms 4 different approaches are used:

* _G(n,p)_ : generates a graph _G_ with _n_ vertices and adds edges between any pair of vertices with probability _p_.
* _G(n,m)_ : generates a graph _G_ with _n_ vertices and adds _m_ edges to randomly sampled start and end vertices.
* In order to have a predetermined minimum number of strongly connected components in the generated graph, cycles (a cycle is an SCC) with fixed/random number of vertices are created and added to the graph (the cycles are disconnected -- downside).
* From the above generated cycles, edges are added using _G(n,p)_ starting from a graph _g_.
