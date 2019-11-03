#pragma once
#include"Graph.h"

namespace ds
{
	template <class T>
	class DisjointSet
	{
	protected:
		T* P;
	public:
		DisjointSet()
		{
			P = NULL;
		}

		DisjointSet(int size)
		{
			P = new T[size]();
			for (int i = 0; i < size; i++)
			{
				P[i] = i;
			}
		}

		~DisjointSet()
		{
			delete P;
		}

		T parent(T a)
		{
			while (P[a] != a)
				a = P[a];
			return a;
		}

		void add(T p,T b)
		{
			P[parent(b)] = P[parent(p)];
			return;
		}
	};
}