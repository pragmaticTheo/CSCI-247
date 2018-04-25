
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//NOTE TO SELF: The identify unique integer function wasn't working because I mistakenly used the sizeof function
// to pass in what I assumed would be the cardinality of the array, "intArray". However, the sizeof function measures size
// in BYTES, so the for loop would apply the XOR operation to values well outside of the scope of "intArray".

int CountSetBits(unsigned int var);
int identifyUniqueInteger(int arrayCount, int* intArray);
int ReverseBits(int var);
bool OnlyOneBitSet(int); 
bool OnlyOneBitSetInEvenPosition(int);
int ModWithoutUsingModOperator(int numerator, int denominator);
int SwapNibbles(int);
int NumberofOperationsRequired(int);

int main(int argc, char* argv[])
{
	int testInteger = 0;
	sscanf(argv[1], "%d", &testInteger);
	int intArray1[11] = {1, 2, 1, 2, 5, 5, 3, 6, 3, 6, 128000};
	int intArray2[9] = {4, 3, 2, 35, 3, 2, 35, 102, 4};
	int intArray3[5] = {546, 647, 546, 647, 302}; 
	printf("The total amount of set bits in the number given is: %d\n", CountSetBits(testInteger));
	printf("The unique number in the set provided is: %d\n", identifyUniqueInteger((sizeof(intArray1)/sizeof(int)), intArray1));
	printf("The given integer's diminished complement is: %d\n", ReverseBits(testInteger));
	printf("Is there only one bit set in this integer...?: ");
	fputs(OnlyOneBitSet(testInteger) ? "(True) Yeah, there is.\n" : "(False) Oh my, no.\n", stdout);
	
	printf("Is this one bit at an even or an odd position...?: ");
	fputs(OnlyOneBitSetInEvenPosition(testInteger) ? "(True)\n" : "(False)\n", stdout);
}

// Return the number of set  bits in an integer.
int CountSetBits(unsigned int var)
{
	int counter = 0; int bitnumber = 1;
	
	while(bitnumber <= 32)
	{
		if(var & 0x01)
		{
			counter++;	
		}
		bitnumber++;
		var >>= 1;
	}
	return counter;
}

// Given an array of integer where all but one occurs in pairs; identify the unique element.
int identifyUniqueInteger(int arrayCount, int* intArray)
{
	int result = 0;
	for(int i = 0; i < arrayCount; i++)
	{
		result ^= intArray[i];
	}	
	return result;
}

// Reverses the bits in an integer.
int ReverseBits(int var)
{
	return ~var;
}

// Tells whether or not only one bit is set in an integer.
bool OnlyOneBitSet(int var)
{
	if(CountSetBits(var) == 1)
	{
		return true;
	}
	return false;
}

//Discerns whether or not an integer with a single bit set has the set bit at an odd or even position.
bool OnlyOneBitSetInEvenPosition(int var)
{
	if(OnlyOneBitSet(var) == true)
	{
		int bitnumber = 1;
		while(bitnumber <= 32)
		{
			if(var & 0x01)
			{
				if(!(bitnumber % 2))
				{
					fputs("It's in an even position. Neat. ", stdout);
					return true;	
				}else{
					fputs("It's in an odd position... how bizarre! ", stdout);
					return false;
				}
			}
			bitnumber++;
			var >>= 1;
		}
		fputs("Looks like we couldn't find the position of the bit :(", stdout);
		return false;
	}else
	{
		fputs("Sorry, but the number given has more than one set bit.", stdout);
		return false;
	}
}

// Performs a modulus operation with a denominator which has only 1 bit set... without the modulus operator (DUN, DUUUN, DUUUUUUUN)?!?
int ModWithoutUsingModOperator(int numerator, int denominator);
{
	
}



































