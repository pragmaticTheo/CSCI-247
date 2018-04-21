/*
	CSCI 247 - Spring 2018
	Filename: Lab2.c
	'itoa' Function and Demo by Brandon Chavez.
	Rated 'E' for "Even You"!
	
	This program is a demonstration of a method which returns a base 10 number of the user's choice
	as a string representation in a user specified base (e.g., giving the method the decimal number "10"
	will result in a string of characters reading "1010". Guaranteed to work for base 'x' such that 2<=x<=16,
	although it should theoretically work for any base 'x' such that 2<=x<=61. Mileage may vary.
*/

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

char* itoa(int num, char* str, int base);

// The main function itself is for purely demonstrative purposes. It allows you the liberty to 
// select your own desired base and base ten number to work with.
int main(int argc, char* argv[])
{
	int runFlag = 1;

	while(runFlag)
	{
		char str[MAX_LENGTH] = {0};

		printf("Welcome to a demonstration of my very basic base conversion function, \"itoa\".\n");
		printf("Please specify output base. Input is assumed to be in base 10.\n");
		int desiredBase = 0;
		scanf("%d", &desiredBase);
 
		printf("Please enter the integer you wish to convert: \n");
		int baseTenNum = 0;
		scanf("%d", &baseTenNum);

		// Display the string of characters returned by itoa to verify that the function works.
		puts(itoa(baseTenNum, str, desiredBase));
	
		printf("Operation complete. Enter '1' to continue, or '0' to quit.\n");
		scanf("%d", &runFlag);
	}
	
	return 0;
}

// Converts a single integer (assumed to be in base 10), to a user-specified base.
char* itoa(int num, char* str, int base)
{
	char* strHead = str;
	// Special case for a number being negative, in which case a '-' will
	// immediately be appended to the string.
	if(num < 0)
	{
		*str = '-';
		str++;
		// The number itself istreated as an unsigned int from here on out.
		// Because if it isn't, unpleasant bugs like garbled responses, and even
		// segementation faults are observed to occur from trying to work with a negative int.	
		num *= -1; 
	}
	// Special case for a number being '0' itself, in which case the char pointer is 
	// simply returned after tacking on the character '0'.
	if(num == 0)
	{
		*str = '0';
		return str;		
	}	
	else
	{
		// Otherwise, go to work on converting the number to the desired base.
		while(num)
		{
			// Special case where the remainder is greater than 9 (for bases larger than 10).
			if(num % base > 9)
			{
				*str = (num % base) + '7';
			}
			else
			{
				*str = (num % base) + '0';
			}
			num /= base;
			//Move on to the next character in the string.
			str++;
		}
	}
	// Ensure that the pointer to the tail of the string is pointing towards the last
	// character of the string.
	char* strTail = (str - 1);
	char* tempHead = strHead;
	// If the number is negative, we skip that character to avoid swapping the sign with some other digit.
	if(*tempHead == '-')
	{
		tempHead++;
	}
	while(tempHead < strTail)
	{		
		char temp = *tempHead;
		*tempHead++ = *strTail;
		*strTail-- = temp;
	}
	return strHead;
}

