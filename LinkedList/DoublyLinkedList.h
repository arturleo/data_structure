#pragma once
#include <exception>
#include <iostream>
#include <cassert>
#include <type_traits>

namespace ds
{
	template <class T>
	class DoublyLinkedList
	{
	protected:
		struct Node
		{
			T data;
			Node* last, * next;
			Node(T d = T()) : data(d), last(nullptr), next(nullptr) {};
			Node(const Node& b) :data(b.data), last(b.last), next(b.next) {};
			virtual ~Node() {};
			bool operator<(Node const& b) { return data - b.data; }
		};
		int pSize;
		Node* pHead, * pTail;

	public:

		template <bool is_const = false>
		struct Iterator
		{
			//it can't be random_access_iterator_tag since the pointer are not stored in a sequence,
			// so std::sort cannot be applied
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename std::conditional<is_const, const Node, Node>::type value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename std::conditional<is_const, const Node*, Node*>::type pointer;
			typedef typename std::conditional<is_const, const Node&, Node&>::type reference;

			using It = Iterator;

			pointer node;
			Iterator(pointer b = NULL) :node{ reinterpret_cast<pointer>(b) } {};
			// If IsConst, defines an implicit conversion.
			// If !IsConst, defines a copy constructor.
			Iterator(const Iterator<>& b) :node(b.node) {};
			virtual ~Iterator() {};

			operator bool()const { return node != nullptr; }
			////fix: add ampersand
			It& operator=(const It& b) & = default;

			//reference
			template< bool _Const = is_const >
			std::enable_if_t< _Const, reference > operator*() const 
			{
				assert(node != NULL && "Invalid iterator dereference!");
				return *node; 
			};

			template< bool _Const = is_const >
			std::enable_if_t< !_Const, reference > operator*()
			{
				assert(node != NULL && "Invalid iterator dereference!");
				return *node;
			};

			//pointer
			pointer operator->() const
			{
				assert(node != NULL && "Invalid iterator dereference!");
				return node;
			};

			It& operator++()
			{
				assert(node != NULL && "Invalid iterator dereference!");
				node = (*this)->next;
				return *this;
			}
			It operator++(int)
			{
				assert(node != NULL && "Invalid iterator dereference!");
				It b = *this;  ++(*this);
				return b;
			}
			It& operator--()
			{
				assert(node != NULL && "Invalid iterator dereference!");
				node = (*this)->last;
				return *this;
			}
			It operator--(int)
			{
				assert(node != NULL && "Invalid iterator dereference!");
				It b = *this; --(*this);
				return b;
			}

			friend bool operator==(const It& a, const It& b) { return a.node == b.node; }

			friend bool operator!=(const It& a, const It& b) { return !(a == b); }

			template <typename Z>
			struct is_integral {
				static bool const value = std::numeric_limits<Z>::is_integer;
			};
			template <typename Integral>
			typename std::enable_if<is_integral<Integral>::value, It>::type
				operator+(Integral v) const
			{
				It b = *this;
				for (Integral i = 0; i < v; i++)
					++b;
				return b;
			}

			// in fact below should not exist
			template <typename Integral>
			typename std::enable_if<is_integral<Integral>::value, It&>::type
				operator+=(Integral v) { for (Integral i = 0; i < v; i++)++(*this);  return *this; }
			template <typename Integral>
			typename std::enable_if<is_integral<Integral>::value, It>::type
				operator-(Integral v) const { It b = *this; for (Integral i = 0; i < v; i++)--b; return b; }
			template <typename Integral>
			typename std::enable_if<is_integral<Integral>::value, It&>::type
				operator-=(Integral v) { for (Integral i = 0; i < v; i++)--(*this); return *this; }
			template <typename Integral>
			typename std::enable_if<is_integral<Integral>::value, It&>::type
				operator[](Integral v) const { It b = *this; b += v; return b; }
		};

		DoublyLinkedList();
		DoublyLinkedList(const DoublyLinkedList<T>& dll);
		virtual ~DoublyLinkedList();
		void clear();
		int empty() const { return pSize == 0; };
		Iterator<true> cbegin() const { return Iterator<true>((const Node*)pHead); }
		Iterator<true> cend() const { return Iterator<true>(NULL); }
		Iterator<> begin() const { return Iterator<>(pHead); }
		Iterator<> end() const { return Iterator<>(NULL); }
		const int size() const;
		Iterator<> find(T d) const;
		void insert(Iterator<> itr, T data);
		void delete_node(Iterator<> itr);

		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<U>& dlt);
	};

	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList() :pSize(0)
	{
		pHead = pTail = NULL;
		pSize = 0;
	};

	// deep copy
	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
	{
		pHead = pTail = NULL;
		pSize = 0;
		for (Iterator<> i = dll.begin(); i != dll.end();++i)
		{
			insert(end(),i->data);
		}
	};

	template <class T>
	DoublyLinkedList<T>::~DoublyLinkedList()
	{
		clear();
	}

	template <class T>
	void DoublyLinkedList<T>::clear()
	{
		for (Iterator<> i = begin(); i != end();)
		{
			Iterator<> t = i;
			++i;
			delete&* t;
		}
		pSize = 0;
	}

	// to declear it is a type, use "typename" here
	template <class T>
	typename DoublyLinkedList<T>::Iterator<> DoublyLinkedList<T>::find(T d) const
	{
		for (Iterator<> itr = begin(); itr != end(); ++itr)
		{
			if (itr->data == d)
				return itr;
		}
		return Iterator<>();
	}

	//insert before
	template <class T>
	void DoublyLinkedList<T>::insert(Iterator<false> itr, T data)
	{
		Node* n = new Node(data);

		if (pSize == 0)
		{
			if (pHead)
				delete pHead;

			pTail = pHead = n;
			pSize++;
			return;
		}

		if (itr != cend())
		{
			if ((itr - 1) != cend())
			{
				Node& node = *(itr - 1);
				n->last = &node;
				(itr - 1)->next = n;
			}
		}
		else
		{
			pTail->next = n;
			n->last = pTail;
			pTail = n;
		}

		if (itr != cbegin())
		{
			if (itr != cend())
			{
				n->next = &*itr;
				itr->last = n;
			}
		}
		else
		{
			pHead->last = n;
			n->next = pHead;
			pHead = n;
		}
		pSize++;
	}

	template <class T>
	const int DoublyLinkedList<T>::size() const
	{
		return pSize;
	}

	//avoid random pointer of itr
	template <class T>
	void DoublyLinkedList<T>::delete_node(Iterator<> itr)
	{
		if (itr == cend())
			return;

		if (itr == cbegin() && (itr + 1) == cend())
		{
			pTail = nullptr;
			pHead = nullptr;
			pSize = 0;
			return;
		}

		if (itr == cbegin())
			pHead = &*(itr + 1);
		else
			(itr - 1)->next = itr->next;

		if ((itr + 1) == cend())
			pTail = &*(itr - 1);
		else
			(itr + 1)->last = itr->last;

		delete(&*itr);
		--pSize;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& dlt)
	{
		for (DoublyLinkedList<T>::Iterator<true> itr = dlt.cbegin(); itr != dlt.cend(); ++itr)
		{
			os << itr->data << " ";
		}
		os << std::endl;
		return os;
	}
}