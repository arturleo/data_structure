#pragma once

#include<iostream>
#include<algorithm>
#include<cmath>
#include<exception>

namespace ds
{
	//template <typename T>
	//int default_comparator(T a, T b)
	//{
	//	return a - b;
	//}

	//template <typename T, int (*cmp)(T, T) = default_comparator<T>>
	template <class T, typename C=std::less<>>
	class Heap
	{
	protected:
		int pSize;
		T* p;
		void heapify(int i, int length);
		void build_heap();;
	public:
		Heap();
		template<std::size_t sz>
		explicit Heap(T(&d)[sz]);
		~Heap();
		void sort();
		T extract_first();
		void increase_key(int index, T bigger);
		void insert(T data);
		T first() const;
		int size() const;
		void clear();
		void push(T d) { insert(d); };
		void pop() { extract_first(); };
		T front() const { return first(); };
		bool empty() const { return pSize == 0; };

		//template <typename U, int (*cmp2)(U, U)>
		template <class U, typename C = std::less<>>
		friend std::ostream& operator<<(std::ostream& os, const Heap<U, C>& hp);
	};

	template <class T, typename C>
	Heap<T, C>::Heap()
	{
		pSize = 0;
		p = NULL;
	}

	template <class T, typename C>
	template<std::size_t sz>
	Heap<T, C>::Heap(T(&d)[sz])
	{
		pSize = sz;
		p = new T[pSize];
		std::copy(d, d + pSize, p);
		build_heap();
	}

	template <class T, typename C>
	Heap<T, C>::~Heap()
	{
		clear();
	}

	// put the i node at the lowest position
	template <class T, typename C>
	void Heap<T, C>::heapify(int i, int length)
	{
		C c = C();
		int last = i, big = i, l = 0, r = 0;
		while (big < length)
		{
			l = 2 * big + 1, r = 2 * big + 2;
			last = big;
			if (l < length && c(p[big], p[l]))
				big = l;

			if (r < length && c(p[big], p[r]))
				big = r;

			if (big > last)
				std::swap(p[last], p[big]);
			else
				break;
		}
	}

	// from the second last layer to top.
	template <class T, typename C>
	void Heap<T, C>::build_heap()
	{
		long last = 0.00001 + log(pSize) / log(2.0);
		for (long i = pow(2, last) - 2; i >= 0; i--)
			heapify(i, pSize);
	}

	template <class T, typename C>
	int Heap<T, C>::size() const
	{
		return pSize;
	}

	template <class T, typename C>
	void Heap<T, C>::sort()
	{
		build_heap();
		for (int i = pSize; i >= 2; i--)
		{
			std::swap(p[0], p[i - 1]);
			heapify(0, i - 1);
		}
		for (int i = pSize; i >= pSize / 2; i--)
			std::swap(p[i], p[pSize - i - 1]);
	}

	template <class T, typename C>
	T Heap<T, C>::first() const
	{
		return p[0];
	}

	template <class T, typename C>
	T Heap<T, C>::extract_first()
	{
		T out = first();
		std::swap(p[0], p[pSize - 1]);
		pSize--;
		heapify(0, pSize-1);
		return out;
	}

	template <class T, typename C>
	void Heap<T, C>::increase_key(int index, T bigger)
	{
		C c = C();
		if (index >= pSize)
			throw std::exception("index out of range");

		if (c(bigger, p[index]))
			throw std::exception("new datum should be larger");
		else
		{
			p[index] = bigger;
			int cur = index, par = cur / 2 - 1 + cur % 2;
			while (par >= 0 && c(p[par], bigger))
			{
				std::swap(p[cur], p[par]);
				cur = par, par = cur / 2 - 1 + cur % 2;
			}
		}
	}

	template <class T, typename C>
	void Heap<T, C>::insert(T data)
	{
		C c = C();
		// new allocate
		pSize++;
		T* temp = p;
		p = new T[pSize];
		if (temp) {
			std::copy(temp, temp + pSize - 1, p);
			delete temp;
		}

		// similar to func:increase_key
		p[pSize - 1] = data;
		int cur = pSize - 1, par = cur / 2 - 1 + cur % 2;
		while (par >= 0 && c(p[par], data))
		{
			std::swap(p[cur], p[par]);
			cur = par, par = cur / 2 - 1 + cur % 2;
		}
		
	}

	template <class T, typename C>
	void Heap<T, C>::clear()
	{
		delete p;
		p = NULL;
	}

	template <class T, typename C>
	std::ostream& operator<<(std::ostream& os, const Heap<T, C>& hp)
	{
		int i = 0;
		os << "heap: [" << hp.p[i];
		while (++i < hp.pSize)
			os << "," << hp.p[i];
		os << "]\n";
		return os;
	}
}