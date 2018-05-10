#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*
	CSCI 247 - Spring 2018
	Filename: Lab4.c
	A Series of Floating Point Oriented Bitwise Functions by Brandon Chavez.
	Rated 'S' for "Snuffleupagus".

	This program is a collection of bit-wise manipulation functions for use with
  a float_bits strucuture.

  NOTE that Main must be supplied with two command-line arguments: The first specifies the desired
  mode for the input argument that the functions will examine. Simply enter 'd' for decimal and 'h'
  for hexadecimal. The second argument is the number you wish to use to set myFloat's bits. Entering
  0x is not necessary for hexadecimal input.
*/

#define MANTISSA_MASK 0x7fffff
#define DENORMALIZED_MASK 0xff

// From lab prompt: "access bit-level representation of a floating-point number."
typedef unsigned float_bits;

float itof(float_bits myFloat);
int floatClass(float_bits myFloat);
float_bits float_negate(float_bits f);
float_bits float_absval(float_bits f);
float_bits float_twice(float_bits f);
float_bits float_half(float_bits f);

int main(int argc, char* argv[])
{
  printf("======================================================================\n");
  float_bits myFloat = 0;
  if(*argv[1] == 'd')
  {
    printf("Input parameter type set to Decimal.\n");
    myFloat = atoi(argv[2]);
    printf("The number you have provided to represent the set bits in myFloat is: %d\n", myFloat);
  }else if(*argv[1] == 'h')
  {
    printf("Input parameter type set to Hexadecimal.\n Note that \"0x\" prefix is not required.\n");
    myFloat = strtol(argv[2], NULL, 16);
    printf("The number you have provided to represent the set bits in myFloat is: 0x%08x\n", myFloat);
  }else
  {
    printf("ERROR: input parameter type is invalid.\n");
    return  -1;
  }

  printf("The set bits in myFloat are accordingly now: 0x%08x\n", myFloat);
  float trueFloat = itof(myFloat);
  printf("Using the IEEE 754 SP Floating Point Standard, truncated to 10 decimal places:\n\n");

  printf("myFloat evaluates to: %.10f\n\n", trueFloat);
  int class = floatClass(myFloat);
  switch(class)
  {
    case 0 : printf("This value is +0 or -0.\n\n");
    break;
    case 1: printf("This value is +infinity or -infinity.\n\n");
    break;
    case 2: printf("Whoa, yo. This value is NaN!\n\n");
    break;
    case 3: printf("This value is a denormalized number.\n\n");
    break;
    case 4: printf("This value is a normalized number.\n\n");
    break;
  }
  float_negate(myFloat);
  float_absval(myFloat);
  float_twice(myFloat);
  float_half(myFloat);

}
// Lovely helper function that translates our float_bits object (an integer) into the
// actual IEEE 754 Standard floating-point value.
float itof(float_bits f)
{
  int sign = f >> 31;
  // ORing with a bit mask just *one* bit longer than the mantissa (with that bit set) adds
  // the implied 1.
  int mantissa = (f & MANTISSA_MASK) | 0x800000;
  // Isolate the exp and the sign bit. Then isolate the mantissa with bitmask. This is 'e'.
  int exp = ((f >> 23) & 0xFF) - 127 - 23;

  float result = (mantissa * (pow(2.0, exp)) * ((sign == 1) ? -1 : 1));
  return result;
}
// Determines the classification of a floating-point number.
int floatClass(float_bits f)
{
  unsigned signAndExp = f >> 23;
  // If all the bits in the exp are 0, it's either +0, -0, or a denormalized number.
  if(!(signAndExp & DENORMALIZED_MASK))
  {
    if(f & MANTISSA_MASK)
    {
      return 3;
    }else
    {
      return 0;
    }
  // Conversely, if all of the exp bits are 1, it's either +infinity, -infinity, or NaN.
  }else if((signAndExp & DENORMALIZED_MASK) == DENORMALIZED_MASK)
  {
    if(f & MANTISSA_MASK)
    {
      return 2;
    }else
    {
      return 1;
    }
  }else
  {
    return 4;
  }
}
// Flips the sign bit of a floating-point number.
float_bits float_negate(float_bits f)
{
  f = (0x80000000 ^ f);
  printf("The negated value of myFloat is: %.10f\n", itof(f));
  printf("Hex representation: 0x%08x\n\n", f);
  return f;
}
// Determines the absolute value of a floating-point number.
float_bits float_absval(float_bits f)
{
  // Effectively clears the sign bit.
  f = ((f << 1) >> 1);
  printf("The absolute value of myFloat is: %.10f\n", itof(f));
  printf("Hex representation: 0x%08x\n\n", f);
  return f;
}
// Doubles a floating-point number.
float_bits float_twice(float_bits f)
{
  //Incrementing the exponent effectively doubles the number as it measures in powers of 2.
  //Note that this will only work for normalized number.
  if(!(floatClass(f) == 4))
  {
    printf("Yikes! Doubling operation only works for normalized numbers.\n");
    return -1;
  }
  int signAndExp = (((f >> 23) + 1) << 23);
  f = ((f << 9) >> 9) | signAndExp;
  printf("The value of myFloat doubled is: %.10f\n", itof(f));
  printf("Hex representation: 0x%08x\n\n", f);
  return f;
}
// Halves a floating-point number.
float_bits float_half(float_bits f)
{
  if(!(floatClass(f) == 4))
  {
    printf("Yikes! Halfing operation only works for normalized numbers.\n");
    return -1;
  }
  int signAndExp = (((f >> 23) - 1) << 23);
  f = ((f << 9) >> 9) | signAndExp;
  printf("The value of myFloat halfed is: %.10f\n", itof(f));
  printf("Hex representation: 0x%08x\n\n", f);
  return f;
}
