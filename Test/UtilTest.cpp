#include<algorithm>
#include<iostream>
#include"../Util/QuickSort.h"
#include"../Util/StringMatching.h"

using namespace ds;
int main()
{
	char a[] = "ni99hao199", b[] = "998";
	std::cout << knuth_morris_pratt(a, b);
	char a2[] = "ni99hao1998", b2[] = "998";
	std::cout << knuth_morris_pratt(a2, b2);

	int list[] = { 1,1,54,24,235,435,4189,3,54,428 };
	int list2[10];
	std::copy(list, list + 10, list2);
	quickSortRecurrence(list, 1, 9);
	quickSortNoRecurrence(list2);
	return 0;
}