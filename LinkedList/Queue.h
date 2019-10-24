#pragma once
#include "DoublyLinkedList.h"

namespace ds
{
	template <class T>
	class Queue :public DoublyLinkedList<T>
	{
	public:
		Queue() {};
		void push(T a);
		void pop();
		T front() const;
		T last() const;
	};

	template<class T>
	void Queue<T>::push(T a)
	{
		insert(end(), a);
	};

	template<class T>
	void Queue<T>::pop()
	{
		delete_node(begin());
	};

	template<class T>
	T Queue<T>::front() const
	{
		return pHead->data;
	};

	template<class T>
	T Queue<T>::last() const
	{
		return pTail->data;
	};
}