#pragma once
#include"Graph.h"
#include"DisjointSet.h"
#include"../Heap/Heap.h"
namespace ds
{
	template<class T> using vector = std::vector<T>;
	using vpi = std::vector<std::pair<int, int>>;
	class Kruskal
	{
	protected:
		Graph g;
	public:
		Kruskal(Graph gr) :g(gr)
		{}

		void run()
		{
			struct edge
			{
				int u, v, w;
			};

			class Comparator
			{
			public:
				bool operator()(edge a, edge b)
				{
					return a.w > b.w;
				}
			};
			int size = g.neighbourLists.size();
			DisjointSet<int> jds = DisjointSet<int>(size);
			Heap<edge, Comparator> heap;
			for (vector<vpi>::iterator itr = g.neighbourLists.begin(); itr != g.neighbourLists.end(); itr++)
			{
				int u = itr - g.neighbourLists.begin();
				for (vpi::iterator i2 = (*itr).begin(); i2 != (*itr).end(); i2++)
				{
					heap.insert(edge{ u,(*i2).first,(*i2).second });
				}
			}

			int gs=heap.first().u;
			while (!heap.empty())
			{
				edge e = heap.extract_first();
				if (jds.parent(e.v) == e.v)
				{
					jds.add(gs, e.v);
					std::cout << "u:" << e.u << ",v:" << e.v << ",w:" << e.w<<std::endl;
				}
			}
		}
	};

}