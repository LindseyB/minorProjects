/**************************************************************
 *  LinkedList.h - a generic linked list
 *                                                                  
 *                                                  
 *  Lindsey Bieda
 *************************************************************/

#ifndef	_LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdlib.h>

template <class T>
class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	void add(T);	      // add an item to the end of the list	
	T remove(T);          // remove a specified item
	T removeIndex(int);   // remove the node at given index
	T remove();	          // remove the node in a FIFO manner 
	void clear();         // clear the list

private:

	int count;

	struct node
	{
		T data;
		struct node *next;
	};

	node *head;
};

template<class T> 
LinkedList<T>::LinkedList()
{
	head = NULL;
	count = 0;
}

template<class T> 
LinkedList<T>::~LinkedList()
{
	clear();
}

template<class T> 
void LinkedList<T>::add(T newData)
{
	node *cur = head;
	node *newNode;

	if(head == NULL)
	{
		//added node becomes head
		cur = new node;

		cur->data = newData;
		cur->next = NULL;

		head = cur;

		return;		
	}
	else
	{
		//loop to find end
		while(cur)
		{
			if(cur->next == NULL)
			{
				newNode = new node;

				newNode->data = newData;
				newNode->next = NULL;

				cur->next = newNode;

				count++;
				return;
			}
			else
			{
				cur = cur->next;
			}
		}
	}
}

template<class T> 
T LinkedList<T>::remove(T data)
{
	T ret = NULL;
	node* temp = head;
	node* prev = NULL;

	if(temp == NULL)
	{
		return ret;
	}
	else
	{
		while((temp) && (temp->data != data))
		{
			prev = temp;
			temp = temp->next;
		}
		
		if(temp)
		{
			if(prev == NULL)
			{
				//removing head
				head = temp->next;
			}
			else
			{
				prev->next = temp->next;
			}

			ret = temp->data;
			delete[] temp;

			count--;

			return ret;
		}
	}

	return ret;
}

template<class T>
T LinkedList<T>::removeIndex(int index)
{
	T ret = NULL;
	node* temp = head;
	node* prev = NULL;

	if(index > count || temp == NULL)
	{
		// index out of list or empty list
		return ret;	
	}
	
	// find the node to remove
	for(int i=0; i<index; i++)
	{
		prev = temp;
		temp = temp->next;
	}
	
	// remove it
	if(prev == NULL)
	{
		//removing head
		head = temp->next;
	}
	else
	{
		prev->next = temp->next;
	}

	ret = temp->data;
	delete[] temp;

	count--;

	return ret;

}

template<class T>
T LinkedList<T>::remove()
{
	// remove the head
	T ret = head->data;
	node* temp = head;
	head = head->next;
	delete[] temp;

	count--;
		
	return ret; 		
}

template<class T> 
void LinkedList<T>::clear()
{
	node *cur = head;
	node *temp;

	count = 0;

	while(cur)
	{
		temp = cur;
		cur = cur->next;
		delete[] temp;
	}

	head = NULL;
}


#endif