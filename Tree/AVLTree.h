#pragma once
#include "BinarySearchTree.h"
#include <exception>
#include <cmath>
#include<algorithm>

namespace ds
{
	template <class T>
	class AVLTree : public BinarySearchTree<T>
	{
	public:
		struct HeightNode :InthreadNode
		{
		public:
			size_t h;
			HeightNode(const Node& n) :InthreadNode(T(n.data))
			{
				parent = lchild = rchild = NULL;
				// recount needed;
				h = 0;
				//recursive
				if (n.lchild)
				{
					lchild = new HeightNode(n.lchild);
					lchild->parent = this;
				}
				if (n.rchild)
				{
					rchild = new HeightNode(n.rchild);
					rchild->parent = this;
				}

				if (HeightNode* itn = dynamic_cast<HeightNode*>(&n))
				{
					h = itn->h;
				}
			};
			explicit HeightNode(const Node* const n) :InthreadNode(T(n->data))
			{
				parent = lchild = rchild = NULL;
				// recount needed;
				h = 0;

				//recursive
				if (n->lchild)
				{
					lchild = new HeightNode(n->lchild);
					lchild->parent = this;
				}
				if (n->rchild)
				{
					rchild = new HeightNode(n->rchild);
					rchild->parent = this;
				}

				if (HeightNode* itn = 
					dynamic_cast<HeightNode*>(const_cast<Node*>(n)))
				{
					h = itn->h;
				}
			};
			HeightNode(T d = T()) :InthreadNode(d)
			{
				h = 1;
				// since redefined, these should be initialized outside base class
				parent = lchild = rchild = NULL;
			};
		};
		AVLTree() :BinarySearchTree() { root = pHead = pTail = NULL; };
		explicit AVLTree(const BinaryTree<T>& bt);
		explicit AVLTree(const DoublyLinkedList<T>& dll);
		~AVLTree() override {};
		virtual void insert(T d) override;
		virtual void delete_node(Node* x) override;
	protected:
		void rotate_right(Node* x) override;
		void rotate_left(Node* x) override;
		void addHeight(HeightNode* x);
		void removeHeight(HeightNode* x);
		//inherited:
			//public:
				//	Node;
				//  Queue<T> in_order() const;
				//  Queue<T> pre_order() const;
				//  Queue<T> post_order() const;
				//  void clear();
				//  virtual Node* find(T d) const;
				//  void inthreadify();
				//
				//  template<typename U>
				//  friend std::ostream& operator<< (std::ostream& os, const BinarySearchTree<U>& bt);
			//protected:
				//	size_t pSize;
	};

	template<class T>
	AVLTree<T>::AVLTree(const BinaryTree<T>& bt)
	{
		pSize = 0;
		thread = 0;
		root = pHead = pTail = NULL;

		//dynamic_cast requires no template
		if (typeid(AVLTree<T>) == typeid(bt))
		{
			root = new HeightNode(bt.root);
			pSize = bt.size();
		}
		else
		{
			BinarySearchTree<T>* tmp = new BinarySearchTree<T>();
			tmp->root = new InthreadNode(bt.root);
			tmp->pSize = bt.size();
			tmp->inthreadify();

			InthreadNode* p = tmp->pHead;
			while (p)
			{
				insert(p->data);
				InthreadNode* nx = dynamic_cast<InthreadNode*>(p->rchild);
				if (!p->next)
					while (nx && !nx->last)
						nx = dynamic_cast<InthreadNode*>(nx->lchild);
				p = nx;
			}
			delete tmp;
		}
	}
	template<class T>
	AVLTree<T>::AVLTree(const DoublyLinkedList<T>& dll) :BinarySearchTree(dll)
	{
		root = pHead = pTail = NULL;
		for (DoublyLinkedList<T>::Iterator itr = dll.cbegin();
			itr != dll.cend(); ++itr)
		{
			insert(itr->data);
		}
	}

	template<class T>
	void AVLTree<T>::addHeight(HeightNode* x)
	{
		HeightNode* p = dynamic_cast<HeightNode*>(x->parent), * cur = x;
		while (p)
		{
			if (p->h < cur->h + 1)
			{
				p->h = cur->h + 1;
				cur = p;
			}
			else
				break;

			p = dynamic_cast<HeightNode*>(cur->parent);
		}
	}

	template<class T>
	void AVLTree<T>::removeHeight(HeightNode* x)
	{
		HeightNode* p = dynamic_cast<HeightNode*>(x->parent), * cur = x;
		while (p)
		{
			if ((!p->rchild && p->h == 2 || p->h > 
				dynamic_cast<HeightNode*>(p->rchild)->h + 1)
				&& (!p->lchild && p->h == 2 || p->h > 
					dynamic_cast<HeightNode*>(p->lchild)->h + 1))
			{
				p->h = cur->h + 1;
				cur = p;
			}
			else
				break;

			p = dynamic_cast<HeightNode*>(cur->parent);
		}
	}

