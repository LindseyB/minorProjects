/**************************************************************
 *  Example of generic linked list
 *                                                                  
 *                                                  
 *  Lindsey Bieda
 *************************************************************/

#include "LinkedList.h"
#include <stdio.h>

void main()
{
	LinkedList<int> list;

	list.add(1);
	list.add(2);
	list.add(3);

	printf("%d\n", list.removeIndex(0));
	printf("%d\n", list.removeIndex(1));
	printf("%d\n", list.removeIndex(0));

	list.clear();


}