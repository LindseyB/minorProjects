/**********************************************
* linkedlist.c - a linked list
*
* Lindsey Bieda
***********************************************/


#include <stdio.h>
#include <malloc.h>

//linked list struct
struct linked_list
{
	struct node *head;
	int count;
};

//node struct
struct node
{
	int data;
	struct node *next;
};



// allocates a new list, inits object
struct linked_list* linked_list_new()
{
	struct linked_list* newList;
	newList = malloc(sizeof(struct linked_list));

	newList->count = 0;
	newList->head = NULL;

	return newList;
}

// adds in FIFO fashion
void linked_list_add( struct linked_list* list, int data)
{
	struct node* cur = list->head;

	if (cur == NULL)
	{
		cur = malloc(sizeof(struct node));
		cur->data = data;
		cur->next = NULL;
		
		list->head = cur;

		return;
	}

	while(cur)
	{
		if(cur->next == NULL)
		{
			struct node* newNode;
			newNode = malloc(sizeof(struct node));
			newNode->data = data;
			newNode->next = NULL;

			cur->next = newNode;
			list->count ++;
		}
		else
		{
			cur = cur->next;
		}
	}

}

// adds entry after entry at index, or adds at end on invalid index 
//(see 'get' function for indexing rules)
void linked_list_add_after( struct linked_list* list, int data, int index)
{
	struct node* cur = list->head;
	struct node* newNode;
	int i = 0;

	if (cur == NULL)
	{
		newNode = malloc(sizeof(struct node));
		newNode->data = data;
		newNode->next = NULL;
		
		list->head = newNode;

		return;
	}

	while(cur)
	{
		if(i == index || cur->next == NULL)
		{
			newNode = malloc(sizeof(struct node));
			newNode->data = data;
			newNode->next = cur->next;
			cur->next = newNode;
			
			list->count ++;

			return;
		}

		i++;
		cur = cur->next;
	}


}

// removes in FIFO fashion
int linked_list_remove( struct linked_list* list )
{
	int temp = -1;
	struct node* tempptr = list->head;

	if(list->head == NULL)
	{
		return temp;
	}

	list->head = tempptr->next;
	temp = tempptr->data;

	list->count -= 1;
	free(tempptr);

	return temp;
}

//  clears, and deallocates list
void linked_list_clear(struct linked_list* list)
{
	struct node* temp;
	struct node* cur = list->head;

	while(cur)
	{	
		temp = cur;
		cur = cur->next;
		free(temp);
	}

	list->count = 0;
	list->head = NULL;

}

// deallocates list nodes
void linked_list_free(struct linked_list* list)
{
	linked_list_clear(list);

	free(list);
}

// returns number of nodes
int linked_list_count(struct linked_list* list)
{
	return list->count;
}

// returns node data at index (0 == first node created, etc) or node data of 
// last entry on invalid entry
int linked_list_get(struct linked_list* list, int index)
{
	int i=0;

	struct node* cur = list->head;

	while(cur)
	{
		if(i == index)
			return cur->data;

		i++;
		cur = cur->next;
	}

	return i;
}

int main()
{
	return 0;
}

