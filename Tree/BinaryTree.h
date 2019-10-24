#pragma once
#include"../LinkedList/DoublyLinkedList.h"
#include"../LinkedList/Queue.h"
#include"../LinkedList/Stack.h"
#include<cstdio>
#include<iostream>
#include<vector>
#include<set>
#include <algorithm>    // std::copy

template<class T> using vector = std::vector<T>;
template<class T> using set = std::set<T>;

namespace ds
{
	template<class T>
	class BinarySearchTree;

	template<class T>
	class HuffmanTree;

	template<class T>
	class AVLTree;

	template<class T>
	class BinaryTree
	{
		friend class BinarySearchTree<T>;
		friend class HuffmanTree<T>;
		friend class AVLTree<T>;
	public:
		struct Node
		{
			T data;
			Node* lchild, * rchild, * parent;
			//copy constructor
			Node(const Node& n) :data(T(n.data))
			{
				parent = lchild = rchild = NULL;
				//recursive
				if (n.lchild)
				{
					lchild = new Node(n.lchild);
					lchild->parent = this;
				}
				if (n.rchild)
				{
					rchild = new Node(n.rchild);
					rchild->parent = this;
				}
			};
			explicit Node(const Node* const n) :data(T(n->data))
			{
				parent = lchild = rchild = NULL;
				//recursive
				if (n->lchild)
				{
					lchild = new Node(n->lchild);
					lchild->parent = this;
				}
				if (n->rchild)
				{
					rchild = new Node(n->rchild);
					rchild->parent = this;
				}
			};
			explicit Node(T d = T()) :data(d), lchild(NULL), rchild(NULL), parent(NULL) {};
			virtual ~Node() {};
		};
		BinaryTree() :root(NULL), pSize(0) {};
		BinaryTree(const BinaryTree& bt);
		BinaryTree(Node* n, int size) :root(n), pSize(size) {};
		virtual ~BinaryTree();
		virtual void delete_node(Node* x);
		void clear();
		size_t size() const { return pSize; };
		Queue<T> in_order() const;
		Queue<T> pre_order() const;
		Queue<T> post_order() const;

		template<class A>
		friend std::ostream& operator<< (std::ostream& os, const BinaryTree<A>& BT);

	protected:
		size_t pSize;
		Node* root;
		virtual void rotate_right(Node* x);
		virtual void rotate_left(Node* x);
	};

	template <class T>
	BinaryTree<T>::BinaryTree(const BinaryTree& bt)
	{
		pSize = bt.pSize;
		root = new Node(bt.root);
	}

	template <class T>
	BinaryTree<T>::~BinaryTree()
	{
		clear();
	}

	template<class T>
	void BinaryTree<T>::clear()
	{
		while (pSize > 0)
			delete_node(root);
	}

	template<class T>
	void BinaryTree<T>::rotate_right(Node* x)
	{
		//allow x->rchild to be NULL
		Node* y = x->lchild;
		//parent link
		if (!x->parent)
			root = y;
		else if (x->parent->lchild == x)
			x->parent->lchild = y;
		else if (x->parent->rchild == x)
			x->parent->rchild = y;
		if (y) {
			y->parent = x->parent;

			x->lchild = y->rchild;
			if (y->rchild)
				y->rchild->parent = x;

			y->rchild = x;
		}
		x->parent = y;

	}

	template<class T>
	void BinaryTree<T>::rotate_left(Node* x)
	{
		Node* y = x->rchild;
		//parent link
		if (!x->parent)
			root = y;
		else if (x->parent->lchild == x)
			x->parent->lchild = y;
		else if (x->parent->rchild == x)
			x->parent->rchild = y;
		if (y)
		{
			y->parent = x->parent;

			x->rchild = y->lchild;
			if (y->lchild)
				y->lchild->parent = x;

			y->lchild = x;
		}
		x->parent = y;

	}

	template<class T>
	void BinaryTree<T>::delete_node(Node* x)
	{
		pSize--;
		while (x)
		{
			if (x->lchild)
				rotate_right(x);
			else if (x->rchild)
				rotate_left(x);
			else
			{
				rotate_left(x);
				delete x;
				x = NULL;
			}
		}
	}

	template<class T>
	Queue<T> BinaryTree<T>::pre_order() const
	{
		Queue<T> q;
		Stack<Node*> stk;
		stk.push(root);
		while (!stk.empty())
		{
			Node* cur = stk.top();
			stk.pop();
			q.push(cur->data);
			if (cur->rchild)
				stk.push(cur->rchild);
			if (cur->lchild)
				stk.push(cur->lchild);
		}
		return q;
	}

	template<class T>
	Queue<T> BinaryTree<T>::in_order() const
	{
		Queue<T> q;
		Stack<Node*> stk;
		stk.push(root);
		Node* cur = root;
		while (!stk.empty())
		{
			//left
			while (cur->lchild)
			{
				cur = cur->lchild;
				stk.push(cur);
			}

			//push right branch
			while (!stk.empty())
			{
				cur = stk.top();
				q.push(stk.top()->data);
				stk.pop();
				cur = cur->rchild;
				if (cur)
				{
					stk.push(cur);
					break;
				}
			}
		}
		return q;
	}

	template<class T>
	Queue<T> BinaryTree<T>::post_order() const
	{
		Queue<T> q;
		Stack<Node*> stk;
		stk.push(root);
		Node* cur = root;
		while (!stk.empty())
		{
			//left
			while (cur->lchild)
			{
				cur = cur->lchild;
				stk.push(cur);
			}

			//push right branch
			while (!stk.empty())
			{
				cur = stk.top();
				q.push(stk.top()->data);
				stk.pop();
				if (cur->parent && cur == cur->parent->lchild)
				{
					cur = cur->parent->rchild;
					if (cur)
					{
						stk.push(cur);
						break;
					}
				}
			}
		}
		return q;
	}

