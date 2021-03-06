#include"../Graph/Dijkstra.h"
#include"../Graph/Graph.h"
#include"../Graph/DisjointSet.h"
#include"../Graph/Kruskal.h"
#include"../Graph/Fleury.h"
#include"../Graph/Network_Flow/Dinic.h"
#include"../Graph/Network_Flow/EdmondKarp.h"
#include<vector>
using namespace ds;
template<class T> using vector = std::vector<T>;
using pair = std::pair<int, int>;
using vpi = std::vector<std::pair<int, int>>;
int main()
{
	/*
		   __f6___
		 1/	 |4  2|
		a1-3-b2-2-e5
		5|    \1  |3
		c3     d4--

	*/
	Graph g;
	vpi a, b, c, d, e, f;
	a.push_back(pair(2, 5));
	b.push_back(pair(0, 3));
	b.push_back(pair(4, 2));
	b.push_back(pair(3, 1));
	e.push_back(pair(3, 3));
	e.push_back(pair(2, 1));
	f.push_back(pair(0, 1));
	f.push_back(pair(1, 4));
	f.push_back(pair(4, 2));
	g.neighbourLists.push_back(a);
	g.neighbourLists.push_back(b);
	g.neighbourLists.push_back(c);
	g.neighbourLists.push_back(d);
	g.neighbourLists.push_back(e);
	g.neighbourLists.push_back(f);

	Dijkstra dij = Dijkstra(g);
	dij.run(5, 0, -1, 1);

	Kruskal ksk = Kruskal(g);
	ksk.run();

	g.neighbourLists[0].push_back(std::pair<int, int>(5, 1));
	g.neighbourLists[2].push_back(std::pair<int, int>(1, 1));
	g.neighbourLists[2].push_back(std::pair<int, int>(5, 1));
	g.neighbourLists[3].push_back(std::pair<int, int>(5, 1));
	g.neighbourLists[3].push_back(std::pair<int, int>(1, 1));
	Fleury flr = Fleury(g);
	flr.run();

	std::cout << "=====================Network Flow===========================\n";
	Graph g2;
	g2.neighbourLists.push_back(a);
	g2.neighbourLists.push_back(b);
	g2.neighbourLists.push_back(c);
	g2.neighbourLists.push_back(d);
	g2.neighbourLists.push_back(e);
	g2.neighbourLists.push_back(f);
	EdmondKarp ek = EdmondKarp(g2);
	std::cout << "outcome of Edmond-Karp:" << ek.run(5, 3) << std::endl;

	Dinic dc = Dinic(g2);
	std::cout << "outcome of Dinic:" << dc.run(5, 3) << std::endl;
	return 0;
}