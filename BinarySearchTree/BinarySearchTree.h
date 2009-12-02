/********************************************************************
*	BinarySearchTree.h - a generic binary search tree               *
*																	*
*	Lindsey Bieda													*
********************************************************************/

#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include <iostream>

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	
	void add(T);					// adds an item to the tree
	bool remove(T);					// removes the item from the tree
	void clear();					// removes all items from the tree
	void display();					// prints out all of the members
	bool inTree(T);					// tells if the value is in the tree or not

private:

	struct node
	{
		T data;
		struct node *LChild;
		struct node *RChild;
	};

	node *root;

	void print(node*);				// helper print function
	void killkillkill(node*);		// helper delete function
	void removeNode(node**, node*);	// helper single node delete function
};

template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = NULL;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	clear();
}

template<class T>
void BinarySearchTree<T>::add(T value)
{
	node* newNode = new node;
	
	newNode->data = value;
	newNode->LChild = NULL;
	newNode->RChild = NULL;

	if(root == NULL)
	{
		// empty tree - new node is the root
		root = newNode;
		return;
	}
	
	node* parent;
	node* cur;

	cur = root;

	// find parent node
	while(cur)
	{
		parent = cur;
		
		if(newNode->data > cur->data)
		{
			cur = cur->RChild;
		}
		else
		{
			cur = cur->LChild;
		}
	}

	// add the node as the parent's child
	if(newNode->data > parent->data)
	{
		parent->RChild = newNode;
	}
	else
	{
		parent->LChild = newNode;
	}
}

template<class T>
bool BinarySearchTree<T>::remove(T value)
{	
	node* cur = root;
	node** parent = NULL;

	while(cur != NULL)
	{
		if(cur->data == value)
		{
			break;
		}

		if(cur->data < value)
		{
			parent = &cur->RChild;
			cur = cur->RChild;
		}
		else
		{
			parent = &cur->LChild;
			cur = cur->LChild;
		}
	}

	if(cur == NULL)
	{
		return false;
	}

	removeNode(parent, cur);
	return true;
}


template<class T>
bool BinarySearchTree<T>::inTree(T value)
{
	node* cur = root;

	while(cur)
	{
		if(cur->data == value)
		{
			return true;
		}
		else if(cur->data < value)
		{
			cur = cur->RChild;
		}
		else
		{
			cur = cur->LChild;
		}
	}

	return false;
}

template<class T>
void BinarySearchTree<T>::removeNode(node** parent, node* cur)
{
	// case 1 and 2: nodes with one or no children
	if(cur->LChild == NULL)
	{
		*parent = cur->RChild;

		delete[] cur;
	}
	else if(cur->RChild == NULL)
	{
		*parent = cur->LChild;

		delete[] cur;
	}
	else
	{
		// case 3: node with two children (the worst)
		node *temp = cur->LChild;
		node ** parent_temp = &cur->LChild;

		while(temp->RChild != NULL)
		{
			parent_temp = &temp->RChild;
			temp = temp->RChild;
		}

		*parent_temp = NULL;
		cur->data = temp->data;

		delete[] temp;
	}
	
}


template<class T>
void BinarySearchTree<T>::display()
{
	if(root == NULL)
	{
		std::cout << "Error: Empty tree\n";
		return;
	}
	
	print(root);
	std::cout << "\n";
}

template<class T>
void BinarySearchTree<T>::print(node* cur)
{
	if(cur != NULL)
	{
		std::cout << cur->data << " ";
		print(cur->LChild);				// go print left branch
		print(cur->RChild);				// go print right branch
	}
		
	return;
}
template<class T>
void BinarySearchTree<T>::clear()
{
	if(root == NULL)	// nothing to remove
		return;

	killkillkill(root);
	root = NULL;
}

template<class T>
void BinarySearchTree<T>::killkillkill(node* cur)
{ 
	if(cur == NULL)
		return;

	killkillkill(cur->LChild);		// kill the left  branch
	killkillkill(cur->RChild);		// kill the right branch

	delete[] cur;
}


#endif