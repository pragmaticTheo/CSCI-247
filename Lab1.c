/*
        Course: CSCI 247 - Fall 2017
        File Name: Lab1.c

	PREPROCESSOR DIRECTIVES are orders to import the contents of the named file(s)
	prior to compiling the program. These contents will then effectively replace the directives
	themselves, allowing the content therin to be utilized by the rest of the program.

	MACROS such as "CHAR_DATA_TYPE" can make it easier to change a constant that is used repeatedly
	throughout a program by simply altering the definition here once (as opposed to, say,
	changing a number in 100 places manually), adding flexibility to our program. 
	This also rules out the possibility of simply forgetting to change an instance of a constant, 
	thus completely preventing what would otherwise be an irritating and elusive error to fix.
	Interestingly, it appears that MACROS can also be used to define procedures, many of which
	could have an equivalent function.

	Line 38 is an example of a FORWARD DECLARATION, in which a function that has yet to be defined
	is declared along with key details about what kind of data the function returns and what
	parameters (if any) it takes. It is necessary to do this because otherwise the program would
	simply not recognize that such a function exists when we try to refer to it (as in line 31), as
	the function definition itself is given *after* the main function.

	Using a FUNCTION CALL, as seen at Line 44 confers upon the programmer certain advantages. Firstly, because 
	the function has been defined, the same procedure can be used multiple times without the hassle
	of typing all of the instructions repeatedly. Secondly, this comes with an aesthetic advantage as 
	(properly named) functions reduce clutter in the main function itself, making the program's logic 
	and structure easier to comprehend. 

	Sometimes, the programmer wants to use a character in the "printf" function in a certain way. 
	But this can be a problem because the compiler may normally interpret that same character in an
	entirely different way. For example, using quotes to print a word in quotes "like this" in
	the printf function, as in "I really "like" bananas" wouldn't work because in C, quotes are
	used to enclose a string. In cases like these, an ESCAPE CHARACTER is necessary to treat quotes
	just like any other character and simply print it, like so: "I really \"like\" bananas". 
	Similarly, some uses of the ESCAPE CHARACTER in C tell the compiler to interpret an otherwise
	ordinary character as a special command of some sort, as in the case of "\n", which is interpretted
	as an order to start the next line of text.

	OPERATORS are special terms that apply a specific type of mathematical (or logical) operation 
	to one or more values - the values themselves involved in such an operation are known as "operands."
	As I understand it, by this definition, the predefined OPERATORS which we use most often ( +, -, *, &, <, etc.)
	are functions themselves but with special syntactic rules (e.g., when we add something, we don't have to say
	" +(2 4)" if we want the result of 2 + 2. Macros are similar to functions, and OPERATORS by extension,
	but they also differ in syntax and, most importantly, are *precompiled*. That is, they are preemptively
	calculated instead of being evaluated at runtime.

	KEYWORDS are certain predefined terms that are reserved for use by the programming language.
        Accordingly, no other variables or structures may use these terms as identifiers. Some
        examples here include "void", "int", and "return".

	The display used to view the outcome of the program is significant because it is the default
	output used by the printf function (the terminal, specifically). That is to say, is the default
	value for the pointer, "stdout", or "standard output", which points to a file (which is presumably an 
	abstraction for the monitor in question). Interestingly, one can change this file pointer such that
	the stdout becomes something else entirely, such as a plain ol' text file. There exist two other 
	file pointers used to handle I/O known as stdin (for "standard input") and stderr (for "standard error").
	Typically, I would expect stdin to point to a keyboard (and mouse, if applicable) and stdout to point to
	the terminal. However, I see no reason why these pointers could not be redirected in the same manner as
	stdout.

	
*/



#include <stdio.h>
#include <string.h>

// I realize that I didn't need to make Macros for all of the data types, but I liked
// having them all listed neatly for comparison as I toyed around with the modifiers.
#define CHAR_DATA_TYPE "char"
#define INT_DATA_TYPE "int"
#define FLOAT_DATA_TYPE "float"
#define DOUBLE_DATA_TYPE "double"

// Maximum amount of characters to be recorded.
#define MAX_CHAR_TO_RECORD 100

void PrintMainArguments(int argc, char* argv[]);
void DataTypeSizes(void);
char* GetStringFromStdin(char* str);
void DisplayString(const char* str);

// Where the magic happens.
int main(int argc, char* argv[])
{
    PrintMainArguments(argc, argv);
    DataTypeSizes();
    
    // Create character array and initialize everything to 0 to avoid potential issues with garbage values.
    // I reason that this is okay because the "char" type itself is a subtype of integer value.
    char str[100] = {0};
    GetStringFromStdin(str);
    DisplayString(str);
    return(0);
}

// Shows how many arguments exist within main at time of (this function's) execution.
// It then "regurgitates" these arguments back out to the terminal.
void PrintMainArguments(int argc, char* argv[])
{
        printf("%d\n", argc);
        int i = 0;
        for(i = 0; i < argc; i++)
        {
                puts(argv[i]);
        }
}

// Prints a brief rundown on the basic data types and their corresponding size.
void DataTypeSizes(void)
{
    printf("\"%s\" is a standard C datatype. \nSize of a \"%s\" data type is = %ld bytes.\n",
           CHAR_DATA_TYPE, CHAR_DATA_TYPE, sizeof(char));
    printf("\"%s\" is another standard C datatype. \nSize of a \"%s\" data type is = %ld bytes.\n",
	   INT_DATA_TYPE, INT_DATA_TYPE, sizeof(signed int)); 
    printf("\"%s\" is yet another standard C datatype for decimal representations of numbers."
	   "\nSize of a \"%s\" data type is = %ld  bytes.\n", 
	   FLOAT_DATA_TYPE, FLOAT_DATA_TYPE, sizeof(float));
    printf("Lastly, \"%s\" is a standard C datatype meant for more precise floating point numbers."
           " \nSize of a \"%s\" data type is = %ld bytes.\n",
	   DOUBLE_DATA_TYPE, DOUBLE_DATA_TYPE, sizeof(double));
}

// Records a string from standard input.
char* GetStringFromStdin(char* str)
{
        fgets(str, MAX_CHAR_TO_RECORD, stdin); 
}

// Prints out a string contained within a given character array.
//The constant keyword is significant because we want to pass the pointer to the *Array* containing our string
// to be printed here - a pointer which is immutable, and hence constant. In this way, we can guarantee that
// an array handle in particular is passed off to DisplayString.
void DisplayString(const char* str)
{
        puts(str);
}
        

















