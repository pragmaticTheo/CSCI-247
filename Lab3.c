#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// NOTE TO SELF: Everything appears to be working properly up through Task 7 ("Swap nibbles within each byte of an integer").
// Might be worth investigating the behavior of "CountSetBits" when negative numbers are provided.

int CountSetBits(unsigned int var);
int identifyUniqueInteger(int arrayCount, int* intArray);
int ReverseBits(int var);
bool OnlyOneBitSet(int); 
bool OnlyOneBitSetInEvenPosition(int);
int ModWithoutUsingModOperator(int numerator, int denominator);
int SwapNibbles(int);
int NumberOfOperationsRequired(int);

// This basic testing interface must be provided with three command line arguments: 
// The first number (testInteger) is processed by every function written for the lab.
// The second number (testInteger2) serves as the denominator for the "ModulusWithoutUsingModOperator" function. 
// testInteger2 *MUST* have only one set bit in order to guarantee that the function works correctly.
// The third argument is the array that you wish to use to test the "identifyUniqueInteger" function.

int main(int argc, char* argv[])
{
	int testInteger = 0;
	int testInteger2 = 0;
	sscanf(argv[1], "%d", &testInteger);
	sscanf(argv[2], "%d", &testInteger2);
	
	// Subject Arrays for testing the "identifyUniqueInteger" function. This can be chosen by changing 
	int intArray1[11] = {1, 2, 1, 2, 5, 5, 3, 6, 3, 6, 128000};
	int intArray2[9] = {4, 3, 2, 35, 3, 2, 35, 102, 4};
	int intArray3[5] = {546, 647, 546, 647, 302}; 
	
	printf("The total amount of set bits in the number given is: %d\n", CountSetBits(testInteger));
	printf("The unique number in the set provided is: %d\n", identifyUniqueInteger((sizeof(intArray3)/sizeof(int)), intArray3));
	printf("Reversing all bits, including the sign bit, of %d yields the number: %d\n", testInteger, ReverseBits(testInteger));
	printf("Is there only one bit set in this integer...?: ");
	fputs(OnlyOneBitSet(testInteger) ? "(True) Yeah, there is.\n" : "(False) Oh my, no.\n", stdout);	
	printf("Is this one bit at an even or an odd position...?: ");
	fputs(OnlyOneBitSetInEvenPosition(testInteger) ? "(True)\n" : "(False)\n", stdout);
	printf("The remainder of the given numerator and base 2 denominator is: %d\n", ModWithoutUsingModOperator(testInteger, testInteger2));
	printf("Swapping the nibbles of the number %d yields the number: %d\n", testInteger, SwapNibbles(testInteger));
	printf("The amount of iterations required to reduce the preset counter to 1, is: %d\n", NumberOfOperationsRequired(testInteger));
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
	int reverseVar = 0;
	// Traverse all bits in var...
	for(int i = 0; i < 32; i++)
	{
		// And if the bit is set, assign it to the opposite position in reverseVar.
		if(var & (1 << i))
		{
			reverseVar |= 1 << ((31) - i);
		}
	}
	return reverseVar;
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
				if(bitnumber % 2)
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
int ModWithoutUsingModOperator(int numerator, int denominator)
{
	// Get first 'n' bits of the numerator, based upon the number of leading zeros in the denominator.
	int trailingZeroes = 0;
	// Count the amount of leading zeros in the denominator.
	for(int i = 0; i < 32; i++)
	{
		if(!(denominator & 0x01))
		{
			trailingZeroes++;
			denominator >>= 1;	
		}
		else{
			break;
		}
	}
	// Make a bit mask for the number of trailing zeros (places).
	int isolatingMask = 0;	for(int i = 0; i < trailingZeroes; i++)
	{
		isolatingMask |= 1 << i;
	}	
	// Isolate this number of bits in the numerator, which happens to be the remainder.
	numerator &= isolatingMask;
	return numerator;
}

// Swaps the nibbles within each byte of an integer
int SwapNibbles(int var)
{
	if(!var)
	{
		return 0;
	}
	int nibbleRetainer = 0;
	for(int i = 0; i < 32; i++)
	{
		// Gather 4 bits. Once 4 bits are accumulated...
		if((!(i % 4)) && (i != 0))
		{
			// Assign the next four bits to the four corresponding bits to the right (after clearing them).
			for(int j = i; j < (i + 4); j++)
			{
				var &= ~(1 << (j - 4));
				// If this bit is set then set the bit 4 places to the right.
				if(var & (1 << j))
				{
					var |= (1 << (j - 4));
				}
			}
			// Complete nibble swap by 'emptying' nibbleRetainer into these same 4 bits.
			for(int j = i; j < (i + 4); j++)
			{
				var &= ~(1 << j);
				if(nibbleRetainer & (1 << (j - 4)))
				{
					var |= (1 << j);
				}	
			}
			// Skip the next 4 bits, as we just swapped them with the previous 4 bits.
			i += 4;		
		}
		if(var & (1 << i))
		{
			nibbleRetainer |= (1 << i);
		}		
	}
	return var;
}

// Counter Game - If the counter passed in is a power of 2, reduce the counter.
int NumberOfOperationsRequired(int presetCounter)
{
	int loopCount = 0;
	while(presetCounter > 1)
	{
		// If it is the case that presetCounter is a power of 2...
		int result = (presetCounter && (presetCounter & (presetCounter - 1)) == 0);
		if(result)
		{
			presetCounter >>= 1; 
		}
		loopCount++;
	}
	return loopCount;
}
























