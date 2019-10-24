# pragma once
# include"Graph.h"
# include"../Heap/Heap.h"
# include"../Linkedlist/DoublyLinkedList.h"

# include<iostream>
# include<sstream>
#include<vector>

#define MAX 10000;
template<class T> using vector = std::vector<T>;
using vpi = std::vector<std::pair<int, int>>;
namespace ds
{
	//for sparce graph
	//Lose Kopplung
	class Dijkstra
	{
	private:
		Graph g;

	public:
		Dijkstra(Graph gr) :g(gr) {};
		int* run(int source, int fh = 0, int d = -1, int print = 0);
	};

	int* Dijkstra::run(int source, int fh, int d, int print)
	{
		struct Event
		{
			int idx;
			int dis;
			bool operator<(const Event& b)
			{
				// small first
				return dis > b.dis;
			}
		};

		struct EventComparator
		{
			bool operator()(Event a, Event b)
			{
				return a.dis > b.dis;
			}
		};

		Event sp = Event{ source, 0 };

		////Todo Febonacci Heap
		Heap<Event, EventComparator> q;
		if (!fh)
			Heap<Event, EventComparator> q = Heap<Event, EventComparator>();
		q.push(sp);

		int* visited = new int[g.neighbourLists.size()](),
			* p = new int[g.neighbourLists.size()](),
			* dis = new int[g.neighbourLists.size()]();

		while (!q.empty())
		{
			Event t = q.front();
			q.pop();

			if (visited[t.idx])
				continue;

			vector<vpi>::iterator i = g.neighbourLists.begin() + t.idx;
			vpi nbs = *i;
			for (vpi::iterator itr = nbs.begin(); itr != nbs.end(); itr++)
				if (!visited[itr->first])
				{
					p[itr->first] = t.idx;
					q.push(Event{ itr->first, t.dis + itr->second });
				}
			dis[t.idx] = t.dis;
			visited[t.idx] = 1;
		};

		std::stringstream ss;
		std::string st, tmp;
		//print
		if (d != -1)
		{
			if (dis[d] != 0 || d == source)
			{
				ss << "distance of " << d << " is " << dis[d] << std::endl;
				st += ss.str();
				ss.str(std::string());
				if (print)
				{
					ss << d;
					while (d != source)
					{
						tmp = ss.str();
						ss.str(std::string());
						ss << p[d] << " " << tmp;
						d = p[d];
					};
					ss << "\n";
				}
				st += ss.str();
				ss.str(std::string());
			}
			else
			{
				ss << "There's no path to " << d << ".\n";
				st += ss.str();
				ss.clear();
			}
		}
		else
		{
			for (int tii = 0; tii < g.neighbourLists.size(); tii++)
			{
				int ti = tii;
				if (dis[ti] != 0 || ti == source)
				{
					ss << "distance of " << ti << " is " << dis[ti] << std::endl;
					st += ss.str();
					ss.str(std::string());

					if (print)
					{
						ss << ti;
						while (ti != source)
						{
							tmp = ss.str();
							ss.str(std::string());
							ss << p[ti] << " " << tmp;
							ti = p[ti];
						};
						ss << "\n";
					}
					st += ss.str();
					ss.str(std::string());
				}
				else
				{
					ss << "There's no path to " << ti << ".\n";
					st += ss.str();
					ss.clear();
				}
			}
		}
		std::cout << st;
		return dis;
	}
}