	template<typename T>
	std::ostream& operator<< (std::ostream& os, const BinaryTree<T>& bt)
	{
		os << bt.in_order();
		return os;
	}

	//bfs
	template<class A>
	BinaryTree<A> build_tree_from_pre_in(vector<A> pre_o, vector<A> in_o)
	{
		using Node = BinaryTree<A>::Node;
		Queue<Node*> q;
		Queue<vector<A>> ql;
		Node* first = new Node(pre_o.at(0));
		ql.push(pre_o);
		ql.push(in_o);
		q.push(first);

		while (!ql.empty())
		{
			vector<A> a1, b1, a2, b2, a0, b0;
			a0 = ql.front();
			ql.pop();
			b0 = ql.front();
			ql.pop();
			if (!b0.size())
			{
				continue;
			}
			vector<A>::iterator p = std::find(b0.begin(), b0.end(), a0.at(0));
			int idx = p - b0.begin();
			std::copy(b0.begin(), p, back_inserter(b1));
			std::copy(a0.begin() + 1, a0.begin() + idx + 1, back_inserter(a1));
			if (idx + 1 < b0.size())
			{
				std::copy(p + 1, b0.end(), back_inserter(b2));
				std::copy(a0.begin() + idx + 1, a0.end(), back_inserter(a2));
			}

			Node* cur = q.front();
			q.pop();

			if (b1.size())
			{
				ql.push(a1);
				ql.push(b1);
				ql.push(a2);
				ql.push(b2);
				Node* t = new Node(a1.at(0));
				q.push(t);
				cur->lchild = t;
				if (b2.size())
				{
					t = new Node(a2.at(0));
					q.push(t);
					cur->rchild = t;
				}
			}
		}
		return BinaryTree<A>(first, pre_o.size());
	}

	template<class A>
	BinaryTree<A> build_tree_from_pre_post(vector<A> pre_o, vector<A> post_o)
	{
		using Node = BinaryTree<A>::Node;

		auto find_common = [](vector<A> pre_o, vector<A> post_o)
		{
			if (pre_o.size() == 1)
				return 0;
			set<A> s1, s2;
			int i = 0;
			do
			{
				s1.insert(pre_o.at(1 + i));
				s2.insert(post_o.at(i++));
			} while (s1 != s2);
			return i;
		};

		Queue<Node*> q;
		Queue<vector<A>> ql;
		Node* first = new Node(pre_o.at(0));
		ql.push(pre_o);
		ql.push(post_o);
		q.push(first);

		while (!ql.empty())
		{
			vector<A> a1, b1, a2, b2, a0, b0;
			a0 = ql.front();
			ql.pop();
			b0 = ql.front();
			ql.pop();
			if (!b0.size())
			{
				continue;
			}
			int idx = find_common(a0, b0);
			std::copy(b0.begin(), b0.begin() + idx, std::back_inserter(b1));
			std::copy(a0.begin() + 1, a0.begin() + idx + 1, std::back_inserter(a1));
			if (idx + 1 < b0.size())
			{
				std::copy(b0.begin() + idx, b0.end() - 1, std::back_inserter(b2));
				std::copy(a0.begin() + idx + 1, a0.end(), std::back_inserter(a2));
			}

			Node* cur = q.front();
			q.pop();

			if (b1.size())
			{
				ql.push(a1);
				ql.push(b1);
				ql.push(a2);
				ql.push(b2);
				Node* t = new Node(a1.at(0));
				q.push(t);
				cur->lchild = t;
				if (b2.size())
				{
					t = new Node(a2.at(0));
					q.push(t);
					cur->rchild = t;
				}
			}
		}
		return BinaryTree<A>(first, pre_o.size());;
	}

	template<class A>
	BinaryTree<A> build_tree_from_in_post(vector<A> in_o, vector<A> post_o)
	{
		using Node = BinaryTree<A>::Node;

		Queue<Node*> q;
		Queue<vector<A>> ql;
		Node* first = new Node(post_o.at(post_o.size() - 1));
		ql.push(post_o);
		ql.push(in_o);
		q.push(first);

		while (!ql.empty())
		{
			vector<A> a1, b1, a2, b2, a0, b0;
			a0 = ql.front();
			ql.pop();
			b0 = ql.front();
			ql.pop();
			if (!b0.size())
			{
				continue;
			}
			vector<A>::iterator p = find(b0.begin(), b0.end(), a0.at(a0.size() - 1));
			int idx = p - b0.begin();
			std::copy(b0.begin(), p, std::back_inserter(b1));
			std::copy(a0.begin(), a0.begin() + idx, std::back_inserter(a1));
			if (idx + 1 < b0.size())
			{
				std::copy(p + 1, b0.end(), std::back_inserter(b2));
				std::copy(a0.begin() + idx, a0.end() - 1, std::back_inserter(a2));
			};

			Node* cur = q.front();
			q.pop();

			if (b1.size())
			{
				ql.push(a1);
				ql.push(b1);
				ql.push(a2);
				ql.push(b2);
				Node* t = new Node(a1.at(a1.size() - 1));
				q.push(t);
				cur->lchild = t;
				if (b2.size())
				{
					t = new Node(a2.at(a2.size() - 1));
					q.push(t);
					cur->rchild = t;
				}
			}
		}
		return BinaryTree<A>(first, in_o.size());
	}
}