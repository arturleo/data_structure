#include<iostream>
#include"../Heap/Heap.h"

int main()
{
	int list[] = { 1,1,54,24,235,435,4189,3,54,428 };
	ds::Heap<int> heap = ds::Heap<int>(), heap2 = ds::Heap<int>(list);
	heap.insert(1);
	heap.insert(3);
	heap.insert(4);

	std::cout << heap2.first() << "\n";
	std::cout << heap2;
	heap2.increase_key(5, 435);
	heap2.insert(200);
	heap2.extract_first();
	heap2.sort();
	return 0;
}