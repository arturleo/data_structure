#pragma once
#include<vector>
#include "../Linkedlist/DoublyLinkedList.h"

namespace ds
{
	struct Graph
	{
		// dest, length
		std::vector<std::vector<std::pair<int, int>>> neighbourLists;
	};
}