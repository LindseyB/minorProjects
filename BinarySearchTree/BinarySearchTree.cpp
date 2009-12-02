/********************************************************************
*	BinarySearchTree.cpp - a demo of generic binary search tree		*
*																	*
*	Lindsey Bieda													*
********************************************************************/

#include "BinarySearchTree.h"

void main()
{
	BinarySearchTree<int> tree;

	// build the tree
	tree.add(30);
	tree.add(10);
	tree.add(20);
	tree.add(50);
	tree.add(5);
	tree.add(1);
	tree.add(2);

	tree.display();		// outputs: 30 10 5 1 2 20 50

	tree.remove(2);

	tree.display();		// outputs: 30 10 5 1 20 50 

	tree.clear();

	tree.display();		// outputs: Error: Empty tree
}