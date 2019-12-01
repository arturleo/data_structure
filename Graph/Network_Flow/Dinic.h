#include"../Graph.h"
#include"NFEdge.h"
#include"../../LinkedList/Queue.h"
#include<algorithm>
namespace ds
{
#define maxn (1<<16)
#define INF (1<<16)

	template<class T> using vector = std::vector<T>;

	class Dinic
	{

	private:
		int level[maxn], s, t;
		vector<vector<int>> G;
		vector<NFEdge> edges;
	public:
		Dinic(Graph gr)
		{
			s = t = 0;
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
					c+=2;
				}
				G.push_back(g);
			}
		};
		int BFS()
		{
			Queue<int> q;
			q.push(s);
			int vis[maxn];
			memset(vis, 0, sizeof(vis));
			memset(level, 0, sizeof(level));
			level[s] = 0;
			while (!q.empty())
			{
				int x = q.front();
				q.pop();
				for (int i = 0; i < G[x].size(); i++)
				{
					NFEdge nfe = edges[G[x][i]];
					if (!vis[nfe.ed] && nfe.cap - nfe.flow > 0)
					{
						vis[nfe.ed] = 1;
						level[nfe.ed] = level[x] + 1;
						q.push(nfe.ed);
					}
				}
			}
			return vis[t];
		}

		int DFS(int x, int l)
		{
			if (x == t || l == 0) return l;
			int f = 0, flow = 0;
			for (int i = 0; i < G[x].size(); i++)
			{
				NFEdge e = edges[G[x][i]];

				if (level[e.ed] == level[x] + 1
					&& (f = DFS(e.ed, std::min(l, e.cap - e.flow)) > 0))
				{
					l -= f;
					edges[G[x][i]].flow += f;
					edges[G[x][i] ^ 1].flow -= f;
					flow += f;
					if (l == 0) break;
				}
			}
			return flow;
		}

		int run(int st, int ed)
		{
			s = st, t = ed;
			int flow = 0;
			while (BFS())
			{
				flow += DFS(st, maxn);
			}
			return flow;
		}
	};
#undef maxn
#undef INF
}