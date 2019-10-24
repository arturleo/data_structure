#pragma once
#include"../LinkedList/DoublyLinkedList.h"
#include"../LinkedList/Queue.h"
#include"../LinkedList/Stack.h"
#include"../Heap/Heap.h"
#include"BinaryTree.h"
#include"BinarySearchTree.h"

namespace ds
{
	template <class T>
	class HuffmanTree :public BinaryTree<T>
	{
	public:
		class WeightNode :public Node
		{
		public:
			T weight;
			WeightNode* lchild, * rchild, * parent;
			//copy constructor
			WeightNode(const Node& n) :Node(n)
			{
				weight = T();
				parent = lchild = rchild = NULL;

				//recursive
				if (n.lchild)
				{
					lchild = new WeightNode(n.lchild);
					lchild->parent = this;
				}
				if (n.rchild)
				{
					rchild = new WeightNode(n.rchild);
					rchild->parent = this;
				}

				if (WeightNode* wn = dynamic_cast<WeightNode*>(&n))
				{
					weight = T(wn->data);
				}
			};
			// convert
			explicit WeightNode(const Node* const n) :Node(n)
			{
				weight = T();
				parent = lchild = rchild = NULL;

				//recursive
				if (n->lchild)
				{
					lchild = new WeightNode(n->lchild);
					lchild->parent = this;
				}
				if (n->rchild)
				{
					rchild = new WeightNode(n->rchild);
					rchild->parent = this;
				}
				if (WeightNode* wn = dynamic_cast<WeightNode*>(const_cast<Node*>(n)))
				{
					weight = T(wn->data);
				}
			};
			explicit WeightNode(T data = T()) :Node(data), weight(T(data))
			{
				// since redefined, these should be initialized outside base class
				parent = lchild = rchild = NULL;
			};
			virtual ~WeightNode() {};
		};

		HuffmanTree() :BinaryTree() { root = NULL; };
		explicit HuffmanTree(BinaryTree<T> bt);
		explicit HuffmanTree(const DoublyLinkedList<T>& dll);
		~HuffmanTree() {};

		class WeightNodeCompare
		{
		public:
			bool operator()(WeightNode* a, WeightNode* b)
			{
				return a->weight > b->weight;
			}
		};
	protected:
		WeightNode* root;
		void intialize(const DoublyLinkedList<T>& dll);
		//inherited:
			//public:
				//	Node;
				//  Queue<T> in_order() const;
				//  Queue<T> pre_order() const;
				//  Queue<T> post_order() const;
				//  void clear();
			//protected:
				//	size_t pSize;
				//  void rotate_right(Node* x);
				//  void rotate_left(Node* x);
	private:
		//delete
		using BinaryTree::delete_node;
	};

	template <class T>
	void HuffmanTree<T>::intialize(const DoublyLinkedList<T>& dll)
	{
		pSize = dll.size();
		root = nullptr;

		Heap<WeightNode*, WeightNodeCompare> heap;
		for (DoublyLinkedList<T>::Iterator<> i = dll.begin(); i != dll.end(); ++i)
		{
			WeightNode* wn = new WeightNode(i->data);
			heap.push(wn);
		}
		
		while (!heap.empty())
		{
			WeightNode* a = heap.front();
			heap.pop();
			if (!heap.empty())
			{
				WeightNode* b = heap.front();
				heap.pop();
				WeightNode* c = new WeightNode(a->weight + b->weight);
				c->lchild = a;
				c->rchild = b;
				heap.push(c);
			}
			else root = a;
		}
	}

	template <class T>
	HuffmanTree<T>::HuffmanTree(BinaryTree<T> bt)
	{
		if (typeid(BinarySearchTree<T>) == typeid(bt))
		{
			root = new WeightNode(bt.root);
			pSize = bt.size();
		}
		else
		{
			intialize(bt.in_order());
		}		
	};

	template <class T>
	HuffmanTree<T>::HuffmanTree(const DoublyLinkedList<T>& d)
	{
		intialize(d);
	}

}