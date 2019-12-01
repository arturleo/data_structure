#pragma once
#include"../Graph.h"
#include"NFEdge.h"
#include"../../LinkedList/Queue.h"
#include<algorithm>
namespace ds
{
#define INF (1<<16)
#define maxn (1<<16)
	template<class T> using vector = std::vector<T>;

	class EdmondKarp
	{

	private:
		vector<vector<int>> G;
		vector<NFEdge> edges;
	public:
		EdmondKarp(Graph gr)
		{
			int c = 0;
			for (int i = 0; i < gr.neighbourLists.size(); i++)
			{
				vector<int> g;
				for (int j = 0; j < gr.neighbourLists[i].size(); j++)
				{
					int ed = gr.neighbourLists[i][j].first;
					int v = gr.neighbourLists[i][j].second;
					g.push_back(c);
					edges.push_back(NFEdge{ i,ed,v });
					edges.push_back(NFEdge{ ed,i,0 });
					c += 2;
				}
				G.push_back(g);
			}
		};

		int run(int st, int ed)
		{
			int s = st, t = ed, a[maxn], p[maxn], flow=0;

			for (;;)
			{
				memset(a, 0, sizeof(a));
				a[s] = INF;
				Queue<int> q;
				q.push(s);
				int x;
				while (!q.empty())
				{
					x = q.front();
					q.pop();
					for (int i = 0; i < G[x].size(); i++)
					{
						NFEdge nfe = edges[G[x][i]];
						if (!a[nfe.ed] && nfe.cap - nfe.flow > 0)
						{
							a[nfe.ed] = std::min(a[x], nfe.cap - nfe.flow);
							p[nfe.ed] = G[x][i];
							q.push(nfe.ed);
						}
					}
					if (a[t])
						break;
				}
				if (!a[t])
					return flow;
				for (int i = t; i != s; i = edges[p[i]].st)
				{
					edges[p[i]].flow += a[t];
					edges[p[i] ^ 1].flow -= a[t];
				}
				flow += a[t];
			}
		}
	};
#undef maxn
#undef INF
}