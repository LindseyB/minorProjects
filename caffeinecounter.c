/**************************************************************
 *  caffeinecounter.c - calculates amount of caffeine consumed       
 *                                                  
 *  Asks the user for four commonly cosumed caffeinated drinks 
 *  and displays the total caffeine consumed in mg                                  
 *                                                  
 *  Lindsey Bieda
 *************************************************************/

#include <stdio.h>

int main()
{
	//initalize all the counts to zero
	int tea = 0, coffee = 0, drpepper = 0, mtdew = 0, tot;

	//collect the user data
	printf("Please enter the number of each consumed:\n");

	printf("\t%-20s: ", "Tea (8oz)");
	scanf_s("%d", &tea);

	printf("\t%-20s: ", "Coffee (8oz)");
	scanf_s("%d", &coffee);

	printf("\t%-20s: ", "Dr. Pepper (12oz)");
	scanf_s("%d", &drpepper);

	printf("\t%-20s: ", "Mountain Dew (12oz)");
	scanf_s("%d", &mtdew);

	//calculuate the total
	tot = (tea*47) + (coffee*95) + (drpepper*41) + (mtdew*54);

	printf("\nApprox Caffeine Consumption: %dmg\n", tot);

	return 0;
}