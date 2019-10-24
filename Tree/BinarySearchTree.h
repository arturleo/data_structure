#pragma once
#include <typeinfo>    // for 'typeid'
#include"BinaryTree.h"
#include"../LinkedList/Stack.h"

namespace ds
{
	template<class T>
	class AVLTree;

	template <class T>
	class BinarySearchTree : public BinaryTree<T>
	{
		friend class AVLTree<T>;
	public:
		struct InthreadNode :Node
		{
			short last, next;
			//copy constructor
			InthreadNode(const Node& n) :Node(T(n.data))
			{
				parent = lchild = rchild = NULL;
				last = next = 0;
				//recursive
				if (n.lchild)
				{
					lchild = new InthreadNode(n.lchild);
					lchild->parent = this;
				}
				if (n.rchild)
				{
					rchild = new InthreadNode(n.rchild);
					rchild->parent = this;
				}

				if (InthreadNode* itn = dynamic_cast<InthreadNode*>(&n))
				{
					last = itn->last;
					next = itn->next;
				}
			};
			explicit InthreadNode(const Node* const n) :Node(T(n->data))
			{
				parent = lchild = rchild = NULL;
				last = next = 0;
				//recursive
				if (n->lchild)
				{
					lchild = new InthreadNode(n->lchild);
					lchild->parent = this;
				}
				if (n->rchild)
				{
					rchild = new InthreadNode(n->rchild);
					rchild->parent = this;
				}

				if (InthreadNode* itn = dynamic_cast<InthreadNode*>(const_cast<Node*>(n)))
				{
					last = itn->last;
					next = itn->next;
				}
			};
			explicit InthreadNode(T d = T()) :Node(d) {
				last = next = 0;
				// since redefined, these should be initialized outside base class
				parent = lchild = rchild = NULL;
			};
			virtual ~InthreadNode() {};
		};
		BinarySearchTree() :BinaryTree() { thread = 0; root = pHead = pTail = NULL; };
		explicit BinarySearchTree(const BinaryTree<T>& bt);
		explicit BinarySearchTree(const DoublyLinkedList<T>& dll);
		virtual ~BinarySearchTree() { deinthreadify(); };
		virtual void insert(T d);
		virtual Node* find(T d) const;
		void inthreadify();
		// for consisitency between BinaryTree, inthreadify should be cleared
		// immediately after inthreadify
		void deinthreadify();

		template<typename U>
		friend std::ostream& operator<< (std::ostream& os, const BinarySearchTree<U>& bt);
	protected:
		int thread;
		InthreadNode* pHead, * pTail;
		//inherited:
			//public:
				//	Node;
				//  Queue<T> in_order() const;
				//  Queue<T> pre_order() const;
				//  Queue<T> post_order() const;
				//  virtual void delete_node(Node* x);
				//  void clear();
			//protected:
				//	size_t pSize;
				//  void rotate_right(Node* x);
				//  void rotate_left(Node* x);
	};

	template<class T>
	BinarySearchTree<T>::BinarySearchTree(const BinaryTree<T>& bt)
	{
		pSize = 0;
		thread = 0;
		root = pHead = pTail = NULL;

		//dynamic_cast requires no template
		if (typeid(BinarySearchTree<T>) == typeid(bt))
		{
			root = new InthreadNode(bt.root);
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
	BinarySearchTree<T>::BinarySearchTree(const DoublyLinkedList<T>& dll)
	{
		pSize = thread = 0;
		root = pHead = pTail = NULL;
		for (DoublyLinkedList<T>::Iterator itr = dll.cbegin(); itr != dll.cend(); ++itr)
		{
			insert(itr->data);
		}
	}

	template<class T>
	void BinarySearchTree<T>::inthreadify()
	{
		if (!thread)
		{
			if (!root)
			{
				pHead = pTail = NULL;
				thread = 1;
			}
			InthreadNode* p = dynamic_cast<InthreadNode*>(root), * last = NULL;
			Stack<InthreadNode*> s;
			s.push(p);

			do {
				//left 
				while (p->lchild)
				{
					p = dynamic_cast<InthreadNode*>(p->lchild);
					s.push(p);
				}
				p->last = 1;
				if (!last)
					pHead = p;
				p->lchild = last;

				//find right
				while (!s.empty())
				{
					last = p = s.top();
					s.pop();
					if (p->rchild)
					{
						p = dynamic_cast<InthreadNode*>(p->rchild);
						s.push(p);
						break;
					}
					else if (s.empty())
						pTail = p;
					else {
						p->next = 1;
						p->rchild = s.top();
					}
				}
			} while (!s.empty());
			thread = 1;
		}
		else
		{
			return;
		}
	}

	template<class T>
	void BinarySearchTree<T>::deinthreadify()
	{
		if (thread)
		{
			InthreadNode* p = pHead;
			while (p)
			{
				InthreadNode* nx = dynamic_cast<InthreadNode*>(p->rchild);
				if (p->last)
					p->lchild = NULL;
				if (p->next)
					p->rchild = NULL;
				if (!p->next)
					while (nx && !nx->last)
						nx = dynamic_cast<BinarySearchTree<T>::InthreadNode*>(nx->lchild);
				p = nx;
			}
			thread = 0;
		}
		else
			return;
	};

	template<class T>
	void BinarySearchTree<T>::insert(T d)
	{
		deinthreadify();
		Node* nd = new InthreadNode(d);
		Node* cur = root;

		while (1)
		{
			if (!cur)
			{
				cur = nd;
				pSize++;
				root = cur;
				return;
			}
			else if (cur->data < d)
			{
				if (cur->rchild)
				{
					cur = cur->rchild;
					continue;
				}
				else
				{
					cur->rchild = nd;
					nd->parent = cur;
					pSize++;
					break;
				}
			}
			else if (cur->data > d)
			{
				if (cur->lchild)
				{
					cur = cur->lchild;
					continue;
				}
				else
				{
					cur->lchild = nd;
					nd->parent = cur;
					pSize++;
					break;
				}
			}
			else return;//already exist
		}
	}

	template <class T>
	typename BinarySearchTree<T>::Node* BinarySearchTree<T>::find(T d) const
	{
		Node* s = root;
		while (s && s->data != d)
		{
			if (s->data > d)
				s = s->lchild;
			else if (s->data < d)
				s = s->rchild;
		}
		return s;//nullptr or node*
	}

	template<typename T>
	std::ostream& operator<< (std::ostream& os, const BinarySearchTree<T>& bt)
	{
		if (!bt.thread)
		{
			os << bt.in_order();
		}
		else
		{
			BinarySearchTree<T>::InthreadNode* p = bt.pHead;
			while (p)
			{
				os << p->data << " ";
				BinarySearchTree<T>::InthreadNode* nx = dynamic_cast<BinarySearchTree<T>::InthreadNode*>(p->rchild);
				if (!p->next)
					while (nx && !nx->last)
						nx = dynamic_cast<BinarySearchTree<T>::InthreadNode*>(nx->lchild);
				p = nx;
			}
			os << std::endl;
		}
		return os;
	}
}