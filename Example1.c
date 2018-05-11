# include <stdio.h>

/*
	CSCI 247 - Spring 2018 - Lab 5
	Filename: Example1.c
	1 of 3 in a Series of Simple Reverse-Engineered Trivial Programs.
	Rated 'T' for 'Truly Titilating'.

	Reverse-engineered solution for corresponding example file. See disassembly file
  for my annotated assembly instruction dumps!
*/

int main()
{
  int x = 0;
  int y = 0;
  y += x;
  x += y;
  y += x++;
}
