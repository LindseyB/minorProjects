/**************************************************************
 *  Example.cpp - demonstrates the generic stack      
 *                                                  
 *  Puts the numbers 1-11 on the stack and then pops 3 numbers
 *  from the top of the stack                      
 *                                                  
 *  Lindsey Bieda
 *************************************************************/

#include <stdio.h>
#include <stdio.h>
#include "Stack.h"

void main()
{
	Stack<int> testStack;

	testStack.push(1);
	testStack.push(2);
	testStack.push(3);
	testStack.push(4);
	testStack.push(5);
	testStack.push(6);
	testStack.push(7);
	testStack.push(8);
	testStack.push(9);
	testStack.push(10);
	testStack.push(11);

	printf("%d\n", testStack.pop());     // prints: 11
	printf("%d\n", testStack.pop());     // prints: 10
	printf("%d\n", testStack.pop());     // prints: 9
}