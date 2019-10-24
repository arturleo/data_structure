#include<iostream>
#include"../Tree/BinaryTree.h"
#include"../Tree/BinarySearchTree.h"
#include"../Tree/HuffmanTree.h"
#include"../Tree/AVLTree.h"
using namespace ds;

int main()
{
	/*
			1a
		 /     \
		47b     4c
	   /  \     /
	 234d 12e  35h
	  /
	 9f
	 /
	 25g

	*/
#define Node BinaryTree<int>::Node
	Node* a = new Node(1),
		* b = new Node(47),
		* c = new Node(4),
		* d = new Node(234),
		* e = new Node(12),
		* f = new Node(9),
		* g = new Node(25),
		* h = new Node(35);
	g->parent = f;
	f->lchild = g;
	f->parent = d;
	d->lchild = f;
	d->parent = b;
	b->lchild = d;
	b->rchild = e;
	e->parent = b;
	c->lchild = h;
	h->parent = c;
	a->rchild = c;
	c->parent = a;
	a->lchild = b;
	b->parent = a;
	BinaryTree<int> bt = BinaryTree<int>(a, 8);
	std::cout << bt;
	std::cout << bt.pre_order();
	std::cout << bt.post_order();

	Queue<int> q1 = bt.pre_order(),
		q2 = bt.in_order(),
		q3 = bt.post_order();

	vector<int> preo, ino, psto;
	while (!q1.empty())
	{
		preo.push_back(q1.front());
		q1.pop();
	};

	while (!q2.empty())
	{
		ino.push_back(q2.front());
		q2.pop();
	};

	while (!q3.empty())
	{
		psto.push_back(q3.front());
		q3.pop();
	};

	BinaryTree<int> t2 = build_tree_from_pre_post(preo, psto);
	BinaryTree<int> t1 = build_tree_from_in_post(ino, psto);
	
	BinaryTree<int> t3 = build_tree_from_pre_in(preo, ino);
	std::cout << t1 << t1 << t3;
	// deep copy
	BinaryTree<int>bt2 = BinaryTree<int>(bt);

	bt.delete_node(a);




	/*
			47b
		   /  \
		 234d 12e
		  /     \
		 9f     4c
		 /     /
		 25g 35h
*/
	BinarySearchTree<int>bst = BinarySearchTree<int>(bt);
	bst.insert(30);
	bst.inthreadify();
	std::cout << bst;

	Node* z = bst.find(30);
	z = bst.find(0);

	HuffmanTree<int> hfmt = HuffmanTree<int>(bt);

	AVLTree<int> avlt = AVLTree<int>(bt);
	avlt.insert(333);
	avlt.inthreadify();
	std::cout << avlt;
	AVLTree<int>::HeightNode* hn = dynamic_cast<AVLTree<int>::HeightNode*>(avlt.find(333));
	avlt.delete_node(hn);
	return 0;
}