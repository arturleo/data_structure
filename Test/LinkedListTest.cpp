#include<iostream>

#include"../LinkedList/DoublyLinkedList.h"
#include"../LinkedList/Queue.h"
#include"../LinkedList/Stack.h"

int main()
{
	//DoublyLinkedList
	ds::DoublyLinkedList<int>::Iterator<> itr1, itr2, itr;
	std::cout << (itr1 == itr2) << std::endl;
	ds::DoublyLinkedList<int> list = ds::DoublyLinkedList<int>();
	list.insert(list.begin(), 2);
	list.insert(list.begin(), 3);
	list.insert(list.begin(), 10);
	list.delete_node(list.begin() + 2);
	list.delete_node(list.begin());
	itr = list.find(0);
	itr = list.find(10);
	itr1 = list.find(3);

	//Stack
	ds::Stack<int> st = ds::Stack<int>();
	st.push(3);
	st.push(4);
	st.pop();
	std::cout << st.top() << std::endl;

	//Queue
	ds::Queue<int> qu = ds::Queue<int>();
	qu.push(2);
	qu.push(7);
	std::cout << qu.front() << std::endl;
	qu.pop();
	std::cout << qu.front() << std::endl;
	return 0;
}