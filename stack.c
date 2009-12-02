/**********************************************
* stack.c - a linked list based stack
*
* Lindsey Bieda
***********************************************/


#include <stdio.h>
#include <malloc.h>

//linked list struct
struct stack
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
struct stack* stack_new()
{
	struct stack* newStack;
	newStack = malloc(sizeof(struct stack));

	newStack->count = 0;
	newStack->head = NULL;

	return newStack;
}

// adds in a FILO fashion
void stack_push(struct stack* stacklist, int data)
{
	struct node* newNode = malloc(sizeof(struct node));
	
	newNode->data = data;
	newNode->next = stacklist->head;

	stacklist->head = newNode;
	stacklist->count++;
}

// removes in a FILO fashion
int stack_pop(struct stack* stacklist)
{
	int temp = -1;
	struct node* tempptr = stacklist->head;

	if(stacklist->head == NULL)
	{
		return temp;
	}

	stacklist->head = tempptr->next;
	temp = tempptr->data;

	stacklist->count -= 1;
	free(tempptr);

	return temp;
}


//  clears, and deallocates list
void stack_clear(struct stack* stacklist)
{
	struct node* temp;
	struct node* cur = stacklist->head;

	while(cur)
	{	
		temp = cur;
		cur = cur->next;
		free(temp);
	}

	stacklist->count = 0;
	stacklist->head = NULL;

}

// deallocates list nodes
void stack_free(struct stack* stacklist)
{
	stack_clear(stacklist);

	free(stacklist);
}

// returns number of nodes
int stack_count(struct stack* stacklist)
{
	return stacklist->count;
}

// prints all the nodes
void stack_print(struct stack* stacklist)
{
	struct node* cur = stacklist->head;

	if(cur == NULL)
	{
		printf("Err: Empty stack\n");
		return;
	}

	while(cur)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}

	printf("\n");
}

int main()
{
	struct stack* myStack = stack_new();

	stack_print(myStack);

	stack_push(myStack, 1);
	stack_push(myStack, 2);
	stack_push(myStack, 3);

	stack_print(myStack);

	stack_pop(myStack);

	stack_print(myStack);

	return 0;
}

