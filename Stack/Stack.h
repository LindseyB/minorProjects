/**************************************************************
 *  Stack.h - a generic Stack
 *                                                                  
 *                                                  
 *  Lindsey Bieda
 *************************************************************/

#ifndef _STACK_H
#define _STACK_H

#include <string.h>

template <class T>
class Stack
{
public:
	Stack()
	{
		size = 10;
		count = 0;
		stack = new T[size];
	}

	virtual ~Stack()
	{
		delete[] stack; 
	}

	void push(T);  // push a new item on top of the stack
	T pop();       // pops an item off the top of the stack
	T peek();      // returns the item currently at the top of the stack

private:
	int size;      // number of items the stack can currently hold
	int count;     // number of items currently in the stack
	T *stack;
};

template <class T>
void Stack<T>::push(T value)
{
	if(size==count)
	{
		//resize the stack
		T *newStack = new T[size*2];

		memcpy(newStack, stack, sizeof(T)*size);

		delete[] stack;
		stack = newStack;
		size *= 2;

	}

	stack[count] = value;
	count++;
}

template <class T>
T Stack<T>::pop()
{
	T temp;
	
	count--;
	temp = stack[count];

	return temp;
}

template <class T>
T Stack<T>::peek()
{
	return stack[count-1]; 
}

#endif