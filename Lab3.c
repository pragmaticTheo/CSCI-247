#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int CountSetBits(unsigned int var);
int identifyUniqueInteger(int arrayCount, int* intArray);
int ReverseBits(int var);
bool OnlyOneBitSet(int); 
bool OnlyOneBitSetEvenPosition(int);
int ModWithoutUsingModOperator(int numerator, int denominator);
int SwapNibbles(int);
int NumberofOperationsRequired(int);

int main(int argc, char* argv[])
{
	int intArray[7] = {1, 2, 1, 2, 5, 5, 3};
	printf("The total amount of set bits in the number given is: %d\n", CountSetBits(15));
	printf("The unique number in the set provided is: %d\n", identifyUniqueInteger(sizeof(intArray), intArray));
}

// Return the number of set  bits in an integer.
int CountSetBits(unsigned int var)
{
	int counter = 0;
	int bitnumber = 0;
	
	while(bitnumber < 8)
	{
		if(var & 0x01)
		{
			counter++;	
		}
		bitnumber++;
		var = var >> 1;
	}
	return counter;
}

// Given an array of integer where all but one occurs in pairs; identify the unique element.
int identifyUniqueInteger(int arrayCount, int* intArray)
{
	int uniqueNum = 0;
	//for(int i = 0, i < arrayCount - 1, i++)
	//{
		//uniqueNum = *intArray ^ (*(intArray + 1)) ^ (*(intArray + 2)) ^ (*(intArray + 3)) ^ (*(intArray + 4)) ^ (*(intArray + 5)) ^ (*(intArray + 6));
	//}
	uniqueNum = intArray[0];
	for(int i = 0; i < arrayCount; i++)
	{
		uniqueNum = uniqueNum ^ intArray[i + 1];
	}
	return uniqueNum;
}
