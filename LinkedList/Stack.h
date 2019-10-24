#pragma once
#include "DoublyLinkedList.h"
namespace ds
{
	template<class T>
	class Stack: public DoublyLinkedList<T>
	{
	public:
		Stack() {};
		void push(T a);
		void pop();
		T top() const;
	};

	template<class T>
	void Stack<T>::push(T a)
	{
		insert(end(), a);
	};

	template<class T>
	void Stack<T>::pop()
	{
		delete_node(Iterator<>(pTail));
	};

	template<class T>
	T Stack<T>::top() const
	{
		return pTail->data;
	};
}