	template<class T>
	void AVLTree<T>::insert(T d)
	{
		deinthreadify();
		Node* s = root, * cur = new HeightNode(d);
		while (1)
		{
			if (!s)
			{
				s = cur;
				pSize++;
				root = s;
				return;
			}
			//left
			else if (s->data > d)
			{
				if (s->lchild && (!s->rchild || dynamic_cast<HeightNode*>(s->lchild)->h - dynamic_cast<HeightNode*>(s->rchild)->h == 1))
				{
					rotate_right(s);
					s = s->parent;
				}
				else if (!s->lchild)
				{
					s->lchild = cur;
					cur->parent = s;
					pSize++;
					addHeight(dynamic_cast<HeightNode*>(cur));
					return;
				}
				else
				{
					s = s->lchild;
				}
			}
			//right
			else if (s->data < d)
			{
				if (s->rchild && (!s->lchild || dynamic_cast<HeightNode*>(s->rchild)->h - dynamic_cast<HeightNode*>(s->lchild)->h == 1))
				{
					rotate_left(s);
					s = s->parent;
				}
				else if (!s->rchild)
				{
					s->rchild = cur;
					cur->parent = s;
					pSize++;
					addHeight(dynamic_cast<HeightNode*>(cur));
					return;
				}
				else
				{
					s = s->rchild;
				}
			}
			else return;//already exist
		}
	}

	template<class T>
	void AVLTree<T>::delete_node(Node* x)
	{
		deinthreadify();
		Node* p = x->parent, * cur = x;
		pSize--;

		while (p)
		{
			if (cur == p->lchild)
			{
				if (p->rchild && dynamic_cast<HeightNode*>(p->rchild)->h - dynamic_cast<HeightNode*>(p->lchild)->h == 1)
				{
					cur = p->rchild;
					rotate_left(p);
				}
				else
					cur = p;
			}
			else if (cur == p->rchild)
			{
				if (p->lchild && dynamic_cast<HeightNode*>(p->lchild)->h - dynamic_cast<HeightNode*>(p->rchild)->h == 1)
				{
					cur = p->lchild;
					rotate_right(p);
				}
				else
					cur = p;
			}

			p = dynamic_cast<HeightNode*>(cur->parent);
		}

		while (x)
		{
			if (x->lchild &&
				(!x->rchild || (dynamic_cast<HeightNode*>(p->lchild)->h 
					- dynamic_cast<HeightNode*>(p->rchild)->h == 1)))
				rotate_right(x);
			else if (x->rchild)
				rotate_left(x);
			else
			{
				dynamic_cast<HeightNode*>(x)->h = 0;
				removeHeight(dynamic_cast<HeightNode*>(x));
				rotate_left(x);
				delete x;
				x = NULL;
				break;
			}
		}
	}

	template<class T>
	void AVLTree<T>::rotate_right(Node* x)
	{
		//allow x->lchild to be NULL
		Node* y = x->lchild;
		//parent link
		if (!x->parent)
			root = y;
		else if (x->parent->lchild == x)
			x->parent->lchild = y;
		else if (x->parent->rchild == x)
			x->parent->rchild = y;
		dynamic_cast<HeightNode*>(x)->h = x->rchild ? 
			dynamic_cast<HeightNode*>(x->rchild)->h + 1 : 1;
		if (y) {
			y->parent = x->parent;

			x->lchild = y->rchild;
			if (y->rchild)
				y->rchild->parent = x;

			y->rchild = x;

			dynamic_cast<HeightNode*>(y)->h = 
				dynamic_cast<HeightNode*>(x)->h + 1;
		}
		x->parent = y;
	}

	template<class T>
	void AVLTree<T>::rotate_left(Node* x)
	{
		Node* y = x->rchild;
		//parent link
		if (!x->parent)
			root = y;
		else if (x->parent->lchild == x)
			x->parent->lchild = y;
		else if (x->parent->rchild == x)
			x->parent->rchild = y;
		dynamic_cast<HeightNode*>(x)->h = x->lchild ?
			dynamic_cast<HeightNode*>(x->lchild)->h + 1 : 1;
		if (y)
		{
			y->parent = x->parent;

			x->rchild = y->lchild;
			if (y->lchild)
				y->lchild->parent = x;

			y->lchild = x;

			dynamic_cast<HeightNode*>(y)->h =
				dynamic_cast<HeightNode*>(x)->h + 1;
		}
		x->parent = y;

	}
}