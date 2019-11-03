#include"Graph.h"
#include"../LinkedList/Stack.h"
namespace ds
{
	template<class T> using vector = std::vector<T>;
	using vpi = std::vector<std::pair<int, int>>;
	class Fleury
	{
	protected:
		Graph g;
	public:
		Fleury(Graph gr) :g(gr)
		{}

		void run()
		{

			//check existence
			int size = g.neighbourLists.size();
			int* d = new int[size]();
			vector<vpi> edges = g.neighbourLists;// deep copy
			for (vector<vpi>::iterator itr = g.neighbourLists.begin(); itr != g.neighbourLists.end(); itr++)
			{
				int u = itr - g.neighbourLists.begin();
				for (vpi::iterator i2 = (*itr).begin(); i2 != (*itr).end(); i2++)
				{
					int v = (*i2).first;
					int w = (*i2).second;
					d[u]++;
					d[v]--;
				}
			}
			int isEulerCycle = 1, f = 0, last[2] = { -1,-1 };
			for (int i = 0; i < size; i++)
			{
				if (d[i])
				{
					isEulerCycle = 0;
					if (!f)
					{
						f = d[i];
						last[0] = i;
					}
					else
					{
						f += d[i];
						last[0] = i;
						break;
					}
				}
			}
			if (!f)
			{
				int s;
				if (isEulerCycle)
				{
					s = 0;
					std::cout << "There is an Euler cycle.\n";
				}
				else
				{
					s = last[0];
					std::cout << "There is no Euler cycle but Euler circuit.\n";
				}

				Stack<int> st;
				st.push(s);
				//print the bridge at last
				while (!st.empty())
				{
					int i = st.top(), i0 = i;

					int bridge = 1;
					if (!edges.at(i).empty())
					{
						i0 = i;
						i = edges.at(i).at(0).first;
						st.push(i);
						edges.at(i0).erase(edges.at(i0).begin() + 0);
						bridge = 0;
					}

					if (bridge)
					{
						std::cout << " " << i;
						st.pop();
					}
					else
					{
						//dfs
						while (!edges.at(i).empty())
						{
							i0 = i;
							i = edges.at(i).at(0).first;
							st.push(i);
							edges.at(i0).erase(edges.at(i0).begin() + 0);
						}
					}
				}
				std::cout << "\n";
			}
			else
			{
				std::cout << "There is no Euler circuit.\n";
			}
		}
	};
}