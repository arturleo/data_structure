#include<algorithm>
#include<iostream>
#include"../LinkedList/Stack.h"

namespace ds
{
	template <class T>
	void quickSortRecurrence(T* lst, int lIdx, int sIdx)
	{
		T pivot=lst[lIdx-1];
		int l=lIdx, r=sIdx;

		while(sIdx>lIdx){	
			while(lst[lIdx]<=pivot&&lIdx<r)
				lIdx++;
			while(lst[sIdx]>=pivot&&sIdx>l)
				sIdx--;
			if(sIdx>lIdx)
				std::swap(lst[sIdx],lst[lIdx]);
		}
		
		if(lst[sIdx]<pivot)
			std::swap(lst[sIdx], lst[l - 1]);
		if(l+1<=sIdx)
			quickSortRecurrence(lst, l, sIdx-1);
		if(lIdx+1<=r)
			quickSortRecurrence(lst, lIdx+1, r);
	}
	
	template <class T>
	int partition(T* list, int lIdx, int sIdx)
	{
		T pivot = list[lIdx - 1];
		int l = lIdx, r = sIdx;
		while (sIdx > lIdx) {
			while (list[lIdx] <= pivot && lIdx < r)
				lIdx++;
			while (list[sIdx] >= pivot && sIdx > l)
				sIdx--;
			if (sIdx > lIdx)
				std::swap(list[sIdx], list[lIdx]);
		}
		if (list[sIdx] < pivot)
			std::swap(list[sIdx], list[l - 1]);
		return lIdx;
	}

	template <typename T, size_t size>
	void quickSortNoRecurrence(T(&list)[size])
	{
		Stack<int> stack = Stack<int>();
		stack.push(1);
		stack.push(size - 1);
		while (!stack.empty())
		{
			int r = stack.top();
			stack.pop();
			int l = stack.top();
			stack.pop();
			int m = partition(list, l, r);
			if (l + 1 <= m)
			{
				stack.push(l);
				stack.push(m-1);
			}
			if (m + 1 <= r)
			{
				stack.push(m + 1);
				stack.push(r);
			}
		}
	}
}